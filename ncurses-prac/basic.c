#include <ncurses.h>

int main() {
  int c;
  initscr();
  keypad(stdscr, true);

  printw("%d\n", getch());
  refresh();

  getch();
  endwin();
  return 0;
}
