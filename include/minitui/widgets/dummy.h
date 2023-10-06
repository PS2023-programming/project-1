#ifndef DUMMY_H__
#define DUMMY_H__

#include "../geometry.h"
#include "../event.h"
#include "../widget.h"
#include <debug.h>
#include <basics.h>

struct tui_dummy : public tui_widget {
  char *message;
  int msg_length;
  
  virtual tui_event *on_event(tui_event *event);
  virtual void draw(tui_point point) const;
};

#endif