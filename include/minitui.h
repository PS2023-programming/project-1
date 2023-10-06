#ifndef MINITUI_H__
#define MINITUI_H__

#include "minitui/geometry.h"
#include "minitui/event.h"
#include "minitui/widget.h"
#include "minitui/ui.h"
#include "minitui/widgets/msgbox.h"
#include "minitui/widgets/dummy.h"

#define CREATE_OBJ(type) ((type *) malloc(sizeof(type)))

void tui_init();
 
#endif