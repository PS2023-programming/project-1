#ifdef _WIN32
#include <windows.h>
#endif

#include <ansi.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static int cmd_help(char** argv, int argc);

static int cmd_log(char** argv, int argc) {
  system("cat build\\game.log");
  ANSI_CMD(ANSI_RST);
}

static int cmd_game(char** argv, int argc) {

#ifdef _WIN32

  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  memset(&si, 0, sizeof(si));
  memset(&pi, 0, sizeof(pi));

  si.cb = sizeof(si);
  si.wShowWindow = SW_SHOW;
  si.dwFlags = STARTF_USESHOWWINDOW;

  CreateProcess(NULL, "wt --size 100,41 --pos 100,100 build/game", NULL, NULL, true, 0, NULL, NULL, &si, &pi);

#endif

}

static struct {
  const char* name;
  const char* description;
  int (*handler) (char**, int);
} cmd_table[] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "game", "Activate the game", cmd_game},
  { "log",  "Display log information", cmd_log},
};
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
#define CNT_CMD ARRLEN(cmd_table)

void cmd_mainloop() {
  char str[1024];
  printf("Welcome to the game launcher, use `help` for help.\n");
  while (1) {
    printf(">> ");
    fgets(str, 1024, stdin);
    *strchr(str, '\n') = '\0';

    int argc = 0;
    char* argv[32];
    char* cmd = strtok(str, " ");
    argv[argc++] = cmd;
    while (cmd = strtok(NULL, " ")) {
      argv[argc++] = cmd;
    }
    argv[argc] = NULL;

    if (argv[0] == NULL) { continue; }
    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0) break;

    int cmd_num;
    for (cmd_num = 0; cmd_num < CNT_CMD; cmd_num++) {
      if (strcmp(argv[0], cmd_table[cmd_num].name) == 0) {
        cmd_table[cmd_num].handler(argv, argc);
        break;
      }
    }

    if (cmd_num == CNT_CMD) { printf("Unknown command '%s'\n", argv[0]); }
  }
}



int main() {

  cmd_mainloop();

  return 0;
}

static int cmd_help(char** argv, int argc) {
  if (argc == 1) {
    /* no argument given */
    for (int i = 0; i < CNT_CMD; i++) {
      printf("%s\t - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    int i;
    bool flag[CNT_CMD];
    memset(flag, 0, sizeof(flag));
    for (int cur = 1; cur < argc; cur++) {
      for (i = 0; i < CNT_CMD; i++) {
        if (strcmp(argv[cur], cmd_table[i].name) == 0) {
          if (!flag[i]) {
            printf("%s\t - %s\n", cmd_table[i].name, cmd_table[i].description);
          }
          flag[i] = true;
          break;
        }
      }
      if (i == CNT_CMD) printf("Unknown command '%s'\n", argv[cur]);
    }
  }
  return 0;
}
