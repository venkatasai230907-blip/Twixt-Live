#include <stdio.h>
#include <stdlib.h>
#include "links.h"
extern char board[24][24];
linkage linkB[1000];
linkage linkR[1000];
int linkBcount = 0;
int linkRcount = 0;
int dx[8] = {-2, -2, -1, -1,  1,  1,  2,  2};
int dy[8] = {-1,  1, -2,  2, -2,  2, -1,  1};
int inside(int x, int y) {
    return (x >= 0 && x < 24 && y >= 0 && y < 24);
}
int segments_intersect(int x1,int y1,int x2,int y2,
                       int x3,int y3,int x4,int y4)
{
    double ax = x1, ay = y1;
    double bx = x2, by = y2;
    double cx = x3, cy = y3;
    double dx_ = x4, dy_ = y4;

    double rpx = bx - ax;
    double rpy = by - ay;
    double spx = dx_ - cx;
    double spy = dy_ - cy;

    double den = rpx * spy - rpy * spx;

    if (den == 0.0) {
        return 0;
    }

    double t = ((cx - ax) * spy - (cy - ay) * spx) / den;
    double u = ((cx - ax) * rpy - (cy - ay) * rpx) / den;

    if (t > 0.0 && t < 1.0 && u > 0.0 && u < 1.0) {
        return 1;
    }

    return 0;
}


int crosses_existing(int x1,int y1,int x2,int y2) {
    for(int i=0;i<linkRcount;i++) {
        if(segments_intersect(x1,y1,x2,y2,
                              linkR[i].x1,linkR[i].y1,
                              linkR[i].x2,linkR[i].y2))
            return 1;
    }
    for(int i=0;i<linkBcount;i++) {
        if(segments_intersect(x1,y1,x2,y2,
                              linkB[i].x1,linkB[i].y1,
                              linkB[i].x2,linkB[i].y2))
            return 1;
    }
    return 0;
}
int point_has_link(int x, int y, char color) {
    if (color == 'R') {
        for (int i = 0; i < linkRcount; i++) {
            if ((linkR[i].x1 == x && linkR[i].y1 == y) ||
                (linkR[i].x2 == x && linkR[i].y2 == y)) {
                return 1;
            }
        }
    } else if (color == 'B') {
        for (int i = 0; i < linkBcount; i++) {
            if ((linkB[i].x1 == x && linkB[i].y1 == y) ||
                (linkB[i].x2 == x && linkB[i].y2 == y)) {
                return 1;
            }
        }
    }
    return 0;
}

void add_links_for_new_pin(int x, int y, char turn, char board[24][24]) 
{
    linkage *arr;
    int *cnt;
    if (turn == 'R') {
        arr = linkR;
        cnt = &linkRcount;
    } else {
        arr = linkB;
        cnt = &linkBcount;
    }
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (!inside(nx, ny)) continue;
        if (board[nx][ny] == turn) {
            if (!crosses_existing(x, y, nx, ny)) {
                arr[*cnt].x1 = x;
                arr[*cnt].y1 = y;
                arr[*cnt].x2 = nx;
                arr[*cnt].y2 = ny;
                (*cnt)++;

        printf("For Player %c, (%d,%d) and (%d,%d) are linked\n",
                turn, x+1, y+1, nx+1, ny+1);
    } else {
        printf("Link between (%d,%d) and (%d,%d) blocked due to crossing\n",
                x+1, y+1, nx+1, ny+1);
    }
}
}}
