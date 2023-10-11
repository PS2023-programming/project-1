#include <basics.h>
#include <debug.h>
#include <minitui.h>
#include <mainscr.h>

int main() {
  
  auto mainscr_0 = new mainscr(
    (tui_rect) {
      .start = (tui_point) {0, 0},
      .end = (tui_point) {GLOB_HEIGHT-1, GLOB_WIDTH-1}
    },
    NULL
  );

  mainscr_0->set_global_formatter(
    (tui_formatter) {
      .fore_color = tui_color::none,
      .back_color = tui_color::white_h
    }
  );

  mainscr_0->set_central_message(
    "Hello NJU Universalis!",
    (tui_formatter) {
      .fore_color = tui_color::red_h,
      .back_color = tui_color::white_h
    }
  );

  tui_reg_widget(mainscr_0);

  tui_init();
  ansi_title("NJU Universalis");

  int ret_value = tui_exec();
  if (ret_value != 0)
    Warn("tui_exec() returns with a non-zero value %d", ret_value);
  
  return ret_value;
}
