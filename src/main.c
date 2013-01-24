#include <stdio.h>
#include <stdlib.h>
#include "googlereader.h"
#include "configuration.h"


int main(void){
  puts("Google reader program starting...");
  printf("RES: %d\n",add(2,2));
  read_configuration("/Users/kris/.gr8/gr8.ini");
  return 0;
}
