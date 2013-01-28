#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "googlereader.h"
#include "json_converter.h"

void prts(char *pattern, char *text){
  mvprintw(LINES - 2, 0, pattern ,text);
}
int main(void){
  char mesg[]="Enter a string: ";/* message to be appeared on the screen */
  char str[80];
  int row,col;/* to store the number of rows and *
               * the number of colums of the screen */
  initscr();  /* start the curses mode */
  getmaxyx(stdscr,row,col);/* get the number of rows and columns */
  /* print the message at the center of the screen */

  puts("Google reader program starting...");
  prts("RES: %d\n",add(2,2));
  access_token token = {"access-token","token-type","expires-in","refresh-token"};
  save_access_token(&token);
  access_token token_res;
  read_access_token(&token_res);
  prts("received: %s",token_res.acc_token);
  prts("received: %s",token_res.token_type);
  prts("received: %s",token_res.expires_in);
  prts("received: %s",token_res.refresh_token);

  //user_Code
  user_code code = {"device--code","user--code","ver--url",400,1200};
  save_user_code(&code);
  user_code code_res;
  read_user_code(&code_res);
  prts("received: %s",code_res.device_code);
  prts("received: %s",code_res.usr_code);
  prts("received: %s",code_res.verification_url);
  prts("received: %d\n",code_res.expires_in);
  prts("received: %d\n",code_res.interval);

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

  mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
  
  getstr(str);

  mvprintw(LINES - 2, 0, "You Entered: %s", str);
  getch();
  endwin();

  return 0;
}
