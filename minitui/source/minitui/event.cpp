// An input FSM

#include <ansi.h>
#include <debug.h>
#include <minitui.h>
#include <basics.h>
const int x = '[';

#define BUFSZ 1024
tui_event event_queue[BUFSZ];
// tui_event_t 

bool mouse_enabled = false;

tui_event *tui_get_event() {
  char ch = getchar();
  switch (ch)
  {
  // ESC
  case ESC_CODE: {
    ch = getchar();
    switch (ch)
    {
    // CSI
    case '[':
      // return tui_event_t
      break;
    
    // case ''

    default:
      break;
    }
    break;
  }
  
  default:
    break;
  }
  return NULL;
}

int tui_exec() {
  while (true) {
    tui_event *event = tui_get_event();
    if (!event) {
      Error("A NULL event returned!");
    }
    if (event->event_type == TUI_MOUSE_EVENT && !mouse_enabled) continue;

    tui_widget *current = focus;

    // find the mouse's target
    if (event->event_type == TUI_MOUSE_EVENT) {
      auto mouse_event = (tui_mouse_event *) event->event_body;
      tui_point mouse_point = (tui_point) {
        .x = mouse_event->x,
        .y = mouse_event->y
      };

      for (auto it = wl_tail; it; it = it->prev) {
        if (mouse_point.is_in(it->body->area)) {
          // change focus if it is a click
          if ((mouse_event->type == MOUSE_LEFT_CLICK || mouse_event->type == MOUSE_RIGHT_CLICK || mouse_event->type == MOUSE_MID_CLICK) && mouse_event->ispress) {
            focus = it->body;
          }
          current = it->body;
          break;
        }
      }
    }
    
    while (current && event) {
      event = current->on_event(event);
      current = current->parent;
    }

    if (event && event->event_type == TUI_EXIT_EVENT) {
      auto exit_event = (tui_exit_event *) event->event_body;
      return exit_event->retcode;
    }

    if (event) {
      if (event->event_body) free(event->event_body);
      free(event);
    }
  }
  // Impossible
  return -1;
}