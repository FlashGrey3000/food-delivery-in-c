#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    float rating;
    float distance;
    float travel_time;
} Restaurant;

void parse_line(const char *line, Restaurant *restaurant) {
    sscanf(line, "%[^:]: %f: Distance: %f km, Travel time: %f min", restaurant->name, &restaurant->rating, &restaurant->distance, &restaurant->travel_time);
}

int compare_by_distance(const void *a, const void *b) {
    float distA = ((Restaurant *)a)->distance;
    float distB = ((Restaurant *)b)->distance;
    return (distA > distB) - (distA < distB); // returns -1, 0, or 1
}

int compare_by_rating(const void *a, const void *b) {
    float ratA = ((Restaurant *)a)->rating;
    float ratB = ((Restaurant *)b)->rating;
    return (ratB > ratA) - (ratB < ratA); // returns 1, 0, or -1 to sort in descending order
}

void store_rests(const char *username, Restaurant **restaurants, int *n_rest) {
    char filename[128];
    sprintf(filename, "db/user/%s.txt", username);
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    char line[512];
    int count = 0;

    // Skip the first 10 lines
    for (int i = 0; i < 11; i++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            printf("Error: File has fewer than 10 lines.\n");
            return;
        }
    }

    // Count the remaining lines
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    rewind(file);

    // Skip the first 10 lines again
    for (int i = 0; i < 11; i++) {
        fgets(line, sizeof(line), file);
    }

    // Allocate memory for restaurants
    *restaurants = malloc(count * sizeof(Restaurant));

    // Parse the lines into the restaurants array
    count = 0;
    while (fgets(line, sizeof(line), file)) {
        parse_line(line, &(*restaurants)[count]);
        count++;
    }
    *n_rest = count;

    fclose(file);
}

void sort_rests(int by, Restaurant *restaurants, int n_rest) {
    if (by == 1) {
        qsort(restaurants, n_rest, sizeof(Restaurant), compare_by_distance);
    } else if (by == 2) {
        qsort(restaurants, n_rest, sizeof(Restaurant), compare_by_rating);
    }

    for (int i = 0; i < 10; i++) {
        printf("Name: %s\n", restaurants[i].name);
        printf("Rating: %.2f\n", restaurants[i].rating);
        printf("Distance: %.2f km\n", restaurants[i].distance);
        printf("Travel Time: %.2f min\n", restaurants[i].travel_time);
        printf("\n");
    }
}

