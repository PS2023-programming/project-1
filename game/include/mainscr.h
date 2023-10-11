#ifndef MAINSCR_H__
#define MAINSCR_H__

#include <minitui.h>

const tui_formatter default_formatter = (tui_formatter) {tui_color::red_h, tui_color::none};

struct mainscr : public tui_canvas {

  mainscr(tui_rect area, tui_widget *parent);
  virtual ~mainscr() {}
  
  virtual tui_event *on_event(tui_event *event);
  
  void set_global_formatter(tui_formatter formatter);
  void set_central_message(const char *message, tui_formatter formatter = default_formatter);
};

#endif