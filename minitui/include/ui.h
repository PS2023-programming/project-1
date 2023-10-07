#ifndef UI_H__
#define UI_H__

extern tui_widget *focus;

struct tui_widget_list {
  tui_widget *body;
  tui_widget_list *next, *prev;
};

extern tui_widget_list *wl_head, *wl_tail;

#endif