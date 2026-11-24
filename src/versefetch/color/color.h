#ifndef VERSEFETCH_COLOR_H
#define VERSEFETCH_COLOR_H


#define RESET "\033[0;m"


typedef const char *Color;

const char *color_get_ansi(const char *name);
const char *color_get_bright_ansi(const char *name);


#endif
