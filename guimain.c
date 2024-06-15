#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "map_functions.c"

#define MAX_LENGTH 100

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
int user_exists(const char* username);
void setTextColor(const char* colorCode);
void resetTextColor();
void show_message_dialog(GtkWindow *parent, const char *message);
void on_register_clicked(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);
void activate_reg(GtkWidget *widget, gpointer data);
void print_hello(GtkWidget *widget, gpointer data);
void destroy_Window(GtkWidget *widget, gpointer data);

static GtkWidget *name_entry, *username_entry, *password_entry, *phone_entry;
static GtkWidget *addr1_entry, *addr2_entry, *city_entry, *state_entry, *pinCode_entry;
static GtkWidget *latitude_entry, *longitude_entry, *conform_password_entry;


// void show_new_buttons(GtkWidget *window) {
//     GtkWidget *new_box;
//     GtkWidget *new_button1;
//     GtkWidget *new_button2;

//     new_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
//     gtk_widget_set_halign(new_box, GTK_ALIGN_CENTER);
//     gtk_widget_set_valign(new_box, GTK_ALIGN_CENTER);

//     new_button1 = gtk_button_new_with_label("NEW BUTTON 1");
//     new_button2 = gtk_button_new_with_label("NEW BUTTON 2");

//     g_signal_connect(new_button1, "clicked", G_CALLBACK(print_hello), NULL);
//     g_signal_connect(new_button2, "clicked", G_CALLBACK(print_hello), NULL);

//     gtk_box_append(GTK_BOX(new_box), new_button1);
//     gtk_box_append(GTK_BOX(new_box), new_button2);

//     gtk_window_set_child(GTK_WINDOW(window), new_box);
// }

void search_by_food(GtkWidget *widget, gpointer data) {
    




}


void active_options(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *grid;

    GtkApplication *app = GTK_APPLICATION(data);
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "SORTING");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW));

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 7);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    button1 = gtk_button_new_with_label("1. Search by food");
    button2 = gtk_button_new_with_label("2. Show Restaurant");
    button3 = gtk_button_new_with_label("3. Change Password");
    button4 = gtk_button_new_with_label("4. Sign Out");

    g_signal_connect(button1, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(print_hello), window);
    g_signal_connect(button3, "clicked", G_CALLBACK(print_hello), window);
    g_signal_connect(button4, "clicked", G_CALLBACK(destroy_Window), window);

    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button4, 0, 6, 1, 1);

    gtk_widget_set_visible(button1, TRUE);
    gtk_widget_set_visible(button2, TRUE);
    gtk_widget_set_visible(button3, TRUE);
    gtk_widget_set_visible(button4, TRUE);

    gtk_window_present(GTK_WINDOW(window));    
}


void on_login_clicked(GtkWidget *widget, gpointer data) {
    FILE *usersFile;
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW));
    GtkWidget *Next_button;
    GtkWidget *grid = GTK_WIDGET(data);
    GtkApplication *app = gtk_window_get_application(parent_window);


    
    // Create a new window for the grid
    //window = gtk_window_new();

    // grid = gtk_grid_new();
    // gtk_grid_set_row_spacing(GTK_GRID(grid), 7);
    // gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    // gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    // gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    //gtk_window_set_child(GTK_WINDOW(window), grid);

    int found = 0;

    const char *username = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_entry)));
    const char *password = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_entry)));
    
    // Open the users file in read mode
    usersFile = fopen("db/users.txt", "r");
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
        Next_button = gtk_button_new_with_label("Next-->");
        g_signal_connect(Next_button, "clicked", G_CALLBACK(active_options), app);
        gtk_grid_attach(GTK_GRID(grid), Next_button, 2, 7, 1, 1);

        gtk_widget_set_visible(Next_button, TRUE); //make the button pop-up 

        } else {
            
        g_print("\n=============  Error: Incorrect username or password  =============\n\n");

        char *message = "User Name & Passwords do not match.\n Please try again.";
        show_message_dialog(parent_window, message);
        }
}

void on_register_clicked(GtkWidget *widget, gpointer data) {
    User newUser;
    FILE *usersFile, *userFile;
    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW));
    double lattitude, longitude;

    const char *name = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(name_entry)));
    const char *username;

    // Check if the username is already taken
    //while (1) {
        username = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_entry)));
        if (user_exists(username) == 1) {
            const char *message = "User Name Alredy taken!!";
            GtkWindow *popup_window = GTK_WINDOW(data);
            show_message_dialog(popup_window, message);
            return;
        } else {
                        //break;
        }
    //}

    const char *password;
    while (1) {
        password = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_entry)));
        const char *conf_pass = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(conform_password_entry)));

        if (strcmp(password, conf_pass) == 0) {
            break;
        } else {
            const char *message = "Passwords do not match. Please try again.";
            GtkWindow *popup_window = GTK_WINDOW(data);
            show_message_dialog(popup_window, message);
        }
    }

    const char *phone = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(phone_entry)));
    const char *addr1 = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(addr1_entry)));
    const char *addr2 = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(addr2_entry)));
    const char *city = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(city_entry)));
    const char *state = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(state_entry)));
    const char *pinCode = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(pinCode_entry)));

    strncpy(newUser.name, name, MAX_LENGTH);
    strncpy(newUser.username, username, MAX_LENGTH);
    strncpy(newUser.password, password, MAX_LENGTH);
    strncpy(newUser.phone, phone, MAX_LENGTH);
    strncpy(newUser.address.addr1, addr1, MAX_LENGTH);
    strncpy(newUser.address.addr2, addr2, MAX_LENGTH);
    strncpy(newUser.address.city, city, MAX_LENGTH);
    strncpy(newUser.address.state, state, MAX_LENGTH);
    strncpy(newUser.address.pinCode, pinCode, MAX_LENGTH);


    update_user_coordinates(newUser.address.addr1, newUser.address.addr2, newUser.address.city,
                            newUser.address.state, atoi(newUser.address.pinCode), &lattitude, &longitude);

    newUser.address.lattitude = lattitude;
    newUser.address.longitude = longitude;


    g_print("User Registered:\nName: %s\nUsername: %s\nPassword: %s\nPhone: %s\n",
            newUser.name, newUser.username, newUser.password, newUser.phone);
    g_print("Address:\nAddr1: %s\nAddr2: %s\nCity: %s\nState: %s\nPinCode: %s\nLatitude: %lf\nLongitude: %lf\n",
            newUser.address.addr1, newUser.address.addr2, newUser.address.city,
            newUser.address.state, newUser.address.pinCode, newUser.address.lattitude, newUser.address.longitude);

    // Update the user's coordinates


    // Open the users file in append mode
    usersFile = fopen("db/users.txt", "a");
    if (usersFile == NULL) {
        perror("Error opening users.txt");
        exit(1);
    }

    // Append the new user data to the users file
    fprintf(usersFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%lf,%lf\n", newUser.name, newUser.username, newUser.password,
            newUser.phone, newUser.address.addr1, newUser.address.addr2, newUser.address.city,
            newUser.address.state, newUser.address.pinCode, newUser.address.lattitude, newUser.address.longitude);
    fclose(usersFile);

    // Create a new file for the user with the username as the filename
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
    fclose(userFile);
}

void active_log(GtkWidget *widget, gpointer data){
    FILE *usersFile;
    
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *login_button;
    GtkWidget *Next_button;
    GtkWidget *Back_button;
    
    
    //char username[MAX_LENGTH], password[MAX_LENGTH];
    int found = 0;

    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(data));
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Longin user");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);

    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW));
    
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 7);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    username_entry = gtk_entry_new();
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Username :"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Password :"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 4, 2, 1);
    
    login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), grid);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 6, 3, 1);


    Back_button = gtk_button_new_with_label("<-- Back");
    g_signal_connect(Back_button, "clicked", G_CALLBACK(destroy_Window), window);
    gtk_grid_attach(GTK_GRID(grid), Back_button, 0, 7, 1, 1);

    gtk_window_present(GTK_WINDOW(window));
}

void activate_reg(GtkWidget *widget, gpointer data) {
   
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *register_button;
    GtkWidget *back_button;

    GtkApplication *app = gtk_window_get_application(GTK_WINDOW(data));
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "User Registration");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    name_entry = gtk_entry_new();
    username_entry = gtk_entry_new();
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // Hide password
    conform_password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(conform_password_entry), FALSE);
    phone_entry = gtk_entry_new();

    addr1_entry = gtk_entry_new();
    addr2_entry = gtk_entry_new();
    city_entry = gtk_entry_new();
    state_entry = gtk_entry_new();
    pinCode_entry = gtk_entry_new();
    

    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Name");
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(conform_password_entry), "Confirm Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Phone");
    gtk_entry_set_placeholder_text(GTK_ENTRY(addr1_entry), "Address Line 1");
    gtk_entry_set_placeholder_text(GTK_ENTRY(addr2_entry), "Address Line 2");
    gtk_entry_set_placeholder_text(GTK_ENTRY(city_entry), "City");
    gtk_entry_set_placeholder_text(GTK_ENTRY(state_entry), "State");
    gtk_entry_set_placeholder_text(GTK_ENTRY(pinCode_entry), "Pin Code");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Name"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Username"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Password"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Confirm Password"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), conform_password_entry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Phone"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), phone_entry, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Address Line 1"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addr1_entry, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Address Line 2"), 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addr2_entry, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("City"), 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), city_entry, 1, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("State"), 0, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), state_entry, 1, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Pin Code"), 0, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), pinCode_entry, 1, 9, 1, 1);

    register_button = gtk_button_new_with_label("Register");
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_clicked), window);
    g_signal_connect (register_button, "clicked", G_CALLBACK(destroy_Window), window);
    //g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);
    gtk_grid_attach(GTK_GRID(grid), register_button, 1, 10, 1, 1);

    //back to destroy
    back_button = gtk_button_new_with_label("BACK");
    g_signal_connect(back_button, "clicked", G_CALLBACK(destroy_Window), window);
    gtk_grid_attach(GTK_GRID(grid), back_button, 1, 11, 1, 1);

    gtk_window_present(GTK_WINDOW(window));
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *grid;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "FOOD");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    button1 = gtk_button_new_with_label("LOGIN");
    button2 = gtk_button_new_with_label("SIGN UP");
    button3 = gtk_button_new_with_label("EXIT");

    g_signal_connect(button1, "clicked", G_CALLBACK(active_log), window);
    g_signal_connect(button2, "clicked", G_CALLBACK(activate_reg), window);
    g_signal_connect(button3, "clicked", G_CALLBACK(destroy_Window), window);

    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 4, 1, 1);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.food", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
void print_hello(GtkWidget *widget, gpointer data) {
    g_print("WORKING\n");
}

void destroy_Window(GtkWidget *widget, gpointer data) {
    GtkWindow *window = GTK_WINDOW(data);
    gtk_window_destroy(window);
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

// Function to show a message dialog
void show_message_dialog(GtkWindow *parent, const char *message) {
    GtkWidget *dialog;

    dialog = gtk_dialog_new_with_buttons("Information",
                                         parent,
                                         GTK_DIALOG_MODAL,
                                         ("OK"),
                                         GTK_RESPONSE_OK,
                                         NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label = gtk_label_new(message);
    gtk_box_append(GTK_BOX(content_area), label);

    g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_close), dialog);
    gtk_widget_show(dialog);
}
