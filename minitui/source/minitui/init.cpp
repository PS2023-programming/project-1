#include <debug.h>
#include <basics.h>

void 
tui_init() {
  freopen("build/game.log", "w", stderr);

  /* TODO: set the buffer of stdout */

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  #ifdef _WIN64
    Info("We are in windows, enabling virtual terminal input.");
    HANDLE stdin_handle = GetStdHandle(STD_INPUT_HANDLE);
    if (stdin_handle == INVALID_HANDLE_VALUE) {
      Error("GetStdHandle() failed");
    }
    DWORD stdin_mode;
    if (!GetConsoleMode(stdin_handle, &stdin_mode)) {
      Error("GetConsoleMode() failed");
    }
    
    stdin_mode &= ~ENABLE_ECHO_INPUT;
    stdin_mode &= ~ENABLE_LINE_INPUT;
    stdin_mode &= ~ENABLE_INSERT_MODE;
    stdin_mode |= ENABLE_MOUSE_INPUT;
    stdin_mode &= ~ENABLE_PROCESSED_INPUT;
    stdin_mode &= ~ENABLE_QUICK_EDIT_MODE;
    stdin_mode |= ENABLE_EXTENDED_FLAGS;  /* Needed when changing _QUICK_EDIT_MODE */
    stdin_mode |= ENABLE_WINDOW_INPUT;
    stdin_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

    if (!SetConsoleMode(stdin_handle, stdin_mode)) {
      Error("SetConsoleMode() failed");
    }
    // printf("\033=");
    Info("Enable virtual terminal input success.");
  #else
    Info("We are in Linux, doing some necessary initiation");
  
    ANSI_ENABLE(ANSI_MOUSE);
    ANSI_ENABLE(ANSI_SGR);
    ANSI_ENABLE(ANSI_ANY_EVENT);

    termios termios_0;
    memset(&termios_0, 0, sizeof(termios));
    tcgetattr(1, &termios_0);
    
    termios_0.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    // termios_0.c_oflag &= ~OPOST;
    termios_0.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    termios_0.c_cflag &= ~(CSIZE | PARENB);
    termios_0.c_cflag |= CS8;

    if (tcsetattr(1, TCSANOW, &termios_0) == 0) 
      Info("Initiation Finished!");
    else
      Error("Termios set failed!");

  #endif

  // enable paste mode
  ANSI_ENABLE(ANSI_PASTE);
  // hide the cursor
  ANSI_DISABLE(ANSI_CURSOR);
  
  // ANSI_CMD(ANSI_ENABLE(ANSI_ALTER_BUF));
}
