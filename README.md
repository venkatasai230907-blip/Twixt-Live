Twixt – CLI Version

Name    : Chilamakuru Venkata Sai Jaswanth
Roll.No : 2025102022
Section : B


CLI Commands:

place r c     Place a peg at row r, column c (autolink enabled)
quit          Exit the game

Folder Structure:
|
|-- main.c        
|-- links.h   
|-- links.c   
|-- winning_check.h  
|-- winning_check.c  
|-- README.md      
|-- Makefile
|-- twixt.h  

Compilation Instructions:

If using Makefile:

make

Run the program:
./twixt

If compiling manually:

gcc main.c links.c winning_check.c -o twixt -std=c11 -Wall -Wextra

./twixt

Rules :
    For winning :
        - RED tries to connect **top row** to **bottom row**  
        - BLACK tries to connect **left column** to **right column**   
Features :  
-If a link exists between two points, the pins are displayed in color
(RED prints R in red color, BLACK prints B in blue color).  yes
-Blocking of crossing links 
-Validity rules (borders, occupied cells, corner restriction)


THANK YOU .....
