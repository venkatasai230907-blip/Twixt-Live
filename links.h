// links.h
#ifndef LINKS_H
#define LINKS_H

typedef struct linkage {
    int x1, y1;
    int x2, y2;
} linkage;

extern linkage linkB[1000];
extern linkage linkR[1000];
extern int linkBcount;
extern int linkRcount;

void add_links_for_new_pin(int x, int y, char turn, char board[24][24]);
int point_has_link(int x, int y, char color);

#endif
