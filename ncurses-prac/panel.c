#include <ncurses.h>
#include <panel.h>

#define WIN_NO 3

int main() {
    /* Declaration */
    int i, ch, itr,
        rows,cols,y,x;
    bool flag;

    WINDOW *wins[WIN_NO];
    PANEL *panels[WIN_NO];

    /* Initialization */
    itr = 0;
    flag = true;
    rows = getmaxy(stdscr)/10;
    cols = getmaxx(stdscr)/10;
    y = 10;
    x = 10;

    initscr();
    raw();
    noecho();

    for(i=0;i<3;i++) {
        wins[i] = newwin(0, 0, 0, 0);
    }

    for(i=0;i<WIN_NO;i++) {
        box(wins[i], 0, 0);
    }

    for(i=0;i<WIN_NO;i++) {
        panels[i] = new_panel(wins[i]);
    }

    for(i=0;i<WIN_NO;i++) {
        wmove(wins[i], 5, 5);
        wprintw(wins[i], "This is window %d\n",i);
    }

    update_panels();
    doupdate();

    while(flag) {
        ch = getch();
        switch (ch) {
            case 'q':
                flag = false;
                break;

            case 'l':
                itr = (itr+1)%WIN_NO;
                top_panel(panels[itr]);
                break;
        }
        update_panels();
        doupdate();
    }

    endwin();

    return 0;
}
