// An input FSM

#include <ansi.h>
#include <debug.h>
#include <minitui.h>
#include <basics.h>
#include <ui.h>
// tui_event_t 

bool mouse_enabled = false;

static
char
tui_getchar() {
  char ch = getchar();
  if (ch < '\x7f' && ch >= ' ')
    Trace("Get %c", ch);
  else
    Trace("Get %u", (uint8_t) ch);
  return ch;
}

static
tui_event *
tui_get_ansi_event() {
  Debug("Enter an ansi event");
  char ch = tui_getchar();
  switch (ch) 
  {
  case '[': {
    ch = tui_getchar();
    switch (ch) {
    case '<': {
      Debug("Get a mouse event");
      char mouse_str[512];
      int mouse_str_len;
      while(ch != 'm' && ch != 'M') {
        ch = tui_getchar();
        mouse_str[mouse_str_len++] = ch;
      }
      auto event = CREATE_OBJ(tui_event);
      auto mouse_event = CREATE_OBJ(tui_mouse_event);
      return NULL;
    }
    default: {
      if (isdigit(ch)) {
        while (isdigit(ch)) {
          ch = tui_getchar();
        }
        if (ch == '~') {
          Debug("Get a ^[d~ event");
          return NULL;
        }
        return NULL;
      } else if ((ch <= 'Z' && ch >= 'A') || (ch >= 'a' && ch <= 'z')) {
        return NULL;
      }
      return NULL;
    }
    } 
    return NULL;
  }
  case 'O': {
    ch = tui_getchar();
    return NULL;
  }
  default: {
    return NULL;
  }
  }
  return NULL;
}

tui_event *
tui_get_event() {
#ifdef _WIN64
  int is_kbd = _kbhit();
#endif
  char ch = tui_getchar();
  switch (ch)
  {
  // ESC
  case ESC_CODE: {
    return tui_get_ansi_event();
  }

  case '\x3': {
    auto event = CREATE_OBJ(tui_event);
    auto exit_event = CREATE_OBJ(tui_exit_event);
    
    event->event_type = TUI_EXIT_EVENT;
    event->event_body = exit_event;
    exit_event->retcode = 0;
    return event;
  }

  default: {
    Debug("Get a key!");
    auto event = CREATE_OBJ(tui_event);
    auto kbd_event = CREATE_OBJ(tui_kbd_event);

    event->event_type = TUI_KEYBD_EVENT;
    event->event_body = kbd_event;
    kbd_event->code = ch;
    return event;
  }

  }
  return NULL;
}

int 
tui_exec() {

  Debug("start game mainloop");
  
  // There should be a top widget
  if (!wl_head) {
    Error("No top widget");
  }
  // set top widget as default focus
  focus = wl_head->body;

  while (true) {
    for (auto it = wl_head; it; it = it->next) {
      if (it->body->get_updated()) {
        tui_draw();
        break;
      }
    }

    tui_event *event = tui_get_event();
    if (!event) {
      Debug("A NULL event returned.");
      continue;
    }
    
    if (event->event_type == TUI_EXIT_EVENT) {
      auto exit_event = (tui_exit_event *) event->event_body;
      return exit_event->retcode;
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

      for (auto it = wl_head; it; it = it->next) {
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
      tui_widget *next = current->parent;
      if (event && event->event_type == TUI_EXIT_EVENT) {
        tui_erase_widget(current);
        delete current;
      }
      current = next;
    }

    // top widget exits, end the exection loop
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