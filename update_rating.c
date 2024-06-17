#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_OPTION_LENGTH 50

void updateRating(const char* filename, const char* option, int newRating) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read the entire file and store lines
    char lines[5][MAX_LINE_LENGTH]; // Assuming there are 5 options
    int count = 0;
    while (fgets(lines[count], MAX_LINE_LENGTH, file) && count < 5) {
        count++;
    }
    fclose(file);

    // Update the rating for the chosen option
    for (int i = 0; i < count; i++) {
        char opt[MAX_OPTION_LENGTH];
        int totalReviews;
        float averageRating;
        sscanf(lines[i], "'%[^']',%d,%f", opt, &totalReviews, &averageRating);
        if (strcmp(opt, option) == 0) {
            averageRating = ((averageRating * totalReviews) + newRating) / (totalReviews + 1);
            totalReviews++;
            sprintf(lines[i], "'%s',%d,%f\n", opt, totalReviews, averageRating);
            break;
        }
    }

    // Write updated lines back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fputs(lines[i], file);
    }
    fclose(file);
}

int main() {
    const char* filename = "ratings.txt";
    char option[MAX_OPTION_LENGTH];
    int rating;

    printf("Please enter the option name: ");
    scanf(" '%[^']'", option); // Read a string between single quotes

    printf("Please enter your rating (1-5): ");
    scanf("%d", &rating);

    if(rating < 1 || rating > 5) {
        printf("Invalid rating. Please rate between 1 and 5.\n");
        return 1;
    }

    updateRating(filename, option, rating);

    return 0;
}
