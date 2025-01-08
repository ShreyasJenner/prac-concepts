#include <notcurses/notcurses.h>

int main() {
  struct notcurses_options opts = {
      .flags = NCOPTION_INHIBIT_SETLOCALE,
  };

  struct notcurses *nc = notcurses_init(&opts, NULL);
  if (!nc) {
    return -1;
  }

  struct ncplane *stdplane = notcurses_stdplane(nc);
  unsigned rows, cols; // Use unsigned for dimensions
  ncplane_dim_yx(stdplane, &rows, &cols);

  // Dimensions for the windows
  unsigned left_cols = cols / 2; // Left window takes half the screen width
  unsigned right_cols = cols - left_cols;
  unsigned right_top_rows = rows / 2;
  unsigned right_bottom_rows = rows - right_top_rows;

  // Create the left window
  struct ncplane_options left_opts = {
      .y = 0,
      .x = 0,
      .rows = rows,
      .cols = left_cols,
      .name = "left",
  };
  struct ncplane *left = ncplane_create(stdplane, &left_opts);
  ncplane_set_bg_rgb(left, 0x228B22); // Green background
  ncplane_erase(left);

  // Create the top-right window
  struct ncplane_options top_right_opts = {
      .y = 0,
      .x = (int)left_cols,
      .rows = right_top_rows,
      .cols = right_cols,
      .name = "top_right",
  };
  struct ncplane *top_right = ncplane_create(stdplane, &top_right_opts);
  ncplane_set_bg_rgb(top_right, 0x1E90FF); // Blue background
  ncplane_erase(top_right);

  // Create the bottom-right window
  struct ncplane_options bottom_right_opts = {
      .y = (int)right_top_rows,
      .x = (int)left_cols,
      .rows = right_bottom_rows,
      .cols = right_cols,
      .name = "bottom_right",
  };
  struct ncplane *bottom_right = ncplane_create(stdplane, &bottom_right_opts);
  ncplane_set_bg_rgb(bottom_right, 0xFFD700); // Yellow background
  ncplane_erase(bottom_right);

  notcurses_render(nc);

  // Wait for a key press before exiting

  sleep(4);

  notcurses_stop(nc); // Clean up and stop Notcurses
  return 0;
}
