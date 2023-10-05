#ifndef DEBUG_H__
#define DEBUG_H__

#include <ansi.h>

extern const char *log_level_name[];
extern int log_level;

#define _Log(...) fprintf(stderr, __VA_ARGS__)
// #define _Log_stderr(...) fprintf(stderr, __VA_ARGS__)

#define Log(level, ansi_fmt, fmt, ...) _Log(ANSI_FMT("%s [%s:%d %s] " fmt "\n", ansi_fmt), log_level_name[level], __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#define Plain(fmt, ...) _Log(fmt "\n", ## __VA_ARGS__)

#define Error(fmt, ...) do {\
  Log(5, ANSI_RED, fmt, ## __VA_ARGS__); \
  exit(-1); \
} while(0)
 
#define Info(fmt, ...) Log(3, ANSI_RST, fmt, ## __VA_ARGS__)
#define Debug(fmt, ...) Log(2, ANSI_RST, fmt, ## __VA_ARGS__)
#define Warn(fmt, ...) Log(4, ANSI_RST, fmt, ## __VA_ARGS__)

#endif