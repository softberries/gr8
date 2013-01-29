#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "json_converter.h"

#define DEVICE_CODE_REGEX "\"device_code\" : \"([0-9\/a-zA-Z]+)\""

void get_value(const char *full_str,const char *regex_str, char **result){
  regex_t r;
  regmatch_t matches[3];
  regcomp(&r, regex_str, REG_EXTENDED);
  regexec(&r, full_str, 3, matches, 0);
  char *res = strndup((full_str)+matches[1].rm_so,matches[1].rm_eo-matches[1].rm_so);
  *result = res;
  regfree(&r);
}
int convert_user_code(response *resp, user_code *uc){
  printf("RESPONSE: %s\n",resp->ptr);
  char *dc;
  get_value(resp->ptr,DEVICE_CODE_REGEX,&dc);
  
  printf("got from get_value: %s\n",dc);
  return 0;//ok
}
int convert_access_token(response *r, access_token *ac){
  printf("RESPONSE: %s\n",r->ptr);
}
