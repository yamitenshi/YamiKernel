#ifndef COLORS_H_
#define COLORS_H_

#define FB_BLACK    0
#define FB_BLUE     1
#define FB_GREEN    2
#define FB_CYAN     3
#define FB_RED      4
#define FB_MAGENTA  5
#define FB_BROWN    6
#define FB_LGREY    7
#define FB_DGREY    8
#define FB_LBLUE    9
#define FB_LGREEN   10
#define FB_LCYAN    11
#define FB_LRED     12
#define FB_LMAGENTA 13
#define FB_LBROWN   14
#define FB_WHITE    15

typedef struct {
    unsigned short fg;
    unsigned short bg;
} __attribute__((packed)) color;

#endif
