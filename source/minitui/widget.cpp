#include <minitui.h>

tui_point
tui_widget::position_interpreter (
  tui_point point
) const {
  if (!point.is_in(area)) {
    Warn("Point not in widget!");
  }
  return point - area.start;
}