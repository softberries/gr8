#include <stdio.h>
#include <stdlib.h>
#include "googlereader.h"
#include "configuration.h"


int main(void){
  puts("Google reader program starting...");
  printf("RES: %d\n",add(2,2));
  access_token token = {"access-token","token-type","expires-in","refresh-token"};
  save_access_token(&token);
  access_token token_res;
  read_access_token(&token_res);
  printf("received: %s",token_res.acc_token);
  printf("received: %s",token_res.token_type);
  printf("received: %s",token_res.expires_in);
  printf("received: %s",token_res.refresh_token);
  return 0;
}
