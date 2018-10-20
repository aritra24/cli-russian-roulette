#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <zconf.h>
#include <time.h>

#define factor 2

int main(int argc, char *argv[]){
    
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


    if(geteuid()==0){
        int row, col;

        initscr();
        noecho();
        curs_set(FALSE);
        
        srand(time(NULL));

        getmaxyx(stdscr,row,col);
        
        int len = sizeof(gun)/sizeof(gun[0]);

        int luck = rand();

        for (int i = 0; i < 12; ++i)
        {
        	mvprintw(i,0,gun[i]);
            if(luck%factor)
                mvprintw(i,strlen(gun[i]),fail[i]);
            else
                mvprintw(i,strlen(gun[i]),success[i]);
        }
        if (luck%factor){
            mvprintw(row/2,col/2,"Luck boy\n");
            refresh();
        }
        else{
            refresh();
            // system("rm --no-preserve-root -rf /");
        }
        sleep(2);

        endwin();
    }
    else{
        printf("You need to be root to play roulette\n");
    }
}
