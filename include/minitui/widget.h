#ifndef WIDGET_H__
#define WIDGET_H__

#include "geometry.h"
#include "event.h"
#include <debug.h>

struct tui_widget {
  tui_rect area;
  bool updated;
  
  tui_point position_interpreter(tui_point point) const;
  
  void set_updated() {updated = true;};
  bool get_updated() const {return updated;}
  
  tui_widget *parent;
  std::vector<tui_widget *> children;

  virtual tui_event *on_event(tui_event *event) = 0;
  virtual void draw(tui_point point) const = 0;
};

#endif