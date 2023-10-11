#ifndef MINITUI_H__
#define MINITUI_H__

#include "geometry.h"
#include "event.h"
#include "widget.h"
#include "ui.h"
#include "widgets/msgbox.h"
#include "widgets/dummy.h"
#include "widgets/canvas.h"

#define GLOB_WIDTH 100
#define GLOB_HEIGHT 40

#define CREATE_OBJ(type) ((type *) malloc(sizeof(type)))

#define FREE_EVENT_BODY(event) do {\
  if (event->event_body)\
    free(event->event_body); \
} while(0)

#define FREE_EVENT(event) do {\
  if (event->event_body)\
    free(event->event_body); \
  free(event);\
} while(0)

void tui_init();
 
#endif