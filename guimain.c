#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "colors.h"
#include "map_functions.c"
#include "sorting.c"
#include "search.c"
#include "weatherer.c"

#define MAX_LENGTH 100

// typedef struct {
//     char name[100];
//     float rating;
//     float distance;
//     float travel_time;
// } Restaurant;
typedef struct {
    char name[100];
    float price;
    int quantity;
    int fid;
} MenuItem;

typedef struct {
    char restaurant_name[100];
    MenuItem *menu_items;
    int menu_count;
} RestaurantMenu;


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

Restaurant *restaurants = NULL;
char *restaurant_name;
// Function prototypes
int user_exists(const char* username);

void setTextColor(const char* colorCode);
void resetTextColor();

void on_restaurant_button_clicked(GtkWidget *widget, gpointer data);
void on_register_clicked(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);
void activate_reg(GtkWidget *widget, gpointer data);
RestaurantMenu read_menu(const char *restaurant_name);
void on_search_button_clicked(GtkWidget *widget, gpointer data);
void show_final_menu_window(GtkWidget *widget, gpointer data);

void show_order_summary(GtkWidget *widget, gpointer data);
void show_message_dialog(GtkWindow *parent, const char *message);
void print_hello(GtkWidget *widget, gpointer data);
void destroy_Window(GtkWidget *widget, gpointer data);
//backend prototype
void changePassword(const char* username);
void get_rest_dists(const char *username, const double latitude, const double longitude);
//Restaurant *restaurants = NULL;

void setTextColor(const char* colorCode) {
    printf("%s", colorCode);
}


void resetTextColor() {
    printf("\033[0m");
}

void destroy_data(gpointer data) {
    g_free(data);
    printf("Data has been freed.\n");
}

void on_cancel_order_clicked(GtkWidget *widget, gpointer data) {
    g_print("Order cancelled.\n");
    gtk_window_close(GTK_WINDOW(widget));
}

void print_menu(RestaurantMenu* menu) {
    printf("Restaurant Name: %s\n", menu->restaurant_name);
    printf("Menu:\n");
    printf("%-20s %-10s %-10s %-10s\n", "Dish Name", "Price", "Quantity", "FID");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < menu->menu_count; i++) {
        printf("%-20s ₹%-9.2f %-10d %-10d\n",
               menu->menu_items[i].name,
               menu->menu_items[i].price,
               menu->menu_items[i].quantity,
               menu->menu_items[i].fid);
    }
}
void write_menu_to_bin_file(const char *filename, RestaurantMenu *menu) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Write restaurant name
    fwrite(menu->restaurant_name, sizeof(char), 100, file);
    
    // Write menu count
    fwrite(&(menu->menu_count), sizeof(int), 1, file);

    // Write each menu item
    for (int i = 0; i < menu->menu_count; i++) {
        fwrite(&(menu->menu_items[i]), sizeof(MenuItem), 1, file);
    }

    fclose(file);
}

void read_menu_from_bin_file(const char *filename, RestaurantMenu *menu) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Read restaurant name
    fread(menu->restaurant_name, sizeof(char), 100, file);

    // Read menu count
    fread(&(menu->menu_count), sizeof(int), 1, file);

    // Allocate memory for menu items
    menu->menu_items = (MenuItem *)malloc(menu->menu_count * sizeof(MenuItem));
    if (menu->menu_items == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read each menu item
    for (int i = 0; i < menu->menu_count; i++) {
        fread(&(menu->menu_items[i]), sizeof(MenuItem), 1, file);
    }

    fclose(file);
}


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
void strip_endspaces (char *str) {
    int len = strlen(str);
    int i;

    // Traverse from the end of the string towards the beginning
    for (i = len - 1; i >= 0; i--) {
        if (!isspace(str[i])) {
            break;
        }
    }

    // Null-terminate the string at the first non-space character from the end
    str[i + 1] = '\0';
}

void on_restaurant_button_clicked(GtkWidget *widget, gpointer data) {
    char *restaurant_name = (char *)data;
    g_print("Restaurant: %s\n", restaurant_name);
    strip_endspaces(restaurant_name);
    read_menu(restaurant_name);
}

void on_confirm_order_clicked(GtkWidget *widget, gpointer data) {
    RestaurantMenu *menu = (RestaurantMenu *)data;
    printf("working\n");
    show_order_summary(widget, menu);
    printf("working\n");
    
}

// Function to read menu from file
RestaurantMenu read_menu(const char *restaurant_name) {
    RestaurantMenu menu;
    strncpy(menu.restaurant_name, restaurant_name, sizeof(menu.restaurant_name) - 1);
    menu.restaurant_name[sizeof(menu.restaurant_name) - 1] = '\0';  // Ensure null-termination

    char filename[150];
    snprintf(filename, sizeof(filename), "chennai_rest_menus/%s.txt", menu.restaurant_name);
    printf("Opening file: %s\n", filename);

     

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    menu.menu_items = malloc(256 * sizeof(MenuItem));
    if (!menu.menu_items) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[256];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        // Skip header line
        if (index == 0) {
            index++;
            continue;
        }
        
        // Find commas
        char *first_comma = strchr(line, ',');
        if (!first_comma) {
            continue;  // Invalid line format, skip
        }
        
        char *second_comma = strchr(first_comma + 1, ',');
        if (!second_comma) {
            continue;  // Invalid line format, skip
        }

        char *third_comma = strchr(second_comma + 1, ',');
        if (!third_comma) {
            continue;  // Invalid line format, skip
        }

        char *fourth_comma = strchr(third_comma + 1, ',');
        if (!fourth_comma) {
            continue;  // Invalid line format, skip
        }

        char *fifth_comma = strchr(fourth_comma + 1, ',');
        if (!fifth_comma) {
            continue;  // Invalid line format, skip
        }

        // Extract the item name (part between first and second comma)
        char *name_start = first_comma + 1;
        int name_length = second_comma - name_start;
        strncpy(menu.menu_items[index - 1].name, name_start, name_length);
        menu.menu_items[index - 1].name[name_length] = '\0';  // Ensure null-termination

        // Extract the price
        float price;
        sscanf(second_comma + 2, "₹%f", &price);
        menu.menu_items[index - 1].price = price;

        // Extract the FID
        int fid;
        sscanf(fifth_comma + 1, "%d", &fid);
        menu.menu_items[index - 1].fid = fid;

        // Initialize quantity to 0
        menu.menu_items[index - 1].quantity = 0;

        index++;
    }
    menu.menu_count = index - 1;  // Adjusting for the skipped header line
    fclose(file);
    print_menu(&menu);
    return menu;
}

// Function to handle quantity changes
void on_quantity_changed(GtkWidget *widget, gpointer data) {
    int *quantity = (int *)data;
    if (strcmp(gtk_button_get_label(GTK_BUTTON(widget)), "+") == 0) {
        (*quantity)++;
    } else {
        if (*quantity > 0) {
            (*quantity)--;
        }
    }
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%d", *quantity);
    gtk_button_set_label(GTK_BUTTON(widget), buffer);
    //quantity = gtk_spin_button_new_with_range(-90.0, 90.0, 0.0001);
}

// Additional function to handle quantity changes
// Function to handle quantity changes
void update_quantity (GtkSpinButton *button, gpointer quantity_ptr) {
    int *qtt = (int *)quantity_ptr;
    *qtt = gtk_spin_button_get_value_as_int (button);
    printf("%d", *qtt);
}

void on_payment_clicked(GtkWidget *widget, gpointer data) {
    RestaurantMenu *menu = (RestaurantMenu *)data;
    
    char *username;
    FILE *ftemp = fopen("tempusername.txt","r");
    fscanf(ftemp, username);
    fclose(ftemp);

    char filename[150];
    snprintf(filename, sizeof(filename), "%s_order.txt", username);

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < menu->menu_count; i++) {
        if (menu->menu_items[i].quantity > 0) {
            fprintf(file, "%s,%.2f,%d\n", menu->menu_items[i].name, menu->menu_items[i].price, menu->menu_items[i].quantity);
        }
    }

    fclose(file);
    g_print("Order confirmed and saved to %s\n", filename);
}

void show_order_summary(GtkWidget *widget, gpointer data) {
    printf("working\n");
    RestaurantMenu menu;
    read_menu_from_bin_file("temp.bin", &menu);
    //in summary
    int *qtt = (int *)data;
    for(int i=0; i<menu.menu_count;i++)
        menu.menu_items[i].quantity = qtt[i];

    write_menu_to_bin_file("temp.bin", &menu);

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Order Summary");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), grid);

    // Add headers
    GtkWidget *header_label;
    header_label = gtk_label_new("S_NO.");
    gtk_grid_attach(GTK_GRID(grid), header_label, 0, 0, 1, 1);

    header_label = gtk_label_new("Dish Name");
    gtk_grid_attach(GTK_GRID(grid), header_label, 1, 0, 1, 1);

    header_label = gtk_label_new("Quantity");
    gtk_grid_attach(GTK_GRID(grid), header_label, 2, 0, 1, 1);

    FILE *file = fopen("order_hist/fid_hist.txt", "a");
    if (!file) {
        perror("Failed to open fid_hist.txt");
        exit(EXIT_FAILURE);
    }
    
    print_menu(&menu);

    int row = 1;
    for (int i = 0; i < menu.menu_count; i++) {
        printf("Working\%d\n",i);
        if (menu.menu_items[i].quantity > 0) {
            printf("Working\%d\n",i);
            char buffer[256];
            

            // Add Serial Number
            snprintf(buffer, sizeof(buffer), "%d", row);
            GtkWidget *label = gtk_label_new(buffer);
            gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);

            // Add Dish Name
            label = gtk_label_new(menu.menu_items[i].name);
            gtk_grid_attach(GTK_GRID(grid), label, 1, row, 1, 1);

            // Add Quantity
            snprintf(buffer, sizeof(buffer), "%d", menu.menu_items[i].quantity);
            label = gtk_label_new(buffer);
            gtk_grid_attach(GTK_GRID(grid), label, 2, row, 1, 1);

            fprintf(file, "%d\n", menu.menu_items[i].fid); // Log the FID

            row++;
        }
    }
    fclose(file);

    // Add buttons at the bottom
    GtkWidget *button1 = gtk_button_new_with_label("<--Back");
    g_signal_connect(button3, "clicked", G_CALLBACK(destroy_Window), window);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, row + 1, 1, 1);

    //GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    //gtk_grid_attach(GTK_GRID(grid), button2, 1, row + 1, 1, 1);

    GtkWidget *button3 = gtk_button_new_with_label("BILL");
    g_signal_connect(button3, "clicked", G_CALLBACK(show_final_menu_window), restaurant_name);
    gtk_grid_attach(GTK_GRID(grid), button3, 2, row + 1, 1, 1);

    gtk_widget_show(window);
}

// Function to show the menu window
void show_menu_window(GtkWidget *widget, gpointer data) {
    char *restaurant_name = (char *)data;
    g_print("Restaurant: %s\n", restaurant_name);
    strip_endspaces(restaurant_name);
     
    RestaurantMenu menu = read_menu(restaurant_name);

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), menu.restaurant_name);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), grid);

    // Add headers
    GtkWidget *header_label;
    header_label = gtk_label_new("Serial No");
    gtk_grid_attach(GTK_GRID(grid), header_label, 0, 0, 1, 1);

    header_label = gtk_label_new("Dish Name");
    gtk_grid_attach(GTK_GRID(grid), header_label, 1, 0, 1, 1);

    header_label = gtk_label_new("Price");
    gtk_grid_attach(GTK_GRID(grid), header_label, 2, 0, 1, 1);

    header_label = gtk_label_new("Quantity");
    gtk_grid_attach(GTK_GRID(grid), header_label, 3, 0, 1, 1);

    int *qtt = (int *)calloc(menu.menu_count, sizeof(int));
    for (int i = 0; i < menu.menu_count; i++) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%d", i + 1);
        GtkWidget *label = gtk_label_new(buffer);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i + 1, 1, 1);

        label = gtk_label_new(menu.menu_items[i].name);
        gtk_grid_attach(GTK_GRID(grid), label, 1, i + 1, 1, 1);

        snprintf(buffer, sizeof(buffer), "%.2f", menu.menu_items[i].price);
        label = gtk_label_new(buffer);
        gtk_grid_attach(GTK_GRID(grid), label, 2, i + 1, 1, 1);

        //snprintf(buffer, sizeof(buffer), "%d", menu.menu_items[i].quantity);
        GtkWidget *quantity_spin_button = gtk_spin_button_new_with_range(0.0, 90.0, 1.0);
        gtk_grid_attach(GTK_GRID(grid), quantity_spin_button, 3, i + 1, 1, 1);

        //g_signal_connect(quantity_spin_button, "value-changed", G_CALLBACK(grab_int_value), &qtt);
        g_signal_connect(GTK_SPIN_BUTTON(quantity_spin_button), "value-changed", G_CALLBACK(update_quantity), &qtt[i]);
    }
    print_menu(&menu);
    GtkWidget *confirm_button = gtk_button_new_with_label("Confirm Order");

    write_menu_to_bin_file("temp.bin", &menu);

    //g_object_set_data_full(G_OBJECT(confirm_button), "menu-data", &menu, destroy_data);
    g_signal_connect(confirm_button, "clicked", G_CALLBACK(show_order_summary), qtt);
    //g_object_set_data(G_OBJECT(confirm_button), "menu-data", &menu);

    gtk_grid_attach(GTK_GRID(grid), confirm_button, 2, menu.menu_count + 1, 2, 1);

    GtkWidget *back_button = gtk_button_new_with_label("<-- Back");
    g_signal_connect(back_button, "clicked", G_CALLBACK(destroy_Window), &menu);
    gtk_grid_attach(GTK_GRID(grid), back_button, 0, menu.menu_count + 1, 2, 1);

    gtk_widget_show(window);
}

void create_restaurant_buttons(GtkWidget *box, Restaurant *restaurants, int count) {
    for (int i = 0; i < count; i++) {
        char label_text[256];
        snprintf(label_text, sizeof(label_text), "%d. %s\nRating: %.2f\nDistance: %.2f km\nTravel Time: %.2f min",
                 i + 1, restaurants[i].name, restaurants[i].rating, restaurants[i].distance, restaurants[i].travel_time);

        GtkWidget *button = gtk_button_new_with_label(label_text);
        g_signal_connect(button, "clicked", G_CALLBACK(show_menu_window), g_strdup(restaurants[i].name));
        gtk_box_append(GTK_BOX(box), button);
    }
}

void show_final_menu_window(GtkWidget *widget, gpointer data) {
    //restaurant_name = (char *)data;
    //g_print("Restaurant: %s\n", restaurant_name);
    //strip_endspaces(restaurant_name);
    RestaurantMenu menu;
    read_menu_from_bin_file("temp.bin", &menu);

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), menu.restaurant_name);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), grid);

    GtkWidget *header_label;
    header_label = gtk_label_new("Serial No");
    gtk_grid_attach(GTK_GRID(grid), header_label, 0, 0, 1, 1);

    header_label = gtk_label_new("Dish Name");
    gtk_grid_attach(GTK_GRID(grid), header_label, 1, 0, 1, 1);

    header_label = gtk_label_new("Price");
    gtk_grid_attach(GTK_GRID(grid), header_label, 2, 0, 1, 1);

    header_label = gtk_label_new("Quantity");
    gtk_grid_attach(GTK_GRID(grid), header_label, 3, 0, 1, 1);

    header_label = gtk_label_new("Total");
    gtk_grid_attach(GTK_GRID(grid), header_label, 4, 0, 1, 1);

    int row = 1;
    float grand_total = 0.0;

    for (int i = 0; i < menu.menu_count; i++) {
        if (menu.menu_items[i].quantity > 0) {
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%d", row);
            GtkWidget *label = gtk_label_new(buffer);
            gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);

            label = gtk_label_new(menu.menu_items[i].name);
            gtk_grid_attach(GTK_GRID(grid), label, 1, row, 1, 1);

            snprintf(buffer, sizeof(buffer), "%.2f", menu.menu_items[i].price);
            label = gtk_label_new(buffer);
            gtk_grid_attach(GTK_GRID(grid), label, 2, row, 1, 1);

            GtkWidget *quantity_spin_button = gtk_spin_button_new_with_range(0.0, 90.0, 1.0);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(quantity_spin_button), menu.menu_items[i].quantity);
            g_object_set_data(G_OBJECT(quantity_spin_button), "menu-item", &menu.menu_items[i]);
            //g_signal_connect(quantity_spin_button, "value-changed", G_CALLBACK(on_quantity_value_changed), &menu.menu_items[i]);
            gtk_grid_attach(GTK_GRID(grid), quantity_spin_button, 3, row, 1, 1);

            float total = menu.menu_items[i].price * menu.menu_items[i].quantity;
            snprintf(buffer, sizeof(buffer), "%.2f", total);
            label = gtk_label_new(buffer);
            gtk_grid_attach(GTK_GRID(grid), label, 4, row, 1, 1);

            grand_total += total;
            row++;
        }
    }

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "Total: ₹%.2f", grand_total);
    GtkWidget *total_label = gtk_label_new(buffer);
    gtk_grid_attach(GTK_GRID(grid), total_label, 3, row, 2, 1);

    GtkWidget *confirm_button = gtk_button_new_with_label("ONLINE PAYMENT");
    g_signal_connect(confirm_button, "clicked", G_CALLBACK(on_payment_clicked), &menu);
    gtk_grid_attach(GTK_GRID(grid), confirm_button, 1, row + 1, 1, 1);

    GtkWidget *cancel_button = gtk_button_new_with_label("Cash On Dilivery");
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_cancel_order_clicked), window);
    gtk_grid_attach(GTK_GRID(grid), cancel_button, 2, row + 1, 1, 1);

    GtkWidget *back_button = gtk_button_new_with_label("<-- Back");
    g_signal_connect(back_button, "clicked", G_CALLBACK(destroy_Window), window);
    gtk_grid_attach(GTK_GRID(grid), back_button, 3, row + 1, 1, 1);

    gtk_widget_show(window);
}


void on_Sort_by_Rating_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    int n_rest = 29;
    //Restaurant *restaurants = NULL;

    //store_rests(username, &restaurants, &n_rest);
    sort_rests(2, restaurants, n_rest);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Sort by Rating");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    // Create a scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    // Create a box to hold the restaurant buttons
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

    // Create and add restaurant buttons to the box
    create_restaurant_buttons(box, restaurants, n_rest);

    gtk_widget_show(window);
    


}
void on_Sort_by_Distance_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    int n_rest = 29;
    
    //Restaurant *restaurants = NULL;
     // Allocate memory for restaurants
    //restaurants = malloc(100 * sizeof(Restaurant));
    //if (!restaurants) {
    //    perror("Failed to allocate memory");
    //  exit(EXIT_FAILURE);
    //}
    //store_rests(username, &restaurants, &n_rest);
    sort_rests(1, restaurants, n_rest);

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Sorted by Distance");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    // Create a scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    // Create a box to hold the restaurant buttons
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

    // Create and add restaurant buttons to the box
    create_restaurant_buttons(box, restaurants, n_rest);

    gtk_widget_show(window);
     // Free allocated memory
    //free(restaurants);
}

void on_food_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    int n_rest = 29;
    //Restaurant *restaurants = NULL;

    //store_rests(username, &restaurants, &n_rest);
    //sort_rests(2, restaurants, n_rest);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Sort by Rating");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    // Create a scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

    create_restaurant_buttons(box, restaurants, n_rest);

    gtk_widget_show(window);
}
void on_rest_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    int n_rest = 29;
    //Restaurant *restaurants = NULL;

    //store_rests(username, &restaurants, &n_rest);
    //sort_rests(2, restaurants, n_rest);
    
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Sort by Rating");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

    // Create and add restaurant buttons to the box
    create_restaurant_buttons(box, restaurants, n_rest);

    gtk_widget_show(window);
}

void on_search_button_clicked(GtkWidget *widget, gpointer data){
    GtkWidget *window;
    GtkWidget *rest_button;
    GtkWidget *food_button;
    GtkWidget *search_bar;
    //GtkWidget *button4;
    GtkWidget *grid;
    //GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW));
    
    //GtkApplicationWindow *app = GTK_APPLICATION_WINDOW(data);
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "SEARCH");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 7);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    search_bar = gtk_entry_new();
    gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(search_bar)));
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_bar), "Search");
    gtk_grid_attach(GTK_GRID(grid), search_bar, 0, 0, 4, 1);

    food_button = gtk_button_new_with_label("SEARCH BY FOOD");
    g_signal_connect(food_button, "clicked", G_CALLBACK(on_food_button_clicked), search_bar);
    gtk_grid_attach(GTK_GRID(grid), food_button, 0, 1, 2, 1);
    //gtk_grid_attach(GTK_GRID(grid), button4, 0, 6, 1, 1);

    rest_button = gtk_button_new_with_label("SEARCH BY RESTAURANT");
    g_signal_connect(rest_button, "clicked", G_CALLBACK(on_rest_button_clicked), search_bar);
    gtk_grid_attach(GTK_GRID(grid), rest_button, 2, 1, 2, 1);

    gtk_widget_set_visible(food_button, TRUE);
    gtk_widget_set_visible(rest_button, TRUE);

    gtk_window_present(GTK_WINDOW(window));
}

void on_search_by_restaurant_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    //GtkWidget *button4;
    GtkWidget *grid;
    //GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW));
    
    //GtkApplicationWindow *app = GTK_APPLICATION_WINDOW(data);
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "SORTING");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 7);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), grid);

    button1 = gtk_button_new_with_label("1. Sort by Distance");
    button2 = gtk_button_new_with_label("2. Sort by Rating");
    button3 = gtk_button_new_with_label("<--Back");
    //button4 = gtk_button_new_with_label("4. Sign Out");

    g_signal_connect(button1, "clicked", G_CALLBACK(on_Sort_by_Distance_clicked), window);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_Sort_by_Rating_clicked), window);
    g_signal_connect(button3, "clicked", G_CALLBACK(destroy_Window), window);
    //g_signal_connect(button4, "clicked", G_CALLBACK(destroy_Window), window);

    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 2, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), button3, 1, 4, 1, 1);
    //gtk_grid_attach(GTK_GRID(grid), button4, 0, 6, 1, 1);

    gtk_widget_set_visible(button1, TRUE);
    gtk_widget_set_visible(button2, TRUE);
    gtk_widget_set_visible(button3, TRUE);
    //gtk_widget_set_visible(button4, TRUE);

    gtk_window_present(GTK_WINDOW(window));
}



void active_options(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *grid;

    //GtkApplicationWindow *app = gtk_application_new("com.example.GtkApplication",G_APPLICATION_FLAGS_NONE);
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

    g_signal_connect(button1, "clicked", G_CALLBACK(on_search_button_clicked), window);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_search_by_restaurant_clicked), window);
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

            
            
            int n_rest = 0;
            //undo the comment
            //get_rest_dists(username, user.address.lattitude, user.address.longitude);
            store_rests(username, &restaurants, &n_rest);

            break;
        }
    }

    fclose(usersFile);

    if (found==1) {
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
    //while (1) {
        password = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_entry)));
        const char *conf_pass = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(conform_password_entry)));

        if (strcmp(password, conf_pass) == 0) {
            //break;
        } else {
            const char *message = "Passwords do not match. Please try again.";
            GtkWindow *popup_window = GTK_WINDOW(data);
            show_message_dialog(popup_window, message);
        }
    //}

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

//getting resturant distance
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


//change password
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
        sscanf(line, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%lf,%lf", 
               user.name, user.username, user.password, user.phone, 
               user.address.addr1, user.address.addr2, user.address.city, 
               user.address.state, user.address.pinCode, &user.address.lattitude, &user.address.longitude);

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

    //goes into active password
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
