#include <gtk-4.0/gtk/gtk.h>
#include <iostream>

// Modified callback for the login button - just prints the input
void on_login_button_clicked(GtkButton *button, gpointer user_data) {
  GtkEntry **entries = (GtkEntry **)user_data;
  const gchar *username = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
  const gchar *password = gtk_editable_get_text(GTK_EDITABLE(entries[1]));

  std::cout << "Username entered: " << username << std::endl;
  std::cout << "Password entered: [hidden]" << std::endl;
}

static void activate(GtkApplication *app, gpointer user_data) {
  // create main gtk window
  GtkWidget *window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(window), "Simple GTK4 Test");
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
  g_object_unref(app);
  return status;
}
