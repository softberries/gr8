#include <stdio.h>
#include <stdlib.h>
//#include <ncurses.h>
#include <string.h>
#include "googlereader.h"
#include "json_converter.h"

//void prts(char *pattern, char *text){
//  mvprintw(LINES - 2, 0, pattern ,text);
//}
int main(void){
  char mesg[]="Enter a command: ";/* message to be appeared on the screen */
  char str[80];
  int row,col;
//  initscr(); 
//  getmaxyx(stdscr,row,col);

  //converting json
  puts("============CONVERTING JSON=============");
  char *response_str = "{ \
     \"device_code\" : \"4/L9fTtLrhY96442SEuf1Rl3KLFg3y\",\
     \"user_code\" : \"a9xfwk9c\",\
     \"verification_url\" : \"http://www.google.com/device\",\
     \"expires_in\" : 1800,\
     \"interval\" : 5\
    }";
  response r = {response_str,0};
  user_code uc;
  convert_user_code(&r,&uc); 
//  mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
  
//  getstr(str);

//  mvprintw(LINES - 2, 0, "You Entered: %s", str);
//  getch();
//  endwin();

  return 0;
}
