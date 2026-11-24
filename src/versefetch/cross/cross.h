#ifndef VERSEFETCH_CROSS_H
#define VERSEFETCH_CROSS_H


#define CROSS_ROWS	8
#define CROSS_WIDTH	16


typedef const char Cross[8][17];

const Cross *versefetch_cross_by_name(const char *name);


#endif
