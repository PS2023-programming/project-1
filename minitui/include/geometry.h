#ifndef GEOMETRY_H__
#define GEOMETRY_H__

struct tui_rect;

struct tui_point {
  int x, y;
  bool is_valid() const;
  bool is_in(const tui_rect &rect) const;
  tui_point operator - (const tui_point &b) const;
};

struct tui_rect {
  tui_point start, end;
  int height() const;
  int width() const;
};

extern tui_rect global_rect;

#endif