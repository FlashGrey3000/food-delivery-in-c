#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_OPTION_LENGTH 50

void update_reviews(const char* restaurant_name, float *new_rating) {
    FILE *file = fopen("city_wise_rests/zomato_chennai.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    char updated_lines[1024][1024]; // Store updated lines
    int updated_lines_count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, " :");
        char *averageRatingStr = strtok(NULL, " :");
        char *rest = strtok(NULL, "\n");

        if (name != NULL && averageRatingStr != NULL && rest != NULL && strcmp(name, restaurant_name) == 0) {
            float averageRating = atof(averageRatingStr);
            int totalReviews = atoi(strrchr(rest, ':') + 1);

            averageRating = ((averageRating * totalReviews) + *new_rating) / (totalReviews + 1);
            totalReviews += 1;

            // Format updated line
            snprintf(line, sizeof(line), "%s : %.1f : %s : %d\n", name, averageRating, rest, totalReviews);
        } else {
            // Restore original line structure
            snprintf(line, sizeof(line), "%s : %s : %s\n", name, averageRatingStr, rest);
        }

        strcpy(updated_lines[updated_lines_count++], line);
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
