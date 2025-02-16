
#include <notcurses/notcurses.h>

int main() {
  // Initialize notcurses
  struct notcurses_options opts = {};
  struct notcurses *nc = notcurses_init(&opts, NULL);
  if (!nc) {
    return EXIT_FAILURE;
  }

  // Get terminal dimensions
  struct ncplane *stdplane = notcurses_stdplane(nc);
  unsigned int dimy, dimx;
  ncplane_dim_yx(stdplane, &dimy, &dimx);

  // Define box size
  unsigned int box_width = dimx / 2;
  unsigned int box_height = dimy / 2;

  // Box starting position
  int start_y = (dimy - box_height) / 2;
  int start_x = (dimx - box_width) / 2;

  // Create a plane for the box
  struct ncplane_options box_opts = {.y = start_y,
                                     .x = start_x,
                                     .rows = box_height,
                                     .cols = box_width,
                                     .userptr = NULL,
                                     .name = "rounded_box",
                                     .resizecb = NULL,
                                     .flags = 0};

  struct ncplane *box = ncplane_create(stdplane, &box_opts);
  if (!box) {
    notcurses_stop(nc);
    return EXIT_FAILURE;
  }

  // Draw a rounded box
  uint64_t border_styles = NCBOXGRAD_TOP | NCBOXGRAD_BOTTOM;
  int ret =
      ncplane_box(box, NULL, NULL, NULL, NULL, NULL, NULL, // Default box styles
                  border_styles, // Gradients for top and bottom
                  0              // No gradient on the corners.
      );
  ncplane_box(struct ncplane * n, const nccell *ul, const nccell *ur,
              const nccell *ll, const nccell *lr, const nccell *hline,
              const nccell *vline, unsigned int ystop, unsigned int xstop,
              unsigned int ctlword)
}
