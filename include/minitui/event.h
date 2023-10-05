#ifndef EVENT_H__
#define EVENT_H__

// SGR mouse event codes
#define MOUSE_SCROLL 64
#define MOUSE_LEFT_CLICK 0
#define MOUSE_MID_CLICK 1
#define MOUSE_RIGHT_CLICK 2 
#define MOUSE_MOVE 35

struct tui_event {
  int event_type;
  void *event_body;
};

struct tui_mouse_event {
  int type;
  int x, y;
  bool ispress;
};

// #define F1
struct tui_kbd_event {
  char code;
};

#ifndef __cplusplus
typedef struct tui_event tui_event;
typedef struct tui_mouse_event_info tui_mouse_event;
#endif


#endif