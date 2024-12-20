#include <ncurses.h>
#include <unistd.h>

int map_into_range(int val, int term_width, int data_max) {
    return (val*term_width)/data_max;
}

int main() {
    /* Declaration */
    int i,x,y;

    /* Init ncurses */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    scrollok(stdscr,TRUE);

    printw("%d\n",getmaxx(stdscr));
    getch();
    for(i=0;i<75;i++) {
        mvprintw(0,map_into_range(i,getmaxx(stdscr), 
                    75),"#");
        mvprintw(1,0,"%d",i);
        refresh();
        usleep(100*1000);
    }
    getch();

    endwin();

    return 0;
}
