#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

#define MAX_LENGTH 100

// typedef struct {
//     char addr1[MAX_LENGTH];
//     char addr2[MAX_LENGTH];
//     char city[MAX_LENGTH];
//     char state[MAX_LENGTH];
//     char pinCode[MAX_LENGTH];
//     double lattitude;
//     double longitude;
// } Address;

// typedef struct {
//     char name[MAX_LENGTH];
//     char username[MAX_LENGTH];
//     char password[MAX_LENGTH];
//     char phone[MAX_LENGTH];
//     Address address;
// } User;

void setTextColor(const char* colorCode) {
    printf("%s", colorCode);
}

void resetTextColor() {
    printf("\033[0m");
}

// int user_exists(const char* username);


// void registerUser(GtkWidget *widget, gpointer data) {
//     User newUser;
//     FILE* usersFile, * userFile;
//     char conf_pass[MAX_LENGTH];
//     double lattitude, longitude;

//     printf("Enter name: ");
//     scanf(" %[^\n]", newUser.name);
//     while (1) {
//         printf("Enter username: ");
//         scanf("%s", newUser.username);

//         if (user_exists(newUser.username) == 1) {
//             setTextColor(YELLOW);
//             printf("\n!! Username already taken !!\n");
//             resetTextColor();
//         } else break;
//     }

//     while (1) {
//         printf("Enter password: ");
//         scanf("%s", newUser.password);
//         printf("Confirm password: ");
//         scanf("%s", conf_pass);

//         if (strcmp(newUser.password, conf_pass) == 0) {
//             setTextColor(GREEN);
//             printf("Passwords match.\n");
//             resetTextColor();
//             break;
//         } else {
//             setTextColor(YELLOW);
//             printf("Passwords do not match. Please try again.\n");
//             resetTextColor();
//         }
//     }

//     printf("Enter phone number: ");
//     scanf("%s", newUser.phone);
//     printf("Enter address line 1: ");
//     scanf(" %[^\n]", newUser.address.addr1);
//     printf("Enter address line 2: ");
//     scanf(" %[^\n]", newUser.address.addr2);
//     printf("Enter city name: ");
//     scanf("%s", newUser.address.city);
//     printf("Enter state: ");
//     scanf(" %[^\n]", newUser.address.state);
//     printf("Enter pin code: ");
//     scanf("%s", newUser.address.pinCode);

// //     //update_user_coordinates(newUser.address.addr1, newUser.address.addr2, newUser.address.city, 
// //     //                        newUser.address.state, atoi(newUser.address.pinCode), &lattitude, &longitude);
// }

static void print_hello(GtkWidget *widget, gpointer data) {
    g_print("WORKING\n");
}


// static void destroy_window(GtkWidget *widget, gpointer data) {
//     GtkWindow *window = GTK_WINDOW(data);
//     gtk_window_destroy(window);
// }


static void show_new_buttons(GtkWidget *window) {
    GtkWidget *new_box;
    GtkWidget *new_button1;
    GtkWidget *new_button2;

    new_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_widget_set_halign(new_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(new_box, GTK_ALIGN_CENTER);

    new_button1 = gtk_button_new_with_label("NEW BUTTON 1");
    new_button2 = gtk_button_new_with_label("NEW BUTTON 2");

    g_signal_connect(new_button1, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect(new_button2, "clicked", G_CALLBACK(print_hello), NULL);

    gtk_box_append(GTK_BOX(new_box), new_button1);
    gtk_box_append(GTK_BOX(new_box), new_button2);

    gtk_window_set_child(GTK_WINDOW(window), new_box);
}

// static void destroy_main_box_and_show_new_buttons(GtkWidget *widget, GtkWidget *window) {
//     show_new_buttons(window);
// }

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *grid;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "FOOD");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    button1 = gtk_button_new_with_label("LOGIN");
    button2 = gtk_button_new_with_label("SIGN UP");
    button3 = gtk_button_new_with_label("EXIT");

    g_signal_connect(button1, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(/*destroy_window*/print_hello), window);



    //g_signal_connect_swapped(button1, "clicked", G_CALLBACK(destroy_main_box_and_show_new_buttons), grid);

    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 2, 1, 2);
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 4, 1, 2);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    printf("working");

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
