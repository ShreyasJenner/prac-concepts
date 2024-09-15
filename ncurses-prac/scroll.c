
#include <ncurses.h>

int main() {
    initscr();              // Initialize the window
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable function keys (like arrows)
    mousemask(ALL_MOUSE_EVENTS, NULL); // Enable all mouse events
    MEVENT event;           // Struct to store mouse events

    while(true) {
        int ch = getch();   // Wait for user input

        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON4_PRESSED) {
                    // Mouse scroll up
                    printw("Scroll up detected at position (%d, %d)\n", event.x, event.y);
                } else if (event.bstate & BUTTON5_PRESSED) {
                    // Mouse scroll down
                    printw("Scroll down detected at position (%d, %d)\n", event.x, event.y);
                }
            }
        } else if (ch == 'q') {
            break;          // Exit on 'q' key press
        }
        refresh();
    }

    endwin();               // End curses mode
    return 0;
}

