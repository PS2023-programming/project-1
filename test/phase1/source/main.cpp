#include <basics.h>
#include <debug.h>
#include <minitui.h>
#include <mainscr.h>

int main() {

  /* TODO: Add a mainscr widget and register it to ui module */

  tui_init();
  ansi_title("NJU Universalis");
  
  int ret_value = tui_exec();
  if (ret_value != 0)
    Warn("tui_exec() returns with a non-zero value %d", ret_value);
  
  return ret_value;
}
