#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "links.h"
#include "winning_check.h"
#define RESET "\033[0m"
#define BRED  "\033[1;31m"
#define BBLUE "\033[1;34m"
char board[24][24];
void display() {
    printf("   ");
    for (int c = 1; c <= 24; c++) 
    {
        if(c == 2 || c == 24)  printf(" | ");
        printf("%2d ", c);
    }
    printf("\n");
    for (int i = 0; i < 24; i++)
    {
        if(i == 1 || i==23) printf("%s---------------------------------------------------------------------------------%s\n",BRED,RESET);
        printf("%2d ", i+1);
        for (int j = 0; j < 24; j++) 
        {
            if(j == 1 || j == 23)  printf("%s | %s",BBLUE,RESET);
                char ch = board[i][j];
                if (ch == 'R') {
                    if (point_has_link(i, j, 'R')) {
                        printf(" %sR%s ", BRED, RESET);
                    } else {
                        printf(" R ");
                    }
                } else if (ch == 'B') {
                    if (point_has_link(i, j, 'B')) {
                        printf(" %sB%s ", BBLUE, RESET);
                    } else {
                        printf(" B ");
                    }
                } else {
                    printf("%2c ", ch);
                    }
        }
        printf("\n");
    }
}
int main()
{
    printf("Twixt Game\n\n");
    printf("Usage: place <row> <col>\nTo exit game type quit\n\n");
    char *player = "RED";
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 24; j++) {
            if((i==0 && j==0)||(i == 23 && j == 0) || (i==0 && j==23)|| (i==23 && j==23))   board[i][j] = ' ';
            else
                board[i][j] = '.';
        }
    }
    display();
    while (1) {
        char cmd[25];
        printf("%s> ", (strcmp(player , "RED")==0) ? "RED" : "BLACK");
        scanf("%15s", cmd);
        if (strcmp(cmd, "place") == 0) {
            int r, c;
            if (scanf("%d %d", &r, &c) != 2) {
                printf("Usage: place <row> <col>\n");
                int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
                continue;
            }
            if (r <= 0 || r > 24 || c <= 0 || c > 24) {
                printf("Out of bounds. Valid rows 1..24, cols 1..24\n");
                continue;
            }
            if (board[r-1][c-1] != '.') {
                if((r==1 && c==1)||(r == 24 && c == 1) || (r==1 && c==24)|| (r==24 && c==24))   printf("Cell (%d,%d) Invalid Posistion\n",r,c);
                else printf("Cell (%d,%d) is already occupied.\n", r, c);
                continue;
            }
            if((strcmp(player , "RED")==0 && (c == 1 || c == 24)) ||(strcmp(player , "BLACK")==0 && ( r == 1 || r == 24)))
            {
                printf("Cell (%d,%d) Invalid Posistion for %s\n",r,c,player);
                continue;
            }
            char color = (strcmp(player,"RED")==0 )? 'R' : 'B';
            board[r-1][c-1] = color;
            add_links_for_new_pin(r-1, c-1, color, board);
            display();
            if (color == 'R') 
            {
                if (check_red_win()) {
                    printf("RED wins!\n");
                    break;
                }
            }
            else
            {
                if (check_black_win()) {
                    printf("BLACK wins!\n");
                    break;
                }
            }
        player = (strcmp(player , "RED")==0) ? "BLACK" : "RED";
        }
        else if (strcmp(cmd, "quit") == 0) {
            printf("Thankyou\n");
            break;
        }
        else {
            printf("Unknown command. Use: place <r> <c>  or quit\n");
            int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}
        }
    }
    return 0;
}
