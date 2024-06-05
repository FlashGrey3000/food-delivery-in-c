#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Function to tokenize a string and convert it into a vector (TF)
void tokenize_and_vectorize(const char *str, int *vector, char **vocabulary, int vocab_size) {
    char *temp_str = strdup(str);  // Duplicate the string to avoid modifying the original
    char *token = strtok(temp_str, " ");
    while (token != NULL) {
        for (int i = 0; i < vocab_size; i++) {
            if (strcmp(token, vocabulary[i]) == 0) {
                vector[i]++;
                break;
            }
        }
        token = strtok(NULL, " ");
    }
    free(temp_str);  // Free the duplicated string
}

// Function to calculate cosine similarity between two vectors
double cosine_similarity(int *vec1, int *vec2, int size) {
    double dot_product = 0.0, norm_a = 0.0, norm_b = 0.0;
    for (int i = 0; i < size; i++) {
        dot_product += vec1[i] * vec2[i];
        norm_a += vec1[i] * vec1[i];
        norm_b += vec2[i] * vec2[i];
    }
    return dot_product / (sqrt(norm_a) * sqrt(norm_b));
}

// Function to find the string in the array most similar to the search string
char* find_most_similar_string(char **array, int array_size, const char *search_string, char **vocabulary, int vocab_size) {
    int search_vector[vocab_size];
    memset(search_vector, 0, sizeof(search_vector));

    tokenize_and_vectorize(search_string, search_vector, vocabulary, vocab_size);

    double max_similarity = -1.0;
    int best_match_index = -1;

    for (int i = 0; i < array_size; i++) {
        int array_vector[vocab_size];
        memset(array_vector, 0, sizeof(array_vector));
        tokenize_and_vectorize(array[i], array_vector, vocabulary, vocab_size);

        double similarity = cosine_similarity(search_vector, array_vector, vocab_size);
        if (similarity > max_similarity) {
            max_similarity = similarity;
            best_match_index = i;
        }
    }

    // Check if a match was found
    if (best_match_index == -1) {
        return NULL;
    }

    return array[best_match_index];
}

int main() {
    
    char *vocabulary[] = {"mamagoto",
"paprika", "-", "courtyard", "by", "marriott",
"above", "sea", "level", "-", "the", "raintree",
"the", "reef", "-", "sheraton", "grand",
"punjab", "grill",
"soy", "soi",
"hamsa",
"bombay", "brasserie",
"azzuri", "bay",
"annalakshmi", "restaurant",
"savoury", "sea", "shell",
"the", "flying", "elephant", "-", "park", "hyatt",
"amelie's",
"little", "italy",
"ente", "keralam",
"sandy's", "chocolate", "laboratory",
"the", "fat", "boy",
"mkc", "-", "madras", "kitchen", "company",
"madras", "pavilion", "-", "itc", "grand", "chola",
"tuscana", "pizzeria",
"sigree",
"cream", "centre",
"junior", "kuppanna",
"brew", "room",
"upper", "deck", "-", "taj", "fisherman's", "cove", "resort", "&", "spa",
"sangeetha", "veg", "restaurant",
"pitcherr", "perfect",
"the", "alcove",
"flying", "elephant",
"grill", "wagon"};
    int vocab_size = sizeof(vocabulary) / sizeof(vocabulary[0]);

    char *array[] = {
"mamagoto", "paprika - courtyard by marriott", "above sea level - the raintree", "the reef - sheraton grand", "punjab grill", "soy soi", "hamsa", "bombay brasserie", "azzuri bay", "annalakshmi restaurant", "savoury sea shell", "the flying elephant - park hyatt", "amelie's", "little italy", "ente keralam", "sandy's chocolate laboratory", "the fat boy", "mkc - madras kitchen company", "madras pavilion - itc grand chola", "tuscana pizzeria", "sigree", "cream centre", "junior kuppanna", "the brew room", "upper deck - taj fisherman's cove resort & spa", "sangeetha veg restaurant", "pitcherr perfect", "the alcove", "grill wagon", "the flying elephant"
    };
    int array_size = sizeof(array) / sizeof(array[0]);

    char search_string[] = "Elephant food";

    char *most_similar = find_most_similar_string(array, array_size, search_string, vocabulary, vocab_size);
    if (most_similar != NULL) {
        printf("Most similar string: %s\n", most_similar);
    } else {
        printf("No similar string found.\n");
    }

    return 0;
}
