#include <minitui.h>

tui_widget *focus;
tui_widget_list *wl_head;

static
void
tui_append_widget (
  tui_widget *widget
) {
  auto widget_list = CREATE_OBJ(tui_widget_list);
  widget_list->body = widget;
  widget_list->next = wl_head;
  wl_head = widget_list;
}

static
void
tui_delete_widget (
  tui_widget *widget
) {
  /* TODO: update the linked list */
}

tui_widget *full_map[GLOB_HEIGHT][GLOB_WIDTH];

void
tui_reg_widget(
  tui_widget *widget
) {
  
  /* TODO: register the widget on full_map */

  // add the widget to linked-list
  tui_append_widget(widget);
  widget->set_updated();
}

void
tui_erase_widget(
  tui_widget *widget
) {
  tui_delete_widget(widget);
  if (focus == widget) {
    focus = widget->parent;
    if (!focus) {
      Info("Erasing top focus");
    }
  }
  
  /* TODO: update full map */

  return ;
}

void
tui_draw() {
  Debug("Trigger drawing!");

  /* TODO: draw the interface */

  // reset updated status
  for (auto it = wl_head; it; it = it->next)
    it->body->reset_updated();
}