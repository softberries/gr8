#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "json_converter.h"


int convert_user_code(response *r, user_code *uc){
  printf("RESPONSE: %s\n",r->ptr);
  //#define find_device_code "\"device_code\" : \"([\\s\\S]*?)\""
  #define find_device_code "device"
  int retval = 0;
  regex_t reg_dc;
  if(regcomp(&reg_dc, find_device_code, REG_EXTENDED) != 0){
    printf("cannot compile regex expression %s\n",find_device_code);
    return 1;//error
  }
  //device code buffer
  char device_code[256];
  if((retval = regexec(&reg_dc, r->ptr, 0, NULL, 0)) == 0) printf("found device code %s\n",device_code);

  return 0;//ok
}
int convert_access_token(response *r, access_token *ac){
  printf("RESPONSE: %s\n",r->ptr);
}
