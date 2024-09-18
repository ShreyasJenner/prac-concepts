/*
 * Program file deals with the Initialization, creation and
 * deallocation of the start screen of the media player
 * Program flow is as follows:
 * 1. start_screen_init -> initalize the start screen, creating
 * necessary windows, menus and items
 * 2. handle_keypress -> get the key pressed and then do action based
 * on the key press
 * 3. start_screen_deinit -> deinitialize created menus, items and panel
 * windows
 */

#include <curses.h>
#include <error.h>
#include <menu.h>
#include <ncurses.h>
#include <panel.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define FILE_SZ 10

/*
 * Function assigns a window, menu and items to a panel
 * It draws the menu and its items in the window
 * Menu, items and window must be freed later in deinit function
 * Returns 0 on success
 */
MENU *start_screen_init(PANEL **panel, char filelist[][2][FILE_SZ], int len) {
  /* Declaration */
  int i, x, y;

  WINDOW *win;
  MENU *menu;
  ITEM **items;

  /* Initialization */
  getmaxyx(stdscr, y, x);

  /* create window and attach to panel */
  win = newwin(y - 2, x, 0, 0);
  if (win == NULL) {
    fprintf(stderr, "window creation error\n");
    return NULL;
  }
  *panel = new_panel(win);

  /* create menu and items */
  items = (ITEM **)calloc(len + 1, sizeof(ITEM *));
  if (items == NULL) {
    fprintf(stderr, "item space allocation\n");
    return NULL;
  }

  /* Loop to create the items and their descriptions */
  for (i = 0; i < len; i++) {
    items[i] = new_item(filelist[i][0], filelist[i][1]);
    if (items[i] == NULL) {
      fprintf(stderr, "Item %d creation\n", i);
      return NULL;
    }
  }
  items[len] = NULL;

  menu = new_menu(items);
  set_menu_win(menu, win);
  set_menu_sub(menu, derwin(win, y - 4, x - 2, 1, 1));
  set_menu_mark(menu, "*");

  /* post menu */
  if (post_menu(menu) != E_OK) {
    fprintf(stderr, "Posting menu error\n");
    return NULL;
  }

  box(win, 0, 0);

  return menu;
}

/*
 * Function to handle key code press
 * Is passed the key code of pressed key from main program
 * Returns name of selected file else NULL
 */
const char *handle_keypress(MENU *menu, int key) {
  /* Declaration */
  const char *sel;

  /* Initialization */
  sel = NULL;

  switch (key) {
  case 'j':
    if (item_index(current_item(menu)) == item_count(menu) - 1) {
      menu_driver(menu, REQ_FIRST_ITEM);
    } else {
      menu_driver(menu, REQ_DOWN_ITEM);
    }
    break;

  case 'k':
    if (item_index(current_item(menu)) == 0) {
      menu_driver(menu, REQ_LAST_ITEM);
    } else {
      menu_driver(menu, REQ_UP_ITEM);
    }
    break;

  case 'l':
    menu_driver(menu, REQ_LEFT_ITEM);
    break;

  case 'h':
    menu_driver(menu, REQ_RIGHT_ITEM);
    break;

    // enter key to return item description
  case 10:
    sel = item_description(current_item(menu));
    break;

  default:
    break;
  }

  return sel;
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
  for (i = 0; i < item_count(menu); i++) {
    /* free the index array allocated */
    if (free_item(items[i]) != E_OK) {
      fprintf(stderr, "Freeing items %d error\n", i);
      return -1;
    }
  }
  free(items);

  if (free_menu(menu) != E_OK) {
    fprintf(stderr, "Freeing menu error\n");
    return -1;
  }

  /* delete window and notify if error */
  if (delwin(panwin) == ERR) {
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

  char filelist[][2][FILE_SZ] = {
      {"0", "power"}, {"1", "not"}, {"2", "so"}, {"3", "great"}};
  const char *sel;
  int ch;

  /* start ncureses */
  initscr();
  raw();
  noecho();

  menu = start_screen_init(&panel, filelist, 4);
  update_panels();
  doupdate();

  // loop to run menu traversal
  while ((ch = getch()) != 'q') {
    sel = handle_keypress(menu, ch);
    if (sel != NULL) {
      fprintf(stderr, "%s", sel);
    }
    update_panels();
    doupdate();
  }

  /* Clean up */
  panwin = panel_window(panel);
  del_panel(panel);
  start_screen_deinit(panwin, menu);
  endwin();

  return 0;
}
