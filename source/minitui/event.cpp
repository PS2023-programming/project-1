// An input FSM

#include <ansi.h>
#include <debug.h>
#include <minitui.h>
#include <basics.h>
const int x = '[';

#define BUFSZ 1024
tui_event event_queue[BUFSZ];
// tui_event_t 

tui_event tui_get_event() {
  char ch = getchar();
  switch (ch)
  {
  // ESC
  case ESC_CODE: {
    ch = getchar();
    switch (ch)
    {
    // CSI
    case '[':
      // return tui_event_t
      break;
    
    // case ''

    default:
      break;
    }
    break;
  }
  
  default:
    break;
  }
}