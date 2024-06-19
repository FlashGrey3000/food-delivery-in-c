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
#include "tryory.c"
#include "update_rating.c"

#define MAX_LENGTH 100

// typedef struct {
//     char name[100];
//     float rating;
//     float distance;
//     float travel_time;
// } Restaurant;
typedef struct {
    char foodname[100];
    int fid;
} Fooditem;



Fooditem fooditems_array[] = {
        {"Seafood Platter", 101},
        {"Grilled Fish", 102},
        {"Prawn Cocktail", 103},
        {"Caesar Salad", 104},
        {"Lemon Tart", 105},
        {"Mojito", 106},
        {"French Onion Soup", 201},
        {"Caesar Salad", 202},
        {"Grilled Chicken Sandwich", 203},
        {"Classic Cheeseburger", 204},
        {"Spaghetti Carbonara", 205},
        {"Tiramisu", 206},
        {"Masala Dosa", 301},
        {"Paneer Butter Masala", 302},
        {"Vegetable Biryani", 303},
        {"Idli Sambar", 304},
        {"Rasam Rice", 305},
        {"Mango Lassi", 306},
        {"Margherita Pizza", 401},
        {"Pasta Alfredo", 402},
        {"Caesar Salad", 403},
        {"Grilled Chicken", 404},
        {"Tiramisu", 405},
        {"Lemon Iced Tea", 406},
        {"Paneer Butter Masala", 501},
        {"Chicken Tikka", 502},
        {"Rogan Josh", 503},
        {"Butter Naan", 504},
        {"Lassi", 505},
        {"Gulab Jamun", 506},
        {"Channa Bhatura", 601},
        {"Sizzling Brownie", 602},
        {"Italian Herbed Cheese Balls", 603},
        {"American Corn Cheese Balls", 604},
        {"Paneer Tikka Masala", 605},
        {"Mexican Nachos", 606},
        {"Malabar Parotta", 701},
        {"Kerala Fish Curry", 702},
        {"Appam with Stew", 703},
        {"Prawn Mango Curry", 704},
        {"Thalassery Biryani", 705},
        {"Avial", 706},
        {"Butter Chicken", 801},
        {"Paneer Tikka", 802},
        {"Dal Makhani", 803},
        {"Chicken Fried Rice", 804},
        {"Veg Spring Rolls", 805},
        {"Grilled Fish", 806},
        {"Caesar Salad", 807},
        {"Chocolate Cake", 808},
        {"Brownie Sundae", 809},
        {"Garlic Naan", 810},
        {"Mango Lassi", 811},
        {"Chicken Noodles", 812},
        {"Butter Chicken", 901},
        {"Paneer Tikka", 902},
        {"Dal Makhani", 903},
        {"Chicken Fried Rice", 904},
        {"Veg Spring Rolls", 905},
        {"Grilled Fish", 906},
        {"Caesar Salad", 907},
        {"Chocolate Cake", 908},
        {"Brownie Sundae", 909},
        {"Butter Chicken", 1001},
        {"Dal Makhani", 1002},
        {"Vegetable Biryani", 1003},
        {"Butter Naan", 1004},
        {"Gajar Ka Halwa", 1005},
        {"Mango Lassi", 1006},
        {"Penne Arrabbiata", 1101},
        {"Margherita Pizza", 1102},
        {"Minestrone Soup", 1103},
        {"Tiramisu", 1104},
        {"Bruschetta", 1105},
        {"Gelato", 1106},
        {"Chettinad Chicken", 1201},
        {"Fish Moilee", 1202},
        {"Veg Kurma", 1203},
        {"Malabar Parotta", 1204},
        {"Appam", 1205},
        {"Payasam", 1206},
        {"Sushi Platter", 1301},
        {"Thai Green Curry", 1302},
        {"Japanese Ramen", 1303},
        {"Chicken Teriyaki", 1304},
        {"Asian Stir-Fried Vegetables", 1305},
        {"Tempura Prawns", 1306},
        {"Chicken Chettinad", 1401},
        {"Prawn Moilee", 1402},
        {"Malabar Parotta", 1403},
        {"Veg Biryani", 1404},
        {"Filter Coffee", 1405},
        {"Payasam", 1406},
        {"Caesar Salad", 1501},
        {"Margherita Pizza", 1502},
        {"Grilled Chicken", 1503},
        {"Spaghetti Bolognese", 1504},
        {"Cheesecake", 1505},
        {"Fresh Lime Soda", 1506},
        {"Salted Lemon Fish", 1507},
        {"Margherita Pizza", 1601},
        {"Spaghetti Carbonara", 1602},
        {"Sushi Platter", 1603},
        {"Chicken Caesar Salad", 1604},
        {"Tiramisu", 1605},
        {"Chocolate Milkshake", 1606},
        {"Kung Pao Chicken", 1607},
        {"Lemon Iced Tea", 1608},
        {"Veg Spring Rolls", 1609},
        {"Grilled Chicken", 1610},
        {"Garlic Bread", 1611},
        {"Cappuccino", 1612},
        {"Butter Chicken", 1701},
        {"Paneer Tikka", 1702},
        {"Dal Makhani", 1703},
        {"Garlic Naan", 1704},
        {"Gulab Jamun", 1705},
        {"Mango Lassi", 1706},
        {"Dark Chocolate Cake", 1801},
        {"Chocolate Brownie", 1802},
        {"Chocolate Fondue", 1803},
        {"Hot Chocolate", 1804},
        {"Chocolate Milkshake", 1805},
        {"Tiramisu", 1806},
        {"Rava Dosa", 1901},
        {"Veg Biryani", 1902},
        {"Onion Uttapam", 1903},
        {"Aloo Paratha", 1904},
        {"Gobi Manchurian", 1905},
        {"Mango Lassi", 1906},
        {"Grilled Prawns", 2001},
        {"Fish Curry", 2002},
        {"Chicken Tikka", 2003},
        {"Mutton Biryani", 2004},
        {"Paneer Butter Masala", 2005},
        {"Lassi", 2006},
        {"Paneer Tikka", 2101},
        {"Chicken Tandoori", 2102},
        {"Dal Makhani", 2103},
        {"Naan", 2104},
        {"Gajar Halwa", 2105},
        {"Mango Lassi", 2106},
        {"Sushi Platter", 2201},
        {"Ramen", 2202},
        {"Dim Sum", 2203},
        {"Pad Thai", 2204},
        {"Green Tea Ice Cream", 2205},
        {"Mango Sticky Rice", 2206},
        {"Chicken Chettinad", 2301},
        {"Masala Dosa", 2302},
        {"Fish Curry", 2303},
        {"Fried Rice", 2304},
        {"Veg Hakka Noodles", 2305},
        {"Grilled Sandwich", 2306},
        {"Chicken Burger", 2307},
        {"Paneer Tikka", 2308},
        {"Chocolate Brownie", 2309},
        {"Lemonade", 2310},
        {"Filter Coffee", 2311},
        {"Veg Manchurian", 2312},
        {"Veg Burger", 2401},
        {"Chicken Alfredo Pasta", 2402},
        {"Greek Salad", 2403},
        {"Waffles with Maple Syrup", 2404},
        {"Espresso", 2405},
        {"Lemon Iced Tea", 2406},
        {"BBQ Ribs", 2501},
        {"Buffalo Wings", 2502},
        {"Cheeseburger", 2503},
        {"Loaded Fries", 2504},
        {"Chocolate Milkshake", 2505},
        {"Pulled Pork Sandwich", 2506},
        {"BBQ Pork Ribs", 2601},
        {"Grilled Lamb Chops", 2602},
        {"Caesar Salad", 2603},
        {"Margherita Pizza", 2604},
        {"Chocolate Fondant", 2605},
        {"Mango Smoothie", 2606},
        {"Caesar Salad", 2701},
        {"Margherita Pizza", 2702},
        {"Grilled Chicken", 2703},
        {"Spaghetti Bolognese", 2704},
        {"Cheesecake", 2705},
        {"Mojito", 2706},
        {"Margherita Pizza", 2801},
        {"Quattro Formaggi Pizza", 2802},
        {"Spaghetti Aglio e Olio", 2803},
        {"Caesar Salad", 2804},
        {"Tiramisu", 2805},
        {"Gelato", 2806},
        {"Grilled Fish", 2901},
        {"Caesar Salad", 2902},
        {"Lamb Chops", 2903},
        {"Chicken Skewers", 2904},
        {"Tiramisu", 2905},
        {"Mojito", 2906},
    };
int fooditems_array_size = sizeof(fooditems_array) / sizeof(fooditems_array[0]);

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

Itemset* frequent_itemsets = NULL;
int frequent_itemset_count = 0;
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

char *getfoodname(int fid){
    for (int i=0; i<fooditems_array_size; i++){
        if (fid == fooditems_array[i].fid){
            return fooditems_array[i].foodname;
        }
    }
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

void up_rating(GtkWidget *widget, gpointer data) {
    RestaurantMenu menu;
    read_menu_from_bin_file("temp.bin", &menu);
    float *rate = gtk_entry_buffer_get_text(gtk_entry_get_buffer((GtkEntry *)(data)));
    update_reviews(menu.restaurant_name, rate);
}

void feed_back(GtkWidget *widget, gpointer data) {
    RestaurantMenu menu;
    read_menu_from_bin_file("temp.bin", &menu);

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "FEED BACK");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), grid);

    // Add headers
    GtkWidget *header_label;
    header_label = gtk_label_new("THANK YOU\nPLEASE ENTER YOUR VALUABLE FEED BACK");
    gtk_grid_attach(GTK_GRID(grid), header_label, 0, 0, 1, 1);

    GtkWidget *bar = gtk_entry_new();
    gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(bar)));
    gtk_entry_set_placeholder_text(GTK_ENTRY(bar), "plese enter btw 0-5");
    gtk_grid_attach(GTK_GRID(grid), bar, 3, 1, 3, 1);
    

    GtkWidget *button =  gtk_button_new_with_label("SUBMIT");
    g_signal_connect(button, "clicked", G_CALLBACK(up_rating), bar);
    g_signal_connect(button, "clicked", G_CALLBACK(exit), NULL);
    gtk_grid_attach(GTK_GRID(grid), bar, 4, 2, 1, 1);
    
    gtk_widget_show(window);
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
void update_quantity (GtkSpinButton *button, gpointer quantity_ptr) {
    int *qtt = (int *)quantity_ptr;
    *qtt = gtk_spin_button_get_value_as_int (button);
    printf("%d", *qtt);
}

// void on_payment_clicked(GtkWidget *widget, gpointer data) {
//     //RestaurantMenu *menu = (RestaurantMenu *)data;
    
//     char *username;
//     FILE *ftemp = fopen("tempusername.txt","r");
//     fscanf(ftemp, username);
//     fclose(ftemp);

//     char filename[150];
//     snprintf(filename, sizeof(filename), "%s_order.txt", username);

//     FILE *file = fopen(filename, "w");
//     if (!file) {
//         perror("Failed to open file");
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < menu->menu_count; i++) {
//         if (menu->menu_items[i].quantity > 0) {
//             fprintf(file, "%s,%.2f,%d\n", menu->menu_items[i].name, menu->menu_items[i].price, menu->menu_items[i].quantity);
//         }
//     }

//     fclose(file);
//     g_print("Order confirmed and saved to %s\n", filename);
// }


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
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 400);

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

            snprintf(buffer, sizeof(buffer), "%d", menu.menu_items[i].quantity);
            label = gtk_label_new(buffer);

            gtk_grid_attach(GTK_GRID(grid), label, 3, row, 1, 1);

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
    g_signal_connect(confirm_button, "clicked", G_CALLBACK(feed_back), &menu);
    gtk_grid_attach(GTK_GRID(grid), confirm_button, 1, row + 1, 1, 1);

    GtkWidget *cancel_button = gtk_button_new_with_label("Cash On Dilivery");
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(feed_back), window);
    gtk_grid_attach(GTK_GRID(grid), cancel_button, 2, row + 1, 1, 1);

    GtkWidget *back_button = gtk_button_new_with_label("<-- Back");
    g_signal_connect(back_button, "clicked", G_CALLBACK(destroy_Window), window);
    gtk_grid_attach(GTK_GRID(grid), back_button, 3, row + 1, 1, 1);

    gtk_widget_show(window);
}


void on_Sort_by_Rating_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    int n_rest = 29;

    sort_rests(2, restaurants, n_rest);
    
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
void on_Sort_by_Distance_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    int n_rest = 29;
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

    
    // Generate and prune itemsets iteratively
    int itemset_size = 2;
    //for food_recom
    int transaction_count;
    Transaction* transactions = read_transactions("transactions.txt", &transaction_count);

    frequent_itemsets = NULL;
    frequent_itemset_count = 0;

    // Print the transactions
    for (int i = 0; i < transaction_count; i++) {
        printf("Transaction %d: ", i + 1);
        for (int j = 0; j < transactions[i].count; j++) {
            printf("%d ", transactions[i].items[j]);
        }
        printf("\n");
    }

    int min_support = 2;

    // Determine the distinct items for initial candidates
    int item_counts[1000] = {0};  // Assuming item IDs are less than 1000 for simplicity
    for (int i = 0; i < transaction_count; i++) {
        for (int j = 0; j < transactions[i].count; j++) {
            item_counts[transactions[i].items[j]]++;
        }
    }

    // Initialize candidates (single items)
    int initial_candidate_count = 0;
    for (int i = 0; i < 1000; i++) {
        if (item_counts[i] > 0) {
            initial_candidate_count++;
        }
    }

    Itemset* candidates = (Itemset*)malloc(initial_candidate_count * sizeof(Itemset));
    int candidate_index = 0;
    for (int i = 0; i < 1000; i++) {
        if (item_counts[i] > 0) {
            candidates[candidate_index] = (Itemset){ .items = malloc(sizeof(int)), .count = 1, .support = 0 };
            candidates[candidate_index].items[0] = i;
            candidate_index++;
        }
    }
    int candidate_count = initial_candidate_count;

    // Count support and prune candidates
    count_support(transactions, transaction_count, candidates, candidate_count);
    prune_candidates(&candidates, &candidate_count, min_support);

    
    while (candidate_count > 0) {
        printf("Frequent itemsets of size %d:\n", itemset_size - 1);
        for (int i = 0; i < candidate_count; i++) {
            print_itemset(candidates[i]);
        }

        // Append current candidates to frequent itemsets
        frequent_itemsets = realloc(frequent_itemsets, (frequent_itemset_count + candidate_count) * sizeof(Itemset));
        for (int i = 0; i < candidate_count; i++) {
            frequent_itemsets[frequent_itemset_count + i] = deep_copy_itemset(candidates[i]);
        }
        frequent_itemset_count += candidate_count;

        Itemset* new_candidates;
        int new_candidate_count;
        generate_candidates(candidates, candidate_count, &new_candidates, &new_candidate_count, itemset_size);
        free_itemsets(candidates, candidate_count);

        count_support(transactions, transaction_count, new_candidates, new_candidate_count);
        prune_candidates(&new_candidates, &new_candidate_count, min_support);

        candidates = new_candidates;
        candidate_count = new_candidate_count;
        itemset_size++;
    }

}

void show_order_summary(GtkWidget *widget, gpointer data) {
    RestaurantMenu menu;
    read_menu_from_bin_file("temp.bin", &menu);
    //in summary
    int *qtt = (int *)data;
    for(int i=0; i<menu.menu_count;i++)
        menu.menu_items[i].quantity = qtt[i];

    write_menu_to_bin_file("temp.bin", &menu);

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Order Summary");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);

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

    FILE *file = fopen("transactions.txt", "a");
    if (!file) {
        perror("Failed to open fid_hist.txt");
        exit(EXIT_FAILURE);
    }
    
    print_menu(&menu);

    int row = 1;
    for (int i = 0; i < menu.menu_count; i++) {
        printf("Working\%d\n",i);
        if (menu.menu_items[i].quantity > 0) {
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

            fprintf(file, "%d ", menu.menu_items[i].fid); // Log the FID

            row++;
        }
    }
    fprintf(file, "\n");
    fclose(file);

    header_label = gtk_label_new("RECOMENDED FOOD");
    gtk_grid_attach(GTK_GRID(grid), header_label, 0, row + 1, 1, 1);

    RestaurantMenu rec_menu;
    int count = 0;

    for (int i = 0; i < frequent_itemset_count; i++) {
        int fid;
        if (menu.menu_items[i].quantity>0)
            fid = menu.menu_items[i].fid;
        else continue;
        Itemset itemset = frequent_itemsets[i];
        if (itemset.count == 2) { // Ensure we only consider itemsets of size 2
            int found = 0;
            for (int j = 0; j < itemset.count; j++) {
                if (itemset.items[j] == fid) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                for (int j = 0; j < itemset.count; j++) {
                    if (itemset.items[j] != fid) {
                        printf("%d ", itemset.items[j]);
                    }
                }
                printf("\n");
            }
        }
    }
    // for (int i =0; i<menu.menu_count; i++) {
    //     //rec_menu.menu_items[i].fid = find_frequent_with(menu.menu_items[i].fid, frequent_itemsets, frequent_itemset_count);
    //     if (rec_menu.menu_items[i].fid != 0){
    //         count++;
    //     }
    // }
    int k=1 ;
    for (int j = row + 2; j < row + 2 + count ;j ++ ){
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%d", k);
        GtkWidget *label = gtk_label_new(buffer);
        gtk_grid_attach(GTK_GRID(grid), label, 0, row, 1, 1);

            // Add Dish Name
        label = gtk_label_new(menu.menu_items[k].name);
        gtk_grid_attach(GTK_GRID(grid), label, 1, row, 1, 1);
        //add dish price
        //label = gtk_label_new(menu.menu_items[k].name);
        //gtk_grid_attach(GTK_GRID(grid), label, 1, row, 1, 1);

        GtkWidget *quantity_spin_button = gtk_spin_button_new_with_range(0.0, 90.0, 1.0);
        gtk_grid_attach(GTK_GRID(grid), quantity_spin_button, 2, row, 1, 1);
        g_signal_connect(GTK_SPIN_BUTTON(quantity_spin_button), "value-changed", G_CALLBACK(update_quantity), &qtt[k]);

        k++;
    }
    write_menu_to_bin_file("temp2.bin",&rec_menu);
    // FILE *file = fopen("temp.bin", "ab");
    // if (file == NULL) {
    //     perror("Failed to open file");
    //     exit(EXIT_FAILURE);
    // }
    
    // for (int i = 0; i < menu.menu_count; i++) {
    //     continue;
    // }
    // // Write restaurant name
    // //fwrite(menu->restaurant_name, sizeof(char), 100, file);
    
    // // Write menu count
    // //fwrite(&(menu->menu_count), sizeof(int), 1, file);

    // // Write each menu item
    // for (int i = 0; i < menu.menu_count; i++) {
    //     fwrite(&(menu.menu_items[i]), sizeof(MenuItem), 1, file);
    // }

    // fclose(file);

    // Add buttons at the bottom
    GtkWidget *button1 = gtk_button_new_with_label("<--Back");
    g_signal_connect(button1, "clicked", G_CALLBACK(destroy_Window), window);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, row + 1, 1, 1);

    //GtkWidget *button2 = gtk_button_new_with_label("Button 2");
    //gtk_grid_attach(GTK_GRID(grid), button2, 1, row + 1, 1, 1);

    GtkWidget *button3 = gtk_button_new_with_label("BILL");
    g_signal_connect(button3, "clicked", G_CALLBACK(show_final_menu_window), window);
    gtk_grid_attach(GTK_GRID(grid), button3, 2 , row + 1, 1, 1);

    gtk_widget_show(window);
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
