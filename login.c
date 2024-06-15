#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "map_functions.c"
#include "weatherer.c"
#include "sorting.c"
#include "search.c"


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
    int user_is_loaded;
} User;


void registerUser();
void signIn();
void changePassword(const char* username);
int user_exists(const char* username);
void get_rest_dists(const char *username, const double lattitude, const double longitude);



void setTextColor(const char* colorCode) {
    printf("%s", colorCode);
}


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
                setTextColor(BLUE);
                printf("\nExiting the application... \n\n");
                resetTextColor();
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
            printf("Passwords do not match. Please try again.\nEnter Again\n\n");
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
    newUser.user_is_loaded = 0;
    

    
    usersFile = fopen("db/users.txt", "a");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    
    fprintf(usersFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf,%lf,%d\n",newUser.name,newUser.username, newUser.password,
                             newUser.phone, newUser.address.addr1, newUser.address.addr2, newUser.address.city, 
                            newUser.address.state, newUser.address.pinCode, newUser.address.lattitude, newUser.address.longitude,newUser.user_is_loaded);
    fclose(usersFile);

    char userFileName[MAX_LENGTH + 12];
    snprintf(userFileName, sizeof(userFileName), "db/user/%s.txt", newUser.username);

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
    fprintf(userFile, "Loaded: %d\n", newUser.user_is_loaded);
    fclose(userFile);

    setTextColor(GREEN);
    printf("\n===============User registered successfully!===============\n\n");
    resetTextColor();
}

int user_exists(const char *username) {
    FILE *checkFile;
    int found = 0;
    checkFile = fopen("db/users.txt", "r");
    if (checkFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Check each line in the users file for matching username
    User user;
    while (fscanf(checkFile, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf,%d", 
                  user.name, user.username, user.password, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude, &user.user_is_loaded) != EOF) {
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

    
    usersFile = fopen("db/users.txt", "r");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Check each line in the users file for matching username and password
    User user;
    while (fscanf(usersFile, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf,%d", 
                  user.name, user.username, user.password, user.phone, 
                  user.address.addr1, user.address.addr2, user.address.city, 
                  user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude, &user.user_is_loaded) != EOF) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(usersFile);

    if (found) {
        setTextColor(GREEN);
        printf("\n=============  Sign in successful  =============\n\n");
        resetTextColor();
        int userChoice;
        Restaurant *restaurants = NULL;
        int n_rest = 0;
        get_rest_dists(username, user.address.lattitude, user.address.longitude);

        store_rests(username, &restaurants, &n_rest);
        while (1) {
            printf("1. Change Password\n");
            printf("2. Show Restaurants\n");
            printf("3. Search\n");
            printf("4. Sign Out\n");
            printf("Enter your choice: ");
            scanf("%d", &userChoice);

            if (userChoice == 1) {
                changePassword(username);
            } else if (userChoice == 4) {
                setTextColor(BLUE);
                printf("\nSigning out...\n\n");
                resetTextColor();
                break;
            } else if (userChoice == 2) {
                while (1) {
                    printf("By which parameter to sort by:-\n");
                    printf("1. Sort by Distance\n");
                    printf("2. Sort by Rating\n");
                    printf("3. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &userChoice);

                    if (userChoice==1) sort_rests(1, restaurants, n_rest);
                    else if (userChoice==2) sort_rests(2, restaurants, n_rest);
                    else if (userChoice==3) break;
                    else {
                        setTextColor(YELLOW);
                        printf("Invalid choice. Please try again.\n");
                        resetTextColor();
                    }
                    
                }
            } else if (userChoice == 3) {
                while(1) {
                    printf("\nWhat do you want to search for- \n");
                    printf("1. Restaurants\n");
                    printf("2. Food\n");
                    printf("Enter your choice: ");
                    scanf("%d", &userChoice);
                    char search_string[30];
                    if (userChoice==1) {
                        printf("Enter restaurant name: ");
                        getchar();
                        fgets(search_string, sizeof(search_string), stdin);
                        search_string[strlen(search_string)]='\0';
                        search_rest(search_string);
                    }
                    else if (userChoice==2) {
                        printf("Enter food name: ");
                        getchar();
                        fgets(search_string, sizeof(search_string), stdin);
                        search_string[strlen(search_string)]='\0';
                        search_food(search_string);
                    }
                    else {
                        setTextColor(YELLOW);
                        printf("Invalid option. Try again.");
                        resetTextColor();
                    }
                }
            } else {
                setTextColor(YELLOW);
                printf("Invalid choice. Please try again.\n");
                resetTextColor();
            }
        }
    } else {
        setTextColor(YELLOW);
        printf("\n=============  Error: Incorrect username or password  =============\n\n");
        resetTextColor();
    }
}

void get_rest_dists(const char *username, const double latitude, const double longitude) {
    FILE *file, *userFile;
    double rest_lat, rest_long;
    float rating;
    char rest_name[MAX_LENGTH];
    char line[1024];
    float travelTime, travelDistance;

    char userFileName[MAX_LENGTH + 12];
    snprintf(userFileName, sizeof(userFileName), "db/user/%s.txt", username);
    userFile = fopen(userFileName, "a");
    if (userFile == NULL) {
        perror("Error opening user file");
        exit(1);
    }

    file = fopen("city_wise_rests/zomato_chennai.txt", "r");
    if (file == NULL) {
        perror("Error opening restaurant file");
        fclose(userFile);
        exit(1);
    }

    int count = 0;

    while ((fgets(line, sizeof(line), file) != NULL) && count<50) {
        count++;
        if (sscanf(line, "%[^:]: %f :%*[^:]:%*[^:]:%*[^:]: %lf : %lf", rest_name, &rating, &rest_lat, &rest_long) == 4) {
            get_distance(latitude, longitude, rest_lat, rest_long, &travelDistance, &travelTime);
            if (travelDistance >= 0 && travelTime >= 0) { // Ensure valid distances and times
                fprintf(userFile, "%s: %.2f: Distance: %.2f km, Travel time: %.2f min\n", rest_name, rating, travelDistance, travelTime);
            } else {
                fprintf(stderr, "Error retrieving distance or time for %s\n", rest_name);
            }
        } else {
            fprintf(stderr, "Error parsing latitude and longitude from line: %s\n", line);
        }
    }

    fclose(file);
    fclose(userFile);
}

void changePassword(const char* username) {
    char newPassword[MAX_LENGTH];
    char confPassword[MAX_LENGTH];
    FILE *file, *tempFile;
    char line[1024];
    int found = 0;

    printf("Enter new password: ");
    scanf("%s", newPassword);
    printf("Confirm new password: ");
    scanf("%s", confPassword);

    if (strcmp(newPassword, confPassword) != 0) {
        setTextColor(RED);
        printf("Passwords do not match. Please try again.\n");
        resetTextColor();
        return;
    }

    file = fopen("db/users.txt", "r");
    if (file == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    tempFile = fopen("db/temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp.txt");
        fclose(file);
        exit(1);
    }

    User user;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf,%d", 
               user.name, user.username, user.password, user.phone, 
               user.address.addr1, user.address.addr2, user.address.city, 
               user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude, &user.user_is_loaded);

        if (strcmp(user.username, username) == 0) {
            strcpy(user.password, newPassword);
            found = 1;
        }

        fprintf(tempFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf,%lf\n",
                user.name, user.username, user.password, user.phone,
                user.address.addr1, user.address.addr2, user.address.city,
                user.address.state, user.address.pinCode, user.address.lattitude, user.address.longitude);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("db/users.txt");
        rename("db/temp.txt", "db/users.txt");
        setTextColor(GREEN);
        printf("Password changed successfully.\n");
        resetTextColor();
    } else {
        remove("db/temp.txt");
        setTextColor(RED);
        printf("Error: Username not found.\n");
        resetTextColor();
    }
}