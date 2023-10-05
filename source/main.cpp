#include <basics.h>
#include <debug.h>
#include <minitui.h>

int main() {

  tui_init();

  while (true) {
    int ch = getchar();
    if (ch == '\x3') break;
    Info("Get %d", ch);
  }

  Info("Hello, project1!");
}
