#ifndef MINITUI_H__
#define MINITUI_H__

#include "geometry.h"
#include "event.h"
#include "widget.h"
#include "ui.h"
#include "widgets/msgbox.h"
#include "widgets/dummy.h"

#define CREATE_OBJ(type) ((type *) malloc(sizeof(type)))

void tui_init();
 
#endif