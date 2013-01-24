/* file minunit_tests.c */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "gr8_networking.h"

 int tests_run = 0;
 
 int foo = 7;
 int bar = 5;

 char *str1 = "hello world!";
 char *str2 = "hello world!";
 
 request_param client_id = {"client_id","958593878201.apps.googleusercontent.com"};
 request_param client_secret = {"client_secret","5IqqAe-SHtAFJyY7ODx4uNSy"};

 int parse_response_get_user_info(response *r){
    printf("RESPONSE RECEIVED: %s\n",r->ptr);
 }
 static char * test_execute_request_get_user_info(){
  request_param access_token = {"access_token","ya29.AHES6ZTJtGJwaAgdsuj0SbNDLHew1ATOPyEW_HBs709cUUXdIAdMeA"};
  request_param *params[] = {&access_token};
  const char *url = "https://www.googleapis.com/oauth2/v1/userinfo";
  execute_request(0,url,1,params,parse_response_get_user_info);
 }
 int parse_response_get_access_code(response *r){
    printf("RESPONSE RECEIVED: %s\n",r->ptr);
    if(strstr(r->ptr,"access_token") == NULL) exit(EXIT_FAILURE);
    return 0;
 }
 static char * test_execute_request_get_access_code(){
  request_param code = {"code","4/1LQ5P6xd8kIeRknddiTfmq_Nlqxr"};
  request_param grant_type = {"grant_type","http://oauth.net/grant_type/device/1.0"};
  request_param *params[] = {&client_id,&client_secret,&code,&grant_type};
  const char *url = "https://accounts.google.com/o/oauth2/token";
  execute_request(1,url,4,params,parse_response_get_access_code);
  return 0;
 }


 int parse_response_get_user_code(response *r){
    printf("RESPONSE RECEIVED: %s\n",r->ptr);
    if(strstr(r->ptr,"user_code") == NULL) exit(EXIT_FAILURE);
    return 0;
 }
 static char * test_execute_request_get_user_code(){
   request_param scope = {"scope","https://www.googleapis.com/auth/userinfo.email https://www.googleapis.com/auth/userinfo.profile"};
   const char *url = "https://accounts.google.com/o/oauth2/device/code";
   request_param *params[] = {&client_id, &scope};
   execute_request(1,url,2,params,parse_response_get_user_code);
  return 0;
 }
 static char * test_build_query(){
    request_param p1 = {"name1","value1"};
    request_param p2 = {"name2","value2"};
    request_param *params[] = {&p1,&p2};
    char *result;
    build_query(&result,NULL,2,params);
    char *expected = "name1=value1&name2=value2";
    printf("result of build query is: %s\n",result);
    mu_assert("error, result should be equal to name1=value1&name2=value2",strncmp(result,expected,strlen(expected)) == 0);
    return 0;
 }
 static char * test_strs(){
    int length = strlen(str1) > strlen(str2) ? strlen(str1) : strlen(str2);
    printf("length: %d\n",length);
    mu_assert("error, strings are not equal", strncmp(str1,str2,length) == 0);
    return 0;
 }
 
 static char * test_bar() {
     mu_assert("error, bar != 5", bar == 5);
     return 0;
 }
 
 static char * all_tests() {
     mu_run_test(test_execute_request_get_user_info);
     //mu_run_test(test_execute_request_get_access_code);
     //mu_run_test(test_execute_request_get_user_code);
     mu_run_test(test_build_query);
     mu_run_test(test_strs);
     mu_run_test(test_bar);
     return 0;
 }
 
 int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }

