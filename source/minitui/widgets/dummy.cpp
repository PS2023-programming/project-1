
#include <minitui.h>

tui_event *
tui_dummy::on_event(tui_event *event) {
  if (!event || !event->event_body) {
    Error("Invalid event given!");
  }
  if (event->event_type == KEYBD_EVENT) {
    auto kbd_event = (tui_kbd_event *) event->event_body;
    if (kbd_event->code == 'q' || kbd_event->code == 'Q') {
      auto exit_event = CREATE_OBJ(tui_exit_event);
      exit_event->retcode = 0;
      if (event->event_body)
        free(event->event_body);
      event->event_type = EXIT_EVENT;
      event->event_body = exit_event;
      return event;
    }
  }
  if (event->event_body)
    free(event->event_body);
  free(event);
  return NULL;
}

