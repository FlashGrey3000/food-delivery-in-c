#include <stdio.h>
#include <string.h>

#define MAX_FOOD_ITEMS 10
#define MAX_USERS 5

typedef struct {
    char name[50];
    char type[20];
    char cuisine[20];
} FoodItem;

typedef struct {
    char username[50];
    char preferredType[20];
    char preferredCuisine[20];
} UserPreference;

void recommendFood(FoodItem items[], int itemCount, UserPreference user) {
    printf("Recommended food for %s:\n", user.username);
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].type, user.preferredType) == 0 && strcmp(items[i].cuisine, user.preferredCuisine) == 0) {
            printf("- %s\n", items[i].name);
        }
    }
}

int main() {
    FoodItem menu[MAX_FOOD_ITEMS] = {
        {"Pasta", "vegetarian", "Italian"},
        {"Chicken Curry", "non-vegetarian", "Indian"},
        {"Paneer Tikka", "vegetarian", "Indian"},
        {"Pizza", "vegetarian", "Italian"},
        // Add more items
    };

    UserPreference users[MAX_USERS] = {
        {"Alice", "vegetarian", "Italian"},
        {"Bob", "non-vegetarian", "Indian"},
        // Add more users
    };

    char username[50];
    printf("Enter your username: ");
    scanf("%s", username);

    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0) {
            recommendFood(menu, MAX_FOOD_ITEMS, users[i]);
            break;
        }
    }

    return 0;
}
