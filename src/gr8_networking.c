#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "gr8_networking.h"

void init_empty_response(response *r){
  r->len = 0;
  r->ptr = malloc(r->len+1);
  if(r->ptr == NULL){
    fprintf(stderr, "malloc() for init_empty_response failed\n");
    exit(EXIT_FAILURE);
  }
  r->ptr[0] = '\0';
}
size_t read_response(void *ptr, size_t size, size_t count, response *r){
  size_t new_len = r->len + size*count;
  r->ptr = realloc(r->ptr, new_len+1);
  if(r->ptr == NULL){
    fprintf(stderr,"realloc() while reading response failed!\n");
    exit(EXIT_FAILURE);
  }
  memcpy(r->ptr+r->len, ptr, size*count);
  r->ptr[new_len] = '\0';
  r->len = new_len;
  return size*count;
}

int execute_request(int use_post,const char *base_url, const int param_count, request_param *params[],  int(*process_received_response)(response*) ){
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  char *request_string;
  build_query(&request_string,curl,param_count,params);
  if(curl){
    response r;
    init_empty_response(&r);
    if(use_post){
      curl_easy_setopt(curl,CURLOPT_URL,base_url);
      curl_easy_setopt(curl,CURLOPT_POSTFIELDS,request_string);
      curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, read_response);
      curl_easy_setopt(curl,CURLOPT_WRITEDATA, &r);
    }else{
      char *full_url = malloc(sizeof(base_url) + sizeof(request_string) + 2);//one for null terminator and one for '?'
      strcpy(full_url,base_url);
      strcat(full_url,"?");
      strcat(full_url,request_string);
      curl_easy_setopt(curl,CURLOPT_URL,full_url);
      curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, read_response);
      curl_easy_setopt(curl,CURLOPT_WRITEDATA, &r);
      free(full_url);
    }
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      fprintf(stderr,"curl failed: %s\n",curl_easy_strerror(res));
    }else{
      process_received_response(&r);
    }
    free(r.ptr);
    free(request_string);
    curl_easy_cleanup(curl);
  }
  return 0;
}


int build_query(char **result, CURL *curl, int param_count, request_param *params[]){
  request_param *p;
  int i;
  char *res = malloc(1000); //TODO calculate proper size
  if(res == NULL){
    fprintf(stderr,"malloc() for build_query result failed!\n");
    exit(EXIT_FAILURE);
  }
  strcpy(res,"");
  for(i=0;i<param_count;i++){
    p = params[i];
    printf("REQUEST PARAM: %s = %s\n",p->name,p->value);
    strcat(res,p->name);
    strcat(res,"=");
    if(curl != NULL) strcat(res,curl_easy_escape(curl,p->value,0));
    else strcat(res,p->value);
    if(i < (param_count-1)) strcat(res,"&");
  }
  *result = res;
  return 0;
}

