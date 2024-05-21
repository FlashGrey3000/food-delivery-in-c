#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map_functions.c"

// Function to strip the newline character from the input string
void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main() {
    char addr1[100], addr2[100], city[50], state[20];
    int pincode;
    double *latit1 = (double *)malloc(sizeof(double));
    double *longit1 = (double *)malloc(sizeof(double));
    double *latit2 = (double *)malloc(sizeof(double));
    double *longit2 = (double *)malloc(sizeof(double));

    if (latit1 == NULL || longit1 == NULL || latit2 == NULL || longit2 == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the location of user 1----------\n");

    printf("Enter Address Line 1: ");
    fgets(addr1, sizeof(addr1), stdin);
    strip_newline(addr1);

    printf("Enter Address Line 2: ");
    fgets(addr2, sizeof(addr2), stdin);
    strip_newline(addr2);

    printf("Enter City: ");
    fgets(city, sizeof(city), stdin);
    strip_newline(city);

    printf("Enter State Code: ");
    fgets(state, sizeof(state), stdin);
    strip_newline(state);

    printf("Enter Pincode: ");
    scanf("%d", &pincode);
    getchar(); // Clear the newline character left by scanf

    update_user_coordinates(addr1, addr2, city, state, pincode, latit1, longit1);

    printf("Latitude: %lf\n", *latit1);
    printf("Longitude: %lf\n", *longit1);

    printf("Enter the location of user 2----------\n");

    printf("Enter Address Line 1: ");
    getchar(); // Clear the newline character left in the buffer
    fgets(addr1, sizeof(addr1), stdin);
    strip_newline(addr1);

    printf("Enter Address Line 2: ");
    fgets(addr2, sizeof(addr2), stdin);
    strip_newline(addr2);

    printf("Enter City: ");
    fgets(city, sizeof(city), stdin);
    strip_newline(city);

    printf("Enter State Code: ");
    fgets(state, sizeof(state), stdin);
    strip_newline(state);

    printf("Enter Pincode: ");
    scanf("%d", &pincode);
    getchar(); // Clear the newline character left by scanf

    update_user_coordinates(addr1, addr2, city, state, pincode, latit2, longit2);

    printf("Latitude: %lf\n", *latit2);
    printf("Longitude: %lf\n", *longit2);

    get_distance(latit1, longit1, latit2, longit2);

    free(latit1);
    free(longit1);
    free(latit2);
    free(longit2);

    return 0;
}
