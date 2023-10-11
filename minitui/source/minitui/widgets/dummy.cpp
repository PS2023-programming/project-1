#include <minitui.h>

tui_event *
tui_dummy::on_event(
  tui_event *event
) {
  return NULL;
}

void
tui_dummy::draw(
  tui_point point
) const {
  ANSI_CMD(ANSI_RST);
  putchar(' ');
  ANSI_CMD(ANSI_RST);
}
