#include <stdio.h>
#include <string.h>

typedef struct {
    char rest_name[50];
    char food_name[50];
    int quantity;
    int price;
    int total;
} cart;

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

void print_cart(const cart *row) {
    printf("%s %s %s %s %s %s\n","S.No.:" , "Restaurant", "Food", "Quantity", "Price", "Total");
    for (int i = 0; i < sizeof(row); i++) {
        if (row[i].food_name[0] != '\0') {
            printf(" %d    %s     %s     %d    %d     %d\n", i+1, row[i].rest_name, row[i].food_name, row[i].quantity, row[i].price, row[i].total);
        }
    }
}

void remove_cart(cart *row, const char food_name[]) {
    print_cart(row);
    for (int i = 0; i < 100; i++) {
        if (strcmp(row[i].food_name, food_name) == 0) {
            for (int j = i; j < 99; j++) {
                strcpy(row[j].rest_name, row[j + 1].rest_name);
                strcpy(row[j].food_name, row[j + 1].food_name);
                row[j].quantity = row[j + 1].quantity;
                row[j].price = row[j + 1].price;
                row[j].total = row[j + 1].total;
            }
        }
    }
}


int main() {
    char rest[] = "abc"; // selected restaurant
    cart row[100];
    char food[50];

    while (1) {
        int choice;
        // Let's give 3 options: 1. Add to cart, 2. Remove from cart, 3. Print cart
        printf("0. Exit\n1. Add to cart\n2. Remove from cart\n3. Print cart\nEnter your option: ");
        scanf("%d", &choice);

        switch (choice) {
            int price, i = 0;
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
                        add_cart(row, i, rest, food, price);
                        i++;
                    }
                }
                break;
            case 2:
                printf("Enter food to remove: ");
                scanf("%s", food);
                remove_cart(row, food);
                break;
            case 3:
                print_cart(row);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
