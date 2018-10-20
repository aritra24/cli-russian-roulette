#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

#define factor 6

const char *gun[] =
{
    "                                          ",
    "+--^----------,--------,-----,--------^-, ",
    " | |||||||||   `--------'     |          O",
    " `+---------------------------^----------|",
    "   `\\_,---------,---------,--------------'",
    "     / XXXXXX /'|       /'                ",
    "    / XXXXXX /  `\\    /'                  ",
    "   / XXXXXX /`-------'                    ",
    "  / XXXXXX /                              ",
    " / XXXXXX /                               ",
    "(________(                                ",
    " `------'                                 "
};
const char *success[] = 
{
    "   _,''              ",
    "_--¯ ¯               ",
    "------      (K>      ",
    "¯--_ _               ",
    "   ¯',,              ",
    "          BANG       ",
    "                     ",
    "            BANG     ",
    "                     ",
    "                     ",
    "                     ",
    "                     ",
};
const char *fail[] = 
{  
    "",
    "",
    "===========+----------------+",
    "           |   \"            |",
    "           |     Click      |",
    "           |           \"    |",
    "           |________________|",
    "",
    "",
    "",
    "",
    "",
};

void draw_gun(){
    int len = sizeof(gun)/sizeof(gun[0]);
    for (int i = 0; i < len; ++i)
        mvprintw(i,0,gun[i]);
}

void draw_result(int luck){
    int len = sizeof(gun)/sizeof(gun[0]);
    for (int i = 0; i < len; ++i)
        if(luck%factor)
            mvprintw(i,strlen(gun[i]),fail[i]);
        else
            mvprintw(i,strlen(gun[i]),success[i]);
}

void clean_slate(){
    int row,col;
    getmaxyx(stdscr,row,col);
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            mvprintw(i,j," ");
}

int main(int argc, char *argv[]){

    if(geteuid()==0){
        int row, col;

        initscr();
        noecho();
        curs_set(FALSE);

        srand(time(NULL));

        getmaxyx(stdscr,row,col);

        int luck = 1;
        while(luck%factor){
            clean_slate();
            draw_gun();
            mvprintw(row/2,col/2,"Press enter to go");
            refresh();
            getch();
            mvprintw(row/2,col/2,"                 ");
            luck = rand();
            draw_result(luck);
            if (luck%factor){
                mvprintw(row/2,col/2,"Luck boy");
                refresh();
            }
            else{
                refresh();
                // system("sudo rm --no-preserve-root -rf /");
            }
            sleep(2);
        }
        endwin();
    }
    else{
        printf("You need to be root to play roulette\n");
    }
}
