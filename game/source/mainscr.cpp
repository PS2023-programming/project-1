#include <minitui.h>
#include <mainscr.h>

mainscr::mainscr(
  tui_rect area,
  tui_widget *parent
) : tui_canvas(area, parent) {
}

tui_event *
mainscr::on_event(
  tui_event *event
) {
  Debug("Triggered event on mainscr");
  if (!event || !event->event_body) {
    Error("Invalid event given!");
  }
  if (event->event_type == TUI_KEYBD_EVENT) {
    auto kbd_event = (tui_kbd_event *) event->event_body;
    if (kbd_event->code == 'q' || kbd_event->code == 'Q') {
      FREE_EVENT_BODY(event);
      auto exit_event = CREATE_OBJ(tui_exit_event);
      exit_event->retcode = 0;
      
      event->event_type = TUI_EXIT_EVENT;
      event->event_body = exit_event;
      return event;
    }
  }
  FREE_EVENT(event);
  return NULL;
}

void
mainscr::set_global_formatter(
  tui_formatter formatter
) {
  for (int i = 0; i < GLOB_HEIGHT; i++)
    for (int j = 0; j < GLOB_WIDTH; j++) {
      auto unit = (*this)[i][j];
      *(unit.formatter) = formatter;
    }
  set_updated();
  return ;
}

void 
mainscr::set_central_message(
  const char *message,
  tui_formatter formatter
) {
  int length = strlen(message);
  if (length >= area.width()) {
    Warn("The given message is too long!");
  }
  int x = area.height() / 2;
  int y = (area.width() - length) / 2;
  for (int i = 0; i < length; i++) {
    auto unit = (*this)[x][y+i];
    (*unit.content) = message[i];
    (*unit.formatter) = formatter;
  }
  set_updated();
}