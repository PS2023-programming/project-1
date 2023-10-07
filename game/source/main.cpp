#include <basics.h>
#include <debug.h>
#include <minitui.h>

int main() {

#ifdef _WIN32
  freopen("build/game.log", "w", stderr);
#endif

  tui_init();

  while (true) {
    int ch = getchar();
    if (ch == '\x3') break;
    Info("Get %d", ch);
  }

  Info("Hello, project1!");
}
