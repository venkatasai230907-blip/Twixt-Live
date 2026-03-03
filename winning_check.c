#include <string.h>
#include "links.h"
#include "winning_check.h"
extern char board[24][24];
int visitedR[24][24];
int win_red(int x, int y) {
    if (x == 23) {
        return 1;
    }
    visitedR[x][y] = 1;
    for (int i = 0; i < linkRcount; i++) {
        int nx, ny;

        if (linkR[i].x1 == x && linkR[i].y1 == y) {
            nx = linkR[i].x2;
            ny = linkR[i].y2;
        } else if (linkR[i].x2 == x && linkR[i].y2 == y) {
            nx = linkR[i].x1;
            ny = linkR[i].y1;
        } else {
            continue;
        }

        if (!visitedR[nx][ny]) {
            if (win_red(nx, ny)) {
                return 1;
            }
        }
    }

    return 0;
}
int check_red_win(void) {
    for(int i = 0;i<24;i++)
    {
        for(int j = 0 ;j<24;j++)
            visitedR[i][j] = 0;
    }
    for (int c = 0; c < 24; c++) {
        if (board[0][c] == 'R') {
            if (!visitedR[0][c]) {
                if (win_red(0, c)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
int visitedB[24][24];

int win_black(int x, int y) {
    if (y == 23) {
        return 1;
    }
    visitedB[x][y] = 1;

    for (int i = 0; i < linkBcount; i++) {
        int nx, ny;

        if (linkB[i].x1 == x && linkB[i].y1 == y) {
            nx = linkB[i].x2;
            ny = linkB[i].y2;
        } else if (linkB[i].x2 == x && linkB[i].y2 == y) {
            nx = linkB[i].x1;
            ny = linkB[i].y1;
        } else {
            continue;
        }

        if (!visitedB[nx][ny]) {
            if (win_black(nx, ny)) {
                return 1;
            }
        }
    }
    return 0;
}
int check_black_win(void) {
    for(int i = 0;i<24;i++)
    {
        for(int j = 0 ;j<24;j++)
            visitedB[i][j] = 0;
    }
    for (int r = 0; r < 24; r++) {
        if (board[r][0] == 'B') {
            if (!visitedB[r][0]) {
                if (win_black(r, 0)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
