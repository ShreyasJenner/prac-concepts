#include <gtk-4.0/gtk/gtk.h>
#include <iostream>
#include <lightdm-gobject-1/lightdm.h>
#include <lightdm-gobject-1/lightdm/greeter.h>
#include <lightdm-gobject-1/lightdm/system.h>

LightDMGreeter *greeter;

// callback when authentication is complete
void authentication_complete_cb(LightDMGreeter *greeter, gpointer user_data) {
  if (lightdm_greeter_get_is_authenticated(greeter)) {
    std::cout << "Authentication Successful!" << '\n';
    lightdm_greeter_start_session_sync(greeter, NULL, NULL);
  } else {
    std::cerr << "Authentication Failed!\n";
  }
}

// callback for the login button
void on_login_button_clicked(GtkButton *button, gpointer user_data) {
  GtkEntry **entries = (GtkEntry **)user_data;
  const gchar *username = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
  const gchar *password = gtk_editable_get_text(GTK_EDITABLE(entries[1]));

  if (lightdm_greeter_authenticate(greeter, username, NULL)) {
    lightdm_greeter_respond(greeter, password, NULL);
  } else {
    std::cerr << "Failed to initiate authentication\n";
  }
}

static void activate(GtkApplication *app, gpointer user_data) {
  // initialize lightdm greeter
  greeter = lightdm_greeter_new();
  if (!lightdm_greeter_connect_sync(greeter, NULL)) {
    std::cerr << "Failed to connect to LightDM" << '\n';
    return;
  }
  g_signal_connect(greeter, "authentication-complete",
                   G_CALLBACK(authentication_complete_cb), NULL);

  // create main gtk window
  GtkWidget *window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(window), "Simple GTK4 Greeter");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
  g_signal_connect(window, "close-request", G_CALLBACK(gtk_window_destroy),
                   NULL);

  // create a vertical box layout
  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_window_set_child(GTK_WINDOW(window), vbox);

  // username entry
  GtkWidget *username_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
  gtk_box_append(GTK_BOX(vbox), username_entry);

  // password entry
  GtkWidget *password_entry = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
  gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
  gtk_box_append(GTK_BOX(vbox), password_entry);

  // login button
  GtkWidget *login_button = gtk_button_new_with_label("Login");
  gtk_box_append(GTK_BOX(vbox), login_button);

  // connect the login button to the callback
  GtkEntry *entries[] = {GTK_ENTRY(username_entry), GTK_ENTRY(password_entry)};
  g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked),
                   entries);

  // show all widgets
  gtk_widget_set_visible(window, TRUE);
}

int main(int argc, char **argv) {
  GtkApplication *app = gtk_application_new("org.example.simplegreeter",
                                            G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_application_hold(G_APPLICATION(app));
  g_object_unref(app);

  return status;
}
