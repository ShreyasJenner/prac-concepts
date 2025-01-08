#include "comp.hpp"

ftxui::Component basic_component() {
  ftxui::Component doc;

  doc = ftxui::Renderer(
      [] { return ftxui::vbox({ftxui::vtext("this is vertical")}); });

  return doc;
}

void screen() {
  ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();

  ftxui::Component doc = basic_component();

  screen.Loop(doc);
}
