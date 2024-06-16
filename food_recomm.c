#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** items;
    int count;
} Transaction;

typedef struct {
    char** items;
    int count;
    int support;
} Itemset;

void generate_candidates(Itemset* previous_level, int previous_count, Itemset** candidates, int* candidate_count, int itemset_size);
void count_support(Transaction* transactions, int transaction_count, Itemset* candidates, int candidate_count);
void prune_candidates(Itemset** candidates, int* candidate_count, int min_support);
int is_subset(char** subset, int subset_size, char** set, int set_size);
char** merge_itemsets(char** set1, int size1, char** set2, int size2);

Transaction* read_transactions(const char* filename, int* transaction_count);
void free_transactions(Transaction* transactions, int transaction_count);
void print_itemset(Itemset itemset);
void free_itemsets(Itemset* itemsets, int count);

int main() {
    int transaction_count;
    Transaction* transactions = read_transactions("transactions.txt", &transaction_count);

    // Print the transactions
    for (int i = 0; i < transaction_count; i++) {
        printf("Transaction %d: ", i + 1);
        for (int j = 0; j < transactions[i].count; j++) {
            printf("%s ", transactions[i].items[j]);
        }
        printf("\n");
    }

    int min_support = 2;

    // Determine the distinct items for initial candidates
    char* distinct_items[1000];
    int distinct_count = 0;

    for (int i = 0; i < transaction_count; i++) {
        for (int j = 0; j < transactions[i].count; j++) {
            int exists = 0;
            for (int k = 0; k < distinct_count; k++) {
                if (strcmp(transactions[i].items[j], distinct_items[k]) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                distinct_items[distinct_count] = strdup(transactions[i].items[j]); // Use strdup to copy the string
                distinct_count++;
            }
        }
    }

    // Initialize candidates (single items)
    Itemset* candidates = (Itemset*)malloc(distinct_count * sizeof(Itemset));
    for (int i = 0; i < distinct_count; i++) {
        candidates[i].items = (char**)malloc(sizeof(char*));
        candidates[i].items[0] = strdup(distinct_items[i]); // Use strdup to copy the string
        candidates[i].count = 1;
        candidates[i].support = 0;
    }
    int candidate_count = distinct_count;

    // Count support and prune candidates
    count_support(transactions, transaction_count, candidates, candidate_count);
    prune_candidates(&candidates, &candidate_count, min_support);

    // Generate and prune itemsets iteratively
    int itemset_size = 2;
    while (candidate_count > 0) {
        printf("Frequent itemsets of size %d:\n", itemset_size - 1);
        for (int i = 0; i < candidate_count; i++) {
            print_itemset(candidates[i]);
        }

        Itemset* new_candidates;
        int new_candidate_count;
        generate_candidates(candidates, candidate_count, &new_candidates, &new_candidate_count, itemset_size);
        free_itemsets(candidates, candidate_count);

        count_support(transactions, transaction_count, new_candidates, new_candidate_count);
        prune_candidates(&new_candidates, &new_candidate_count, min_support);

        candidates = new_candidates;
        candidate_count = new_candidate_count;
        itemset_size++;
    }

    // Free allocated memory
    for (int i = 0; i < distinct_count; i++) {
        free(distinct_items[i]);
    }
    free_transactions(transactions, transaction_count);

    return 0;
}

void generate_candidates(Itemset* previous_level, int previous_count, Itemset** candidates, int* candidate_count, int itemset_size) {
    int max_candidates = previous_count * (previous_count - 1) / 2;
    *candidates = (Itemset*)malloc(max_candidates * sizeof(Itemset));
    *candidate_count = 0;

    for (int i = 0; i < previous_count; i++) {
        for (int j = i + 1; j < previous_count; j++) {
            char** merged = merge_itemsets(previous_level[i].items, previous_level[i].count, previous_level[j].items, previous_level[j].count);
            if (merged != NULL) {
                (*candidates)[*candidate_count].items = merged;
                (*candidates)[*candidate_count].count = itemset_size;
                (*candidates)[*candidate_count].support = 0;
                (*candidate_count)++;
            }
        }
    }
}

void count_support(Transaction* transactions, int transaction_count, Itemset* candidates, int candidate_count) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < transaction_count; j++) {
            if (is_subset(candidates[i].items, candidates[i].count, transactions[j].items, transactions[j].count)) {
                candidates[i].support++;
            }
        }
    }
}

void prune_candidates(Itemset** candidates, int* candidate_count, int min_support) {
    int new_count = 0;
    for (int i = 0; i < *candidate_count; i++) {
        if ((*candidates)[i].support >= min_support) {
            (*candidates)[new_count++] = (*candidates)[i];
        } else {
            for (int j = 0; j < (*candidates)[i].count; j++) {
                free((*candidates)[i].items[j]);
            }
            free((*candidates)[i].items);
        }
    }
    *candidates = (Itemset*)realloc(*candidates, new_count * sizeof(Itemset));
    *candidate_count = new_count;
}

int is_subset(char** subset, int subset_size, char** set, int set_size) {
    for (int i = 0; i < subset_size; i++) {
        int found = 0;
        for (int j = 0; j < set_size; j++) {
            if (strcmp(subset[i], set[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

char** merge_itemsets(char** set1, int size1, char** set2, int size2) {
    if (size1 != size2) return NULL;
    for (int i = 0; i < size1 - 1; i++) {
        if (strcmp(set1[i], set2[i]) != 0) return NULL;
    }
    if (strcmp(set1[size1 - 1], set2[size2 - 1]) == 0) return NULL;

    char** merged = (char**)malloc((size1 + 1) * sizeof(char*));
    for (int i = 0; i < size1 - 1; i++) {
        merged[i] = strdup(set1[i]);
    }
    merged[size1 - 1] = strdup(set1[size1 - 1]);
    merged[size1] = strdup(set2[size2 - 1]);

    return merged;
}

Transaction* read_transactions(const char* filename, int* transaction_count) {
    FILE* file = fopen("Transactions.txt", "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    Transaction* transactions = NULL;
    char line[256];
    *transaction_count = 0;

    while (fgets(line, sizeof(line), file)) {
        transactions = realloc(transactions, (*transaction_count + 1) * sizeof(Transaction));
        if (!transactions) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }

        char** items = NULL;
        int item_count = 0;
        char* token = strtok(line, ",\n");
        while (token) {
            items = realloc(items, (item_count + 1) * sizeof(char*));
            if (!items) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            items[item_count] = strdup(token); // Use strdup to copy the string
            item_count++;
            token = strtok(NULL, ",\n");
        }

        transactions[*transaction_count].items = items;
        transactions[*transaction_count].count = item_count;
        (*transaction_count)++;
    }

    fclose(file);
    return transactions;
}

void free_transactions(Transaction* transactions, int transaction_count) {
    for (int i = 0; i < transaction_count; i++) {
        for (int j = 0; j < transactions[i].count; j++) {
            free(transactions[i].items[j]);
        }
        free(transactions[i].items);
    }
    free(transactions);
}

void print_itemset(Itemset itemset) {
    for (int i = 0; i < itemset.count; i++) {
        printf("%s ", itemset.items[i]);
    }
    printf("\n");
}

void free_itemsets(Itemset* itemsets, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < itemsets[i].count; j++) {
            free(itemsets[i].items[j]);
        }
        free(itemsets[i].items);
    }
    free(itemsets);
}