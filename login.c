#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Structure definitions
typedef struct {
    char street[MAX_LENGTH];
    char city[MAX_LENGTH];
    char state[MAX_LENGTH];
    char pinCode[MAX_LENGTH];
} Address;

typedef struct {
    char name[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char phone[MAX_LENGTH];
    Address address;
} User;

// Function prototypes
void registerUser();
void signIn();
void changePassword(const char* username);

int main() {
    int choice;

    while (1) {
        printf("Welcome to the Food Delivery Application\n");
        printf("1. Register\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                signIn();
                break;
            case 3:
                printf("Exiting the application.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void registerUser() {
    User newUser;
    FILE* usersFile, * userFile;

    printf("Enter name: ");
    scanf(" %[^\n]", newUser.name);
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    printf("Enter phone number: ");
    scanf("%s", newUser.phone);
    printf("Enter street name: ");
    scanf(" %[^\n]", newUser.address.street);
    printf("Enter city name: ");
    scanf("%s", newUser.address.city);
    printf("Enter state: ");
    scanf(" %[^\n]", newUser.address.state);
    printf("Enter pin code: ");
    scanf("%s", newUser.address.pinCode);

    // Open the users file in append mode
    usersFile = fopen("users.txt", "a");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Append the new user data to the users file
    fprintf(usersFile, "%s %s %s %s %s %s %s %s\n", 
            newUser.name, newUser.username, newUser.password, newUser.phone, 
            newUser.address.street, newUser.address.city, 
            newUser.address.state, newUser.address.pinCode);
    fclose(usersFile);

    // Create a new file for the user with the username as the filename
    char userFileName[MAX_LENGTH + 4];
    snprintf(userFileName, sizeof(userFileName), "%s.txt", newUser.username);

    userFile = fopen(userFileName, "w");
    if (userFile == NULL) {
        perror("Error creating user file");
        exit(1);
    }

    // Write the user's details to the user-specific file
    fprintf(userFile, "Name: %s\n", newUser.name);
    fprintf(userFile, "Username: %s\n", newUser.username);
    fprintf(userFile, "Password: %s\n", newUser.password);
    fprintf(userFile, "Phone: %s\n", newUser.phone);
    fprintf(userFile, "Street: %s\n", newUser.address.street);
    fprintf(userFile, "City: %s\n", newUser.address.city);
    fprintf(userFile, "State: %s\n", newUser.address.state);
    fprintf(userFile, "Pin Code: %s\n", newUser.address.pinCode);
    fclose(userFile);

    printf("User registered successfully!\n");
}

void signIn() {
    char username[MAX_LENGTH], password[MAX_LENGTH];
    char storedUsername[MAX_LENGTH], storedPassword[MAX_LENGTH];
    FILE* usersFile;
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Open the users file in read mode
    usersFile = fopen("users.txt", "r");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Check each line in the users file for matching username and password
    User user;
    while (fscanf(usersFile, "%s %s %s %s %s %s %s %s", 
                  user.name, storedUsername, storedPassword, user.phone, 
                  user.address.street, user.address.city, 
                  user.address.state, user.address.pinCode) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            found = 1;
            break;
        }
    }

    fclose(usersFile);

    if (found) {
        printf("Sign in successful!\n");
        int userChoice;
        while (1) {
            printf("1. Change Password\n");
            printf("2. Sign Out\n");
            printf("Enter your choice: ");
            scanf("%d", &userChoice);

            if (userChoice == 1) {
                changePassword(username);
            } else if (userChoice == 2) {
                printf("Signing out...\n");
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("Error: Incorrect username or password.\n");
    }
}

void changePassword(const char* username) {
    char newPassword[MAX_LENGTH];
    char storedUsername[MAX_LENGTH];
    User user;
    FILE* usersFile, * tempFile;
    int found = 0;

    printf("Enter your new password: ");
    scanf("%s", newPassword);

    // Open the users file in read mode
    usersFile = fopen("users.txt", "r");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Open a temporary file to write updated data
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp.txt");
        fclose(usersFile);
        exit(1);
    }

    // Check each line in the users file for the matching username
    while (fscanf(usersFile, "%s %s %s %s %s %s %s %s", 
                  user.name, storedUsername, user.password, user.phone, 
                  user.address.street, user.address.city, 
                  user.address.state, user.address.pinCode) != EOF) {
        if (strcmp(username, storedUsername) == 0) {
            found = 1;
            fprintf(tempFile, "%s %s %s %s %s %s %s %s\n", 
                    user.name, storedUsername, newPassword, user.phone, 
                    user.address.street, user.address.city, 
                    user.address.state, user.address.pinCode);
        } else {
            fprintf(tempFile, "%s %s %s %s %s %s %s %s\n", 
                    user.name, storedUsername, user.password, user.phone, 
                    user.address.street, user.address.city, 
                    user.address.state, user.address.pinCode);
        }
    }

    fclose(usersFile);
    fclose(tempFile);

    if (found) {
        // Rename temp file to users.txt
        if (remove("users.txt") != 0) {
            perror("Error deleting original users.txt");
            exit(1);
        }
        if (rename("temp.txt", "users.txt") != 0) {
            perror("Error renaming temp.txt to users.txt");
            exit(1);
        }

        // Update the user's individual file with the new password
        char userFileName[MAX_LENGTH + 4];
        snprintf(userFileName, sizeof(userFileName), "%s.txt", username);

        FILE* userFile = fopen(userFileName, "w");
        if (userFile == NULL) {
            perror("Error opening user file");
            exit(1);
        }

        fprintf(userFile, "Name: %s\n", user.name);
        fprintf(userFile, "Username: %s\n", storedUsername);
        fprintf(userFile, "Password: %s\n", newPassword);
        fprintf(userFile, "Phone: %s\n", user.phone);
        fprintf(userFile, "Street: %s\n", user.address.street);
        fprintf(userFile, "City: %s\n", user.address.city);
        fprintf(userFile, "State: %s\n", user.address.state);
        fprintf(userFile, "Pin Code: %s\n", user.address.pinCode);
        fclose(userFile);

        printf("Password reset successful!\n");
    } else {
        remove("temp.txt");  // Cleanup temporary file if user not found
        printf("Error: Username not found.\n");
    }
}
