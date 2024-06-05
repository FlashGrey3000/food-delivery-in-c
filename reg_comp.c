#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
    char addr1[MAX_LENGTH];
    char addr2[MAX_LENGTH];
    char city[MAX_LENGTH];
    char state[MAX_LENGTH];
    char pinCode[MAX_LENGTH];
    double latitude;
    double longitude;
} Address;

typedef struct {
    char name[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char phone[MAX_LENGTH];
    Address address;
} User;

static GtkWidget *name_entry, *username_entry, *password_entry, *phone_entry;
static GtkWidget *addr1_entry, *addr2_entry, *city_entry, *state_entry, *pinCode_entry;
static GtkWidget *latitude_entry, *longitude_entry;

void on_register_clicked(GtkWidget *widget, gpointer data) {
    User newUser;

    const char *name = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(name_entry)));
    const char *username = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_entry)));
    const char *password = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_entry)));
    const char *phone = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(phone_entry)));

    const char *addr1 = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(addr1_entry)));
    const char *addr2 = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(addr2_entry)));
    const char *city = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(city_entry)));
    const char *state = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(state_entry)));
    const char *pinCode = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(pinCode_entry)));
    
    newUser.address.latitude = gtk_spin_button_get_value(GTK_SPIN_BUTTON(latitude_entry));
    newUser.address.longitude = gtk_spin_button_get_value(GTK_SPIN_BUTTON(longitude_entry));

    strncpy(newUser.name, name, MAX_LENGTH);
    strncpy(newUser.username, username, MAX_LENGTH);
    strncpy(newUser.password, password, MAX_LENGTH);
    strncpy(newUser.phone, phone, MAX_LENGTH);

    strncpy(newUser.address.addr1, addr1, MAX_LENGTH);
    strncpy(newUser.address.addr2, addr2, MAX_LENGTH);
    strncpy(newUser.address.city, city, MAX_LENGTH);
    strncpy(newUser.address.state, state, MAX_LENGTH);
    strncpy(newUser.address.pinCode, pinCode, MAX_LENGTH);

    g_print("User Registered:\nName: %s\nUsername: %s\nPassword: %s\nPhone: %s\n",
            newUser.name, newUser.username, newUser.password, newUser.phone);
    g_print("Address:\nAddr1: %s\nAddr2: %s\nCity: %s\nState: %s\nPinCode: %s\nLatitude: %f\nLongitude: %f\n",
            newUser.address.addr1, newUser.address.addr2, newUser.address.city,
            newUser.address.state, newUser.address.pinCode, newUser.address.latitude, newUser.address.longitude);

    // Save the user to a file or database here if needed
}

void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *register_button;

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
    phone_entry = gtk_entry_new();

    addr1_entry = gtk_entry_new();
    addr2_entry = gtk_entry_new();
    city_entry = gtk_entry_new();
    state_entry = gtk_entry_new();
    pinCode_entry = gtk_entry_new();

    latitude_entry = gtk_spin_button_new_with_range(-90.0, 90.0, 0.0001);
    longitude_entry = gtk_spin_button_new_with_range(-180.0, 180.0, 0.0001);

    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Name");
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(phone_entry), "Phone");

    gtk_entry_set_placeholder_text(GTK_ENTRY(addr1_entry), "Address Line 1");
    gtk_entry_set_placeholder_text(GTK_ENTRY(addr2_entry), "Address Line 2");
    gtk_entry_set_placeholder_text(GTK_ENTRY(city_entry), "City");
    gtk_entry_set_placeholder_text(GTK_ENTRY(state_entry), "State");
    gtk_entry_set_placeholder_text(GTK_ENTRY(pinCode_entry), "Pin Code");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Name:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Username:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Password:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Phone:"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), phone_entry, 1, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Address Line 1:"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addr1_entry, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Address Line 2:"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addr2_entry, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("City:"), 0, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), city_entry, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("State:"), 0, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), state_entry, 1, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Pin Code:"), 0, 8, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), pinCode_entry, 1, 8, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Latitude:"), 0, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), latitude_entry, 1, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Longitude:"), 0, 10, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), longitude_entry, 1, 10, 1, 1);

    register_button = gtk_button_new_with_label("SUBMIT");
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), register_button, 0, 11, 2, 1);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
