#include <ncurses.h>

int main() {
    int c;
    initscr();

    printw("%d\n",getmaxx(stdscr));
    refresh();

    getch();
    endwin();
    return 0;
}
