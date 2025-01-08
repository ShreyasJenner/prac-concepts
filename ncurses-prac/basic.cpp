extern "C" {
#include <menu.h>
#include <ncurses.h>
#include <panel.h>
}

int main() {
  WINDOW *wins[3];
  PANEL *panels[3];

  initscr();
  cbreak();
  noecho();

  wins[0] = newwin(10, 40, 2, 4);
  wins[1] = newwin(10, 40, 2 + 1, 4 + 5);
  wins[2] = newwin(10, 40, 2 + 2, 4 + 10);

  for (int i = 0; i < 3; i++) {
    box(wins[i], 0, 0);
    panels[i] = new_panel(wins[i]);
  }
  update_panels();
  doupdate();

  getch();

  endwin();

  return 0;
}
