#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char housenum[10];
    char street[15];
    char area[20];
    int pin;
    int phone;
    char password[50];
} User;

void save_user(User user) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fprintf(file, "%s,%s,%s,%s,%d,%d,%s\n", user.username, user.housenum, user.street, user.area, user.pin, user.phone, user.password);
    fclose(file);
}

int load_users(User users[]) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return 0;
    }
    int count = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%d,%s\n", users[count].username, users[count].housenum, users[count].street, users[count].area, &users[count].pin, &users[count].phone, users[count].password) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

int user_exists(const char *username, User users[], int user_count) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void signup() {//for new user
    char username[50];
    char housenum[10];
    char street[15];
    char area[20];
    int pin;
    int phone;
    char password[50];

    printf("Enter a username(without space): ");
    scanf("%s", username);
     User users[100];
    int  user_count = load_users(users);

    if (user_exists(username, users, user_count)) {
        printf("Username already exists. Please choose a different username.\n");
        return;
    }
    User new_user;

    strcpy(new_user.username, username);

    printf("Enter a password: ");
    scanf("%s", password);
    printf("Enter phone no. :");
    scanf("%d",&phone);
   fgets(new_user.housenum, sizeof(new_user.housenum), stdin);
    printf("Enter house number: ");
    fgets(new_user.housenum, sizeof(new_user.housenum), stdin);
    new_user.housenum[strcspn(new_user.housenum, "\n")] = '\0';

    printf("Enter street name: ");
    fgets(new_user.street, sizeof(new_user.street), stdin);
    new_user.street[strcspn(new_user.street, "\n")] = '\0';

    printf("Enter your area where you live: ");
    fgets(new_user.area, sizeof(new_user.area), stdin);
    new_user.area[strcspn(new_user.area, "\n")] = '\0';

    printf("Enter pin code :");
    scanf("%d", &pin);


    new_user.phone=phone;
    new_user.pin=pin;
    strcpy(new_user.password, password);
    save_user(new_user);
    printf("Signup successful!\n");
}

void login() {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    User users[100];
    int user_count = load_users(users);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return;
        }
    }
    printf("Invalid username or password.\n");
}

int main() {
    while (1) {//used while
        char choice;
        printf("Enter your option :\n1.Signup.\n2.Login. or 'q' to quit : ");
        scanf(" %c", &choice);
        if (choice == '1') {
            signup();
        } else if (choice == '2') {
            login();
        } else if (choice == 'q' || choice == 'Q') {
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
