#ifdef _WIN32
#include <windows.h>
#endif

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int main() {

#ifdef _WIN32

  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  memset(&si, 0, sizeof(si));
  memset(&pi, 0, sizeof(pi));
  // HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  si.cb = sizeof(si);
  si.wShowWindow = SW_SHOW;
  si.dwFlags = STARTF_USESHOWWINDOW;

  CreateProcess(NULL, "wt --size 150,40 --pos 100,100 build/game", NULL, NULL, true, 0, NULL, NULL, &si, &pi);

  // WaitForSingleObject

  system("cat build\\game.log");

#endif

}