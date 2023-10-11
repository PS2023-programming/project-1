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
  
  /* TODO: Deal the event so as to make the widget exits on `q`  */

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

  /* TODO: write the message into canvas */

  set_updated();
}