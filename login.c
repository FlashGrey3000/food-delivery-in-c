#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "map_functions.c"

#define MAX_LENGTH 100

// Structure definitions
typedef struct {
    char addr1[MAX_LENGTH];
    char addr2[MAX_LENGTH];
    char city[MAX_LENGTH];
    char state[MAX_LENGTH];
    char pinCode[MAX_LENGTH];
    double lattitude;
    double longitude;
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
int user_exists(const char* username);
void get_rest_dists(const double lattitude, const double longitude);

// Function to set text color
void setTextColor(const char* colorCode) {
    printf("%s", colorCode);
}

// Function to reset text color
void resetTextColor() {
    printf("\033[0m");
}

int main() {
    int choice;
    printf("=======================================================================\n");
    printf("=============  Welcome to the Food Delivery Application  ==============\n");
    printf("=======================================================================\n\n");
    while (1) {
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
                printf("\nExiting the application... \n\n");
                exit(0);
            default:
                setTextColor(RED);
                printf("\nInvalid choice. Please try again.\n\n");
                resetTextColor();
        }
    }

    return 0;
}

void registerUser() {
    User newUser;
    FILE* usersFile, * userFile;
    char conf_pass[MAX_LENGTH];
    double lattitude, longitude;

    printf("Enter name: ");
    scanf(" %[^\n]", newUser.name);
    while (1) {
        printf("Enter username: ");
        scanf("%s", newUser.username);

        if (user_exists(newUser.username)==1) {
            setTextColor(YELLOW);
            printf("\n!! Username already taken !!\n");
            resetTextColor();
        } else break;
    }

    while (1) {
        printf("Enter password: ");
        scanf("%s", newUser.password);
        printf("Confirm password: ");
        scanf("%s", conf_pass);

        if (strcmp(newUser.password, conf_pass) == 0) {
            setTextColor(GREEN);
            printf("Passwords match.\n");
            resetTextColor();
            break;
        } else {
            setTextColor(YELLOW);
            printf("Passwords do not match. Please try again.\n");
            resetTextColor();
        }
    } 

    printf("Enter phone number: ");
    scanf("%s", newUser.phone);
    printf("Enter address line 1: ");
    scanf(" %[^\n]", newUser.address.addr1);
    printf("Enter address line 2: ");
    scanf(" %[^\n]", newUser.address.addr2);
    printf("Enter city name: ");
    scanf("%s", newUser.address.city);
    printf("Enter state: ");
    scanf(" %[^\n]", newUser.address.state);
    printf("Enter pin code: ");
    scanf("%s", newUser.address.pinCode);

    update_user_coordinates(newUser.address.addr1, newUser.address.addr2, newUser.address.city, 
                            newUser.address.state, atoi(newUser.address.pinCode), &lattitude, &longitude);

    newUser.address.lattitude = lattitude;
    newUser.address.longitude = longitude;

    // Open the users file in append mode
    usersFile = fopen("users.txt", "a");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Append the new user data to the users file
    fprintf(usersFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf,%lf\n",newUser.name,newUser.username, newUser.password,
                             newUser.phone, newUser.address.addr1, newUser.address.addr2, newUser.address.city, 
                            newUser.address.state, newUser.address.pinCode, newUser.address.lattitude, newUser.address.longitude);
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
    fprintf(userFile, "Address Line 1: %s\n", newUser.address.addr1);
    fprintf(userFile, "Address Line 2: %s\n", newUser.address.addr2);
    fprintf(userFile, "City: %s\n", newUser.address.city);
    fprintf(userFile, "State: %s\n", newUser.address.state);
    fprintf(userFile, "Pin Code: %s\n", newUser.address.pinCode);
    fprintf(userFile, "Lattitude: %lf\n", newUser.address.lattitude);
    fprintf(userFile, "Longitude: %lf\n", newUser.address.longitude);
    fclose(userFile);

    setTextColor(GREEN);
    printf("\n===============User registered successfully!===============\n\n");
    resetTextColor();
}

int user_exists(const char *username) {
    FILE *checkFile;
    int found = 0;
    checkFile = fopen("users.txt", "r");
    if (checkFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Check each line in the users file for matching username
    User user;
    while (fscanf(checkFile, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf", 
                  user.name, user.username, user.password, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude) != EOF) {
        if (strcmp(user.username, username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(checkFile);

    return found;
}

void signIn() {
    char username[MAX_LENGTH], password[MAX_LENGTH];
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
    while (fscanf(usersFile, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf", 
                  user.name, user.username, user.password, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude) != EOF) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(usersFile);

    if (found) {
        printf("=============  Sign in successful  =============\n");
        int userChoice;
        while (1) {
            printf("1. Change Password\n");
            printf("2. Sign Out\n");
            printf("3. Locate Nearby Restaurants\n");
            printf("Enter your choice: ");
            scanf("%d", &userChoice);

            if (userChoice == 1) {
                changePassword(username);
            } else if (userChoice == 2) {
                setTextColor(BLUE);
                printf("\nSigning out...\n\n");
                resetTextColor();
                break;
            } else if (userChoice == 3) {
                get_rest_dists(user.name, user.address.lattitude, user.address.longitude);
            } else {
                setTextColor(YELLOW);
                printf("Invalid choice. Please try again.\n");
                resetTextColor();
            }
        }
    } else {
        printf("\n=============  Error: Incorrect username or password  =============\n\n");
    }
}

void get_rest_dists(const char *username,const double lattitude, const double longitude)
{
    FILE *file, *userFile;
    double rest_lat, rest_long;
    float rating;
    char rest_name[100];
    char line[1024];
    float travelTime, travelDistance;
    
    char userFileName[MAX_LENGTH + 4];
    snprintf(userFileName, sizeof(userFileName), "%s.txt", username);
    userFile = fopen(userFileName, "a");
    file = fopen("city_wise_rests/zomato_chennai.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "%s : %f : %*[^:]: %*[^:]: %*[^:]: %lf : %lf", rest_name, &rating, &rest_lat, &rest_long) == 2) {
            get_distance(&lattitude, &longitude, &rest_lat, &rest_long, &travelDistance, &travelTime);
            fprintf(userFile, "%s: %.2f:%f,%f", rest_name, rating, travelDistance, travelTime);
        } else {
            fprintf(stderr, "Error parsing latitude and longitude from line: %s\n", line);
        }
    }
    fclose(userFile);
    fclose(file);

    return;
}


void changePassword(const char* username) {
    char newPassword[MAX_LENGTH];
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
    while (fscanf(usersFile, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf", 
                  user.name, user.username, user.password, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude) != EOF) {
        if (strcmp(username, user.username) == 0) {
            found = 1;
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf,%lf\n", 
                  user.name, user.username, newPassword, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, user.address.lattitude, user.address.longitude);
        } else {
            fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf,%lf\n", 
                  user.name, user.username, user.password, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, user.address.lattitude, user.address.longitude);
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

        FILE* userFile = fopen(userFileName, "a");
        if (userFile == NULL) {
            perror("Error opening user file");
            exit(1);
        }
        rewind(userFile);

        fprintf(userFile, "Name: %s\n", user.name);
        fprintf(userFile, "Username: %s\n", user.username);
        fprintf(userFile, "Password: %s\n", newPassword);
        fprintf(userFile, "Phone: %s\n", user.phone);
        fprintf(userFile, "Address line 1: %s\n", user.address.addr1);
        fprintf(userFile, "Address line 2: %s\n", user.address.addr2);
        fprintf(userFile, "City: %s\n", user.address.city);
        fprintf(userFile, "State: %s\n", user.address.state);
        fprintf(userFile, "Pin Code: %s\n", user.address.pinCode);
        fprintf(userFile, "Lattitude: %lf\n", user.address.lattitude);
        fprintf(userFile, "Longitude: %lf\n", user.address.longitude);
        fclose(userFile);

        setTextColor(GREEN);
        printf("=============  Password reset successful  =============\n");
        resetTextColor();
    } else {
        remove("temp.txt");
        setTextColor(RED);
        printf("Error: Username not found.\n");
        resetTextColor();
    }
}

