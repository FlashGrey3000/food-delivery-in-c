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
    char name[100];
    float rating, distance, travel_time;
    sscanf(line, "%[^:]: %f: Distance: %f km, Travel time: %f min", name, &rating, &distance, &travel_time);
    strcpy(restaurant->name, name);
    restaurant->rating = rating;
    restaurant->distance = distance;
    restaurant->travel_time = travel_time;
}

int compare_by_distance(const void *a, const void *b) {
    float distA = ((Restaurant *)a)->distance;
    float distB = ((Restaurant *)b)->distance;
    if (distA < distB) return -1;
    if (distA > distB) return 1;
    return 0;
}

int compare_by_rating(const void *a, const void *b) {
    float ratA = ((Restaurant *)a)->rating;
    float ratB = ((Restaurant *)b)->rating;
    if (ratA < ratB) return -1;
    if (ratA > ratB) return 1;
    return 0;
}

void store_rests(const char *username, const int n_rest) {
    char filename[112];
    sprintf(filename, "db/user/%s.txt", username);
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    Restaurant restaurants[n_rest];
    int count = 0;
    char line[512];

    for (int i = 0; i < 11; i++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            printf("Error: File has fewer than 10 lines.\n");
            return;
        }
    }

    while (fgets(line, sizeof(line), file)) {
        parse_line(line, &restaurants[count]);
        count++;
    }

    fclose(file);

    // Sort the restaurants based on distance
    qsort(restaurants, count, sizeof(Restaurant), compare_by_distance);

    for (int i = 0; i < n_rest; i++) {
        printf("Name: %s\n", restaurants[i].name);
        printf("Rating: %.2f\n", restaurants[i].rating);
        printf("Distance: %.2f km\n", restaurants[i].distance);
        printf("Travel Time: %.2f min\n", restaurants[i].travel_time);
        printf("\n");
        
    }
}