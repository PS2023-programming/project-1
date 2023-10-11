#ifndef FORMATTER_H__
#define FORMATTER_H__

enum class tui_color {
  none = 0,
  red,
  blue,
  green,
  yellow,
  meganta,
  cyan,
  white,
  red_h,
  blue_h,
  green_h,
  yellow_h,
  meganta_h,
  cyan_h,
  white_h,
};

static inline void foreset(tui_color forecolor) {
  switch (forecolor)
  {
  case tui_color::red:
    ANSI_CMD(ANSI_RED_NF);
    break;
  case tui_color::red_h:
    ANSI_CMD(ANSI_RED_HF);
    break;
  default:
    break;
  }
}

static inline void backset(tui_color backcolor) {
  switch (backcolor)
  {
  case tui_color::white_h:
    ANSI_CMD(ANSI_WHITE_HG);
    break;
  default:
    break;
  }
}

struct tui_formatter {
  tui_color fore_color;
  tui_color back_color;
};

#endif