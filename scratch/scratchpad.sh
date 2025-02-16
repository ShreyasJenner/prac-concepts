#!/bin/bash

SCRATCHPAD_CLASS="scratchpad-nvim"
TERMINAL=$TERM # Change to your preferred terminal
EDITOR="nvim"

# Check if the scratchpad window exists
WINDOW_ID=$(bspc query -N -n .window.$SCRATCHPAD_CLASS 2>/dev/null)

if [ -n "$WINDOW_ID" ]; then
  # If the window is focused, hide it; otherwise, focus it
  if [ "$(bspc query -N -n focused 2>/dev/null)" = "$WINDOW_ID" ]; then
    bspc node "$WINDOW_ID" --flag hidden
  else
    bspc node "$WINDOW_ID" --flag hidden=off --focus
  fi
else
  # Launch the terminal with nvim in a floating scratchpad
  bspc rule -a \* -o state=floating sticky=on layer=above rectangle=720x360+1190+10 &&
    $TERMINAL --class "$SCRATCHPAD_CLASS" --working-directory ~/Documents/scratch-pad/ -e $EDITOR
fi
