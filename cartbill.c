#include <stdio.h>
#include <string.h>

typedef struct {
    char rest_name[50];
    char food_name[50];
    int quantity;
    int price;
    int total;
} cart;

typedef struct {
    char rest_name[50];
    int rating;
    int total_ratings;
} restaurant;

void add_cart(cart *row, int i, const char rest_name[], const char food_name[], float price) {
    int quantity;
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    strcpy(row[i].rest_name, rest_name);
    strcpy(row[i].food_name, food_name);
    row[i].quantity = quantity;
    row[i].price = price;
    row[i].total = quantity * price;
}

void print_cart(const cart *row, int size) {
    printf("%-6s %-20s %-20s %-10s %-10s %-10s\n", "S.No.", "Restaurant", "Food", "Quantity", "Price", "Total");
    int totalSum = 0; 
    for (int i = 0; i < size; i++) {
        if (row[i].food_name[0] != '\0') {
            printf("%-6d %-20s %-20s %-10d %-10d %-10d\n", i + 1, row[i].rest_name, row[i].food_name, row[i].quantity, row[i].price, row[i].total);
            totalSum += row[i].total; 
        }
    }
      printf("\nTotal Bill: Rs.%d\n", totalSum);
}

void remove_cart(cart *row, const char food_name[], int *size) {
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
            break;
        }
    }
    if (!found) {
        printf("Food item not found in the cart.\n");
    }
} 

void update_ratings(const char rest_name[], int user_rating) {
    FILE *file = fopen("restaurant.csv", "r+");
    if (file) {
        restaurant ratings[100];
        int numRestaurants = 0;
        while (fscanf(file, "%49[^,],%d,%d\n", ratings[numRestaurants].rest_name, &ratings[numRestaurants].rating, &ratings[numRestaurants].total_ratings) == 3) {
            if (strcmp(ratings[numRestaurants].rest_name, rest_name) == 0) {
                ratings[numRestaurants].rating = (ratings[numRestaurants].rating * ratings[numRestaurants].total_ratings + user_rating) / (ratings[numRestaurants].total_ratings + 1);
                ratings[numRestaurants].total_ratings++;
            }
            numRestaurants++;
        }
        fseek(file, 0, SEEK_SET);
        for (int r = 0; r < numRestaurants; r++) {
            fprintf(file, "%s,%d,%d,%d\n", ratings[r].rest_name, ratings[r].rating, ratings[r].total_ratings, user_rating);
        }
        fclose(file);
    }
}

int main() {
    const char rest[50];
    char food[30];
    cart row[10];

    int size = 3;

    while (1) {
        int choice, price, i = size;
        printf("0. Exit\n1. Add to cart\n2. Remove from cart\n3. Print cart\nEnter your option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return 0;
            case 1:
                while (1) {
                    printf("Enter 'q' to exit.\nEnter food: ");
                    scanf("%s", food);
                    if (food[0] == 'q' || food[0] == 'Q')
                        break;
                    else {
                        printf("Enter price: ");
                        scanf("%d", &price);
                        add_cart(row, size, rest, food, price);
                        size++;
                    }
                }
                break;
            case 2:
                printf("Enter food to remove: ");
                scanf("%s", food);
                remove_cart(row, food, &size);
                size--;
                break;
            case 3:
                print_cart(row, size);
                int user_rating;
                printf("Enter your star rating (1-5) for this order: ");
                scanf("%d", &user_rating);
                update_ratings(rest, user_rating);
                break;
             default:
                printf("Invalid choice. Please try again.\n");
    }
    return 0;
}
}
