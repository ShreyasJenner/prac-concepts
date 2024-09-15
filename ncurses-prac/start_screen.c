/*
 * Program file deals with the Initialization, creation and 
 * deallocation of the start screen of the media player
 * Program flow is as follows:
 * 1. start_screen_init -> initalize the start screen, creating
 * necessary windows, menus and items
 * 2. handle_keypress -> get the key pressed and then do action based 
 * on the key press
 * 3. select_file -> select an item and return the name of the item
 * 4. start_screen_deinit -> deinitialize created menus, items and panel 
 * windows
 */

#include <eti.h>
#include <stdlib.h>
#include <curses.h>
#include <error.h>
#include <panel.h>
#include <ncurses.h>
#include <menu.h>
#include <stdio.h>

#define FILE_SZ 10

/*
 * Function assigns a window, menu and items to a panel
 * It draws the menu and its items in the window
 * Menu, items and window must be freed later in deinit function
 * Returns 0 on success
 */
MENU *start_screen_init(PANEL **panel, char *filelist, int len) {
    /* Declaration */
    int i,
        x,y;
    char index[FILE_SZ];

    WINDOW *win;
    MENU *menu;
    ITEM **items;

    /* Initialization */
    getmaxyx(stdscr, y, x);

    /* create window and attach to panel */
    win = newwin(y-2, x, 0, 0);
    if(win == NULL) {
        fprintf(stderr, "window creation error\n"); 
        return NULL;
    }
    *panel = new_panel(win);

    /* create menu and items */
    items = (ITEM **)calloc(len+1, sizeof(ITEM *));
    if(items == NULL) {
        fprintf(stderr, "item space allocation\n");
        return NULL;
    }

    for(i=0;i<len;i++) {
        sprintf(index, "%d", i);
        items[i] = new_item(index, &filelist[i*FILE_SZ]);
        if(items[i] == NULL) {
            fprintf(stderr, "Item %d creation\n",i);
            return NULL;
        }
    }
    items[len] = NULL;

    menu = new_menu(items);
    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, y-4, x-2, 1, 1));
    set_menu_mark(menu, "*");

    /* post menu */
    if(post_menu(menu) != E_OK) {
        fprintf(stderr, "Posting menu error\n");
        return NULL;
    }
    
    box(win, 0, 0);

    return menu;
}

/*
 * Function to handle key code press
 * Is passed the key code of pressed key from main program
 * Returns 0 on success
 */
int handle_keypress(WINDOW *win, int key) {
    switch (key) {
        case 'j':
            wprintw(win, "%c\n", key);
            break;

        case 'k':
            wprintw(win, "%c\n", key);
            break;

        case 'l':
            wprintw(win, "%c\n", key);
            break;
    
        case 'h':
            wprintw(win, "%c\n", key);
            break;

        default:
            break;
    }

    return 0;
}

/*
 * Function creates a menu for a panel
 * It allocates the space for necessary items
 */
MENU *select_file(PANEL **panel) {
    /* Declaration */
    ITEM **items, *cur_item;
    MENU *menu;

    return NULL;
}

/*
 * Function deinits all allocated space for windows, menus, 
 * items and panels
 * Should be called at the end of the program
 * Returns 0 on success
 */
int start_screen_deinit(WINDOW *panwin, MENU *menu) {
    /* Declaration */
    int i;
    ITEM **items;
    
    /* clean up menu and its items */
    unpost_menu(menu);
    items = menu_items(menu);
    for(i=0;i<item_count(menu);i++) {
        if(free_item(items[i])!=E_OK) {
            fprintf(stderr, "Freeing items %d error\n",i);
            return -1;
        }
    }
    if(free_menu(menu)!=E_OK) {
        fprintf(stderr, "Freeing menu error\n");
        return -1;
    }

    /* delete window and notify if error */
    if(delwin(panwin) == ERR) {
        fprintf(stderr, "Deleting panel window error\n");
        return -1;
    }


    return 0;
}




/* Driver Code */
int main() {
    /* Declaration */
    WINDOW *panwin;
    PANEL *panel;
    MENU *menu;
    char filelist[][FILE_SZ] = {
        "power",
        "not",
        "so",
        "great"
    };

    /* start ncureses */
    initscr();
    raw();
    noecho();

    menu = start_screen_init(&panel,&filelist[0][0],4);
    update_panels();
    doupdate();

    handle_keypress(panel_window(panel),getch());
    update_panels();
    doupdate();

    getch();

    /* Clean up */
    panwin = panel_window(panel);
    del_panel(panel);
    start_screen_deinit(panwin,menu);
    endwin();

    return 0;
}
