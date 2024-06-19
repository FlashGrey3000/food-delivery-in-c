#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* items;
    int count;
    int support;
} Itemset;

typedef struct {
    int* items;
    int count;
} Transaction;

void generate_candidates(Itemset* previous_level, int previous_count, Itemset** candidates, int* candidate_count, int itemset_size);
void count_support(Transaction* transactions, int transaction_count, Itemset* candidates, int candidate_count);
void prune_candidates(Itemset** candidates, int* candidate_count, int min_support);
int is_subset(int* subset, int subset_size, int* set, int set_size);
int* merge_itemsets(int* set1, int size1, int* set2, int size2);
Transaction* read_transactions(const char* filename, int* transaction_count);
void free_transactions(Transaction* transactions, int transaction_count);
void print_itemset(Itemset itemset);
void free_itemsets(Itemset* itemsets, int count);
int* find_frequent_with(int number, Itemset* frequent_itemsets, int itemset_count, int* result_count);
Itemset deep_copy_itemset(Itemset itemset);

// int main() {
//     int transaction_count;
//     Transaction* transactions = read_transactions("transactions.txt", &transaction_count);

//     // Print the transactions
//     for (int i = 0; i < transaction_count; i++) {
//         printf("Transaction %d: ", i + 1);
//         for (int j = 0; j < transactions[i].count; j++) {
//             printf("%d ", transactions[i].items[j]);
//         }
//         printf("\n");
//     }

//     int min_support = 4;

//     // Determine the distinct items for initial candidates
//     int item_counts[1000] = {0};  // Assuming item IDs are less than 1000 for simplicity
//     for (int i = 0; i < transaction_count; i++) {
//         for (int j = 0; j < transactions[i].count; j++) {
//             item_counts[transactions[i].items[j]]++;
//         }
//     }

//     // Initialize candidates (single items)
//     int initial_candidate_count = 0;
//     for (int i = 0; i < 1000; i++) {
//         if (item_counts[i] > 0) {
//             initial_candidate_count++;
//         }
//     }

//     Itemset* candidates = (Itemset*)malloc(initial_candidate_count * sizeof(Itemset));
//     int candidate_index = 0;
//     for (int i = 0; i < 1000; i++) {
//         if (item_counts[i] > 0) {
//             candidates[candidate_index] = (Itemset){ .items = malloc(sizeof(int)), .count = 1, .support = 0 };
//             candidates[candidate_index].items[0] = i;
//             candidate_index++;
//         }
//     }
//     int candidate_count = initial_candidate_count;

//     // Count support and prune candidates
//     count_support(transactions, transaction_count, candidates, candidate_count);
//     prune_candidates(&candidates, &candidate_count, min_support);

//     Itemset* frequent_itemsets = NULL;
//     int frequent_itemset_count = 0;

//     // Generate and prune itemsets iteratively
//     int itemset_size = 2;
//     while (candidate_count > 0) {
//         printf("Frequent itemsets of size %d:\n", itemset_size - 1);
//         for (int i = 0; i < candidate_count; i++) {
//             print_itemset(candidates[i]);
//         }

//         // Append current candidates to frequent itemsets
//         frequent_itemsets = realloc(frequent_itemsets, (frequent_itemset_count + candidate_count) * sizeof(Itemset));
//         for (int i = 0; i < candidate_count; i++) {
//             frequent_itemsets[frequent_itemset_count + i] = deep_copy_itemset(candidates[i]);
//         }
//         frequent_itemset_count += candidate_count;

//         Itemset* new_candidates;
//         int new_candidate_count;
//         generate_candidates(candidates, candidate_count, &new_candidates, &new_candidate_count, itemset_size);
//         free_itemsets(candidates, candidate_count);

//         count_support(transactions, transaction_count, new_candidates, new_candidate_count);
//         prune_candidates(&new_candidates, &new_candidate_count, min_support);

//         candidates = new_candidates;
//         candidate_count = new_candidate_count;
//         itemset_size++;
//     }

//     // Print all frequent itemsets
//     // printf("All frequent itemsets:\n");
//     // for (int i = 0; i < frequent_itemset_count; i++) {
//     //     print_itemset(frequent_itemsets[i]);
//     // }

//     // Example usage of find_frequent_with
//     int number_to_check; // Change this to the number you want to check
//     int nums;
//     printf("Enter number to check: ");
//     scanf("%d", &number_to_check);
//     printf("Numbers frequent with %d:\n", number_to_check);
//     int* result = find_frequent_with(number_to_check, frequent_itemsets, frequent_itemset_count, &nums);
//     printf("Items frequent with 1: ");
//     for (int i = 0; i < nums; i++) {
//         printf("%d ", result[i]);
//     }
//     printf("\n");

//     // Free allocated memory
//     free_transactions(transactions, transaction_count);
//     free_itemsets(frequent_itemsets, frequent_itemset_count);

//     return 0;
// }

void generate_candidates(Itemset* previous_level, int previous_count, Itemset** candidates, int* candidate_count, int itemset_size) {
    int max_candidates = previous_count * (previous_count - 1) / 2;
    *candidates = (Itemset*)malloc(max_candidates * sizeof(Itemset));
    *candidate_count = 0;

    for (int i = 0; i < previous_count; i++) {
        for (int j = i + 1; j < previous_count; j++) {
            int* merged = merge_itemsets(previous_level[i].items, previous_level[i].count, previous_level[j].items, previous_level[j].count);
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
            free((*candidates)[i].items);
        }
    }
    *candidates = (Itemset*)realloc(*candidates, new_count * sizeof(Itemset));
    *candidate_count = new_count;
}

int is_subset(int* subset, int subset_size, int* set, int set_size) {
    for (int i = 0; i < subset_size; i++) {
        int found = 0;
        for (int j = 0; j < set_size; j++) {
            if (subset[i] == set[j]) {
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

int* merge_itemsets(int* set1, int size1, int* set2, int size2) {
    if (size1 != size2) return NULL;
    for (int i = 0; i < size1 - 1; i++) {
        if (set1[i] != set2[i]) return NULL;
    }
    if (set1[size1 - 1] == set2[size2 - 1]) return NULL;

    int* merged = (int*)malloc((size1 + 1) * sizeof(int));
    for (int i = 0; i < size1 - 1; i++) {
        merged[i] = set1[i];
    }
    merged[size1 - 1] = set1[size1 - 1];
    merged[size1] = set2[size2 - 1];

    return merged;
}

Transaction* read_transactions(const char* filename, int* transaction_count) {
    FILE* file = fopen(filename, "r");
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

        int* items = NULL;
        int item_count = 0;
        char* token = strtok(line, " \n");
        while (token) {
            items = realloc(items, (item_count + 1) * sizeof(int));
            if (!items) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            items[item_count++] = atoi(token);
            token = strtok(NULL, " \n");
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
        free(transactions[i].items);
    }
    free(transactions);
}

void print_itemset(Itemset itemset) {
    for (int i = 0; i < itemset.count; i++) {
        printf("%d ", itemset.items[i]);
    }
    printf("\n");
}

void free_itemsets(Itemset* itemsets, int count) {
    for (int i = 0; i < count; i++) {
        free(itemsets[i].items);
    }
    free(itemsets);
}

int* find_frequent_with(int number, Itemset* frequent_itemsets, int itemset_count, int* result_count) {
    int* result = NULL;
    *result_count = 0;

    for (int i = 0; i < itemset_count; i++) {
        Itemset itemset = frequent_itemsets[i];
        if (itemset.count == 2) { // Ensure we only consider itemsets of size 2
            int found = 0;
            for (int j = 0; j < itemset.count; j++) {
                if (itemset.items[j] == number) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                for (int j = 0; j < itemset.count; j++) {
                    if (itemset.items[j] != number) {
                        result = realloc(result, (*result_count + 1) * sizeof(int));
                        if (!result) {
                            perror("Failed to allocate memory");
                            exit(EXIT_FAILURE);
                        }
                        result[*result_count] = itemset.items[j];
                        (*result_count)++;
                    }
                }
            }
        }
    }

    return result;
}


Itemset deep_copy_itemset(Itemset itemset) {
    Itemset copy;
    copy.count = itemset.count;
    copy.support = itemset.support;
    copy.items = malloc(itemset.count * sizeof(int));
    memcpy(copy.items, itemset.items, itemset.count * sizeof(int));
    return copy;
}
