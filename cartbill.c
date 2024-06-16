#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CART_SIZE 12
#define MAX_RESTAURANTS 30

typedef struct {
    char rest_name[50];
    char food_name[50];
    int quantity;
    int price;
    int total;
} cart;

typedef struct {
    char rest_name[50];
    float rating;
    int total_ratings;
} restaurant;

// Function prototypes
void add_cart(cart *row, int *size, const char rest_name[], const char food_name[], int price);
void print_cart(const cart *row, int size);
void remove_cart(cart *row, int *size, const char food_name[]);
void update_ratings(const char rest_name[], float user_rating);
void write_transaction(const cart *row, int size);

int main() {
    const char rest[50] = "Sample Restaurant";  // Sample restaurant name
    cart row[MAX_CART_SIZE];
    int size = 0;

    while (1) {
        int choice;
        printf("\n0. Exit\n1. Add to cart\n2. Remove from cart\n3. Print cart\nEnter your option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting program...\n");
                return 0;
            case 1: {
                char food[50];
                int price;

                printf("Enter food to add ('q' to exit): ");
                scanf("%s", food);
                if (food[0] == 'q' || food[0] == 'Q')
                    break;

                printf("Enter price: ");
                scanf("%d", &price);

                add_cart(row, &size, rest, food, price);
                break;
            }
            case 2: {
                if (size == 0) {
                    printf("Cart is empty.\n");
                    break;
                }

                char food[50];
                printf("Enter food to remove: ");
                scanf("%s", food);

                remove_cart(row, &size, food);
                break;
            }
            case 3:
                if (size == 0) {
                    printf("Cart is empty.\n");
                } else {
                    print_cart(row, size);
                    int user_rating;
                    printf("Enter your star rating (1-5) for this order: ");
                    scanf("%d", &user_rating);
                    update_ratings(rest, user_rating);
                    write_transaction(row, size);
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_cart(cart *row, int *size, const char rest_name[], const char food_name[], int price) {
    if (*size >= MAX_CART_SIZE) {
        printf("Cart is full. Cannot add more items.\n");
        return;
    }

    int quantity;
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    strcpy(row[*size].rest_name, rest_name);
    strcpy(row[*size].food_name, food_name);
    row[*size].quantity = quantity;
    row[*size].price = price;
    row[*size].total = quantity * price;

    (*size)++;

    printf("Item added to cart.\n");
}

void print_cart(const cart *row, int size) {
    printf("\n%-6s %-20s %-20s %-10s %-10s %-10s\n", "S.No.", "Restaurant", "Food", "Quantity", "Price", "Total");
    int totalSum = 0;
    for (int i = 0; i < size; i++) {
        printf("%-6d %-20s %-20s %-10d %-10d %-10d\n", i + 1, row[i].rest_name, row[i].food_name, row[i].quantity, row[i].price, row[i].total);
        totalSum += row[i].total;
    }
    printf("\nTotal Bill: Rs.%d\n", totalSum);
}

void remove_cart(cart *row, int *size, const char food_name[]) {
    int found = 0;
    for (int i = 0; i < *size; i++) {
        if (strcmp(row[i].food_name, food_name) == 0) {
            found = 1;
            for (int j = i; j < *size - 1; j++) {
                strcpy(row[j].rest_name, row[j + 1].rest_name);
                strcpy(row[j].food_name, row[j + 1].food_name);
                row[j].quantity = row[j + 1].quantity;
                row[j].price = row[j + 1].price;
                row[j].total = row[j + 1].total;
            }
            (*size)--;
            printf("Item removed from cart.\n");
            break;
        }
    }
    if (!found) {
        printf("Food item not found in the cart.\n");
    }
}

void update_ratings(const char rest_name[], float user_rating) {
    FILE *file = fopen("city_wise_rests/zomato_chennai.txt", "r+");
    if (file) {
        char line[256];  // Assuming lines are not longer than 256 characters
        restaurant ratings[100];
        int numRestaurants = 0;
        int found = 0;

        // Read and update ratings
        while (fgets(line, sizeof(line), file)) {
            // Parse the line
            char *token = strtok(line, " :");
            strcpy(ratings[numRestaurants].rest_name, token);  // Restaurant name

            // Skip over other tokens until we find the rating
            for (int i = 0; i < 4; ++i) {
                token = strtok(NULL, " :");
            }

            // Read and update rating
            ratings[numRestaurants].rating = atof(token);
            ratings[numRestaurants].total_ratings = atoi(strtok(NULL, " ,"));

            // Update the rating if restaurant name matches
            if (strcmp(ratings[numRestaurants].rest_name, rest_name) == 0) {
                ratings[numRestaurants].rating = (ratings[numRestaurants].rating * ratings[numRestaurants].total_ratings + user_rating) / (ratings[numRestaurants].total_ratings + 1);
                ratings[numRestaurants].total_ratings++;
                found = 1;
            }

            numRestaurants++;
        }

        // Write updated ratings back to file
        fclose(file);
        file = fopen("city_wise_rests/zomato_chennai.txt", "w");
        if (file) {
            for (int r = 0; r < numRestaurants; r++) {
                fprintf(file, "%s : %.1f : North Indian, Kebab, Biryani, Mughlai : ₹2,500 for two : %d, %d, Upper Ground Floor, Phoenix Market City, Velachery Main Road, Velachery, Chennai, Tamil Nadu : 12.98855655 : 80.22197565 : 39\n",
                        ratings[r].rest_name, ratings[r].rating, ratings[r].total_ratings, ratings[r].total_ratings);
            }
            fclose(file);
        } else {
            printf("Error: Cannot open zomato_chennai.txt for writing.\n");
        }

        if (found) {
            printf("Rating updated successfully for %s.\n", rest_name);
        } else {
            printf("Restaurant '%s' not found.\n", rest_name);
        }
    } else {
        printf("Error: Cannot open zomato_chennai.txt for rating update.\n");
    }
}

void write_transaction(const cart *row, int size) {
    FILE *f = fopen("transactions.txt", "a");
    if (f == NULL) {
        printf("Error: Cannot open transactions.txt for writing.\n");
        return;
    }

    fprintf(f, "\n%-6s %-20s %-20s %-10s %-10s %-10s\n", "S.No.", "Restaurant", "Food", "Quantity", "Price", "Total");
    for (int i = 0; i < size; i++) {
        fprintf(f, "%-6d %-20s %-20s %-10d %-10d %-10d\n", i + 1, row[i].rest_name, row[i].food_name, row[i].quantity, row[i].price, row[i].total);
    }

    fclose(f);
}
