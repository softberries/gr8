#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "json_converter.h"

#define DEVICE_CODE_REGEX "\"device_code\" : \"([0-9//a-zA-Z]+)\""
#define USER_CODE_REGEX "\"user_code\" : \"([0-9a-zA-Z]+)\""
#define VERIFICATION_URL_REGEX "\"verification_url\" : \"([0-9a-zA-Z//:/.]+)\""
#define EXPIRES_IN_REGEX "\"expires_in\" : ([0-9]+),"
#define INTERVAL_REGEX "\"interval\" : ([0-9]+)"

static void get_value(const char *full_str,const char *regex_str, char **result){
  regex_t r;
  regmatch_t matches[3];
  regcomp(&r, regex_str, REG_EXTENDED);
  regexec(&r, full_str, 3, matches, 0);
  int start = matches[1].rm_so;
  int end = matches[1].rm_eo;
  char *res = strndup((full_str)+start,(end-start));
  *result = res;
  regfree(&r);
}
int convert_user_code(response *resp, user_code *uc){
  printf("RESPONSE: %s\n",resp->ptr);
  char *dc_str;//device code
  get_value(resp->ptr,DEVICE_CODE_REGEX,&dc_str);
  char *uc_str;//user code
  get_value(resp->ptr,USER_CODE_REGEX,&uc_str);
  char *vu_str;//verification url
  get_value(resp->ptr,VERIFICATION_URL_REGEX,&vu_str);
  char *ei_str;//expires in
  get_value(resp->ptr,EXPIRES_IN_REGEX,&ei_str);
  char *i_str;//interval
  get_value(resp->ptr,INTERVAL_REGEX,&i_str);
  printf("got from get_value: %s %s %s %s %s\n",dc_str,uc_str,vu_str,ei_str,i_str);

  free(dc_str);
  free(uc_str);
  free(vu_str);
  free(ei_str);
  free(i_str);

  return 0;//ok
}
int convert_access_token(response *r, access_token *ac){
  printf("RESPONSE: %s\n",r->ptr);
}
