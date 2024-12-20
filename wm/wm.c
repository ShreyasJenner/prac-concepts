#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Display *dsp;
  Window win;

  dsp = XOpenDisplay(NULL);
  if (dsp == NULL) {
    printf("XOpenDisplay error\n");
    exit(1);
  }

  RootWindow(dsp, 0);
  win = XCreateSimpleWindow(dsp, RootWindow(dsp, 0), 0, 0, 300, 150, 0,
                            0xFFFFFF, 0x000000);

  XStoreName(dsp, win, "X Window");

  XMapWindow(dsp, win);
  XFlush(dsp);

  getchar();

  XUnmapWindow(dsp, win);
  XDestroyWindow(dsp, win);
  XCloseDisplay(dsp);

  return 0;
}
