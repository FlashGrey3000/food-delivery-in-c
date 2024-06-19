#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_OPTION_LENGTH 50

void update_reviews(const char* restaurant_name, float *new_rating) {
    FILE *file = fopen("city_wise_rests/zomato_chennai.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    char updated_lines[1024][1024]; // Store updated lines
    int updated_lines_count = 0;
    char lower_restaurant_name[100];
    strcpy(lower_restaurant_name, restaurant_name);
    to_lowercase(lower_restaurant_name);

    while (fgets(line, sizeof(line), file)) {
        char original_line[1024];
        strcpy(original_line, line);

        char *name = strtok(line, " :");
        char *averageRatingStr = strtok(NULL, " :");
        char *rest = strtok(NULL, "\n");

        if (name != NULL && averageRatingStr != NULL && rest != NULL) {
            char lower_name[100];
            strcpy(lower_name, name);
            to_lowercase(lower_name);

            if (strcmp(lower_restaurant_name, lower_name) == 0) {
                float averageRating = atof(averageRatingStr);
                char *last_colon = strrchr(rest, ':');
                if (last_colon != NULL) {
                    int totalReviews = atoi(last_colon + 1);

                    averageRating = ((averageRating * totalReviews) + *new_rating) / (totalReviews + 1);
                    totalReviews += 1;

                    // Remove old total reviews from rest
                    *last_colon = '\0';

                    // Format updated line
                    snprintf(original_line, sizeof(original_line), "%s : %.1f : %s : %d\n", name, averageRating, rest, totalReviews);
                }
            }
        }

        strcpy(updated_lines[updated_lines_count++], original_line);
    }

    fclose(file);

    // Reopen the file in write mode to overwrite it with updated content
    file = fopen("city_wise_rests/zomato_chennai.txt", "w");
    if (file == NULL) {
        perror("Error reopening file");
        return;
    }

    for (int i = 0; i < updated_lines_count; i++) {
        fputs(updated_lines[i], file);
    }

    fclose(file);
}

// int main() {
//     const char* filename = "ratings.txt";
//     char option[MAX_OPTION_LENGTH];
//     int rating;

//     printf("Please enter the option name: ");
//     scanf(" '%[^']'", option); // Read a string between single quotes

//     printf("Please enter your rating (1-5): ");
//     scanf("%d", &rating);

//     if(rating < 1 || rating > 5) {
//         printf("Invalid rating. Please rate between 1 and 5.\n");
//         return 1;
//     }

//     updateRating(filename, option, rating);

//     return 0;
// }
