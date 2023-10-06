#ifndef MSGBOX_H__
#define MSGBOX_H__

#include "../geometry.h"
#include "../event.h"
#include "../widget.h"
#include <debug.h>

struct tui_msgbox : public tui_widget {
  char *message;
  int msg_length;
  static const char hint[];

  virtual tui_event *on_event(tui_event *event);
  virtual void draw(tui_point point) const;
};

#endif