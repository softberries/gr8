#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"



static int handler(void* user, const char* section, const char* name, const char* value){
  configuration *pconfig = (configuration*)user;

  #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
  if(MATCH("protocol", "version")){
    pconfig->version = atoi(value);
  }else if(MATCH("user","name")){
    pconfig->name = strdup(value);
  }else if(MATCH("user", "email")){
    pconfig->email = strdup(value);
  }else{
    return 0;
  }
  return 1;
} 
int save_access_token(access_token *token){
  char *full_path;
  check_file(ACCESS_TOKEN_FILE,&full_path);
  //open the file and create if it doesn't exist
  FILE *fp = fopen(full_path,"wb+");
  if(fp){
    //access_token
    fputs("access_token=",fp);
    fputs(token->acc_token,fp);
    fputs("\n",fp);
    //token_type
    fputs("token_type=",fp);
    fputs(token->token_type,fp);
    fputs("\n",fp);
    //expires_in
    fputs("expires_in=",fp);
    fputs(token->expires_in,fp);
    fputs("\n",fp);
    //refresh_token
    fputs("refresh_token=",fp);
    fputs(token->refresh_token,fp);
    fputs("\n",fp);
    //close the file
    fclose(fp);
  }
  free(full_path);
  return 0;//ok
}

void init_empty_token(access_token *t){
  t->acc_token = malloc(1);
  t->token_type = malloc(1);
  t->expires_in = malloc(1);
  t->refresh_token = malloc(1);
  if(t->acc_token == NULL || t->token_type == NULL || t->expires_in == NULL || t->refresh_token == NULL){
    fprintf(stderr, "malloc() for init_empty_token failed\n");
    exit(EXIT_FAILURE);
  }
  t->acc_token[0] = '\0';
  t->token_type[0] = '\0';
  t->expires_in[0] = '\0';
  t->refresh_token[0] = '\0';
}

int read_access_token(access_token *ac){
 char *acc_tok,*tok_type,*exp_in,*ref_tok;
 FILE *fp;
 char *full_path;
 check_file(ACCESS_TOKEN_FILE,&full_path);
 char *line = NULL;
 size_t len = 0;
 ssize_t read;

 char *at = "access_token=";
 char *tt = "token_type=";
 char *ei = "expires_in=";
 char *rt = "refresh_token=";
 init_empty_token(ac);
 fp = fopen(full_path,"r");
 if(fp == NULL){
  //return 1 for retrieving new token from google api
  return 1;
 }else{
  while((read = getline(&line,&len,fp)) != -1){
    char *res = NULL;
    if(strstr(line,at)){
      res = strndup(line+strlen(at),strlen(line));
      ac->acc_token = realloc(ac->acc_token, strlen(res)+1);
      memcpy(ac->acc_token, res, strlen(res));
      ac->acc_token[strlen(res)] = '\0';
    }else if(strstr(line,tt)){
      res = strndup(line+strlen(tt),strlen(line));
      ac->token_type = realloc(ac->token_type,strlen(res)+1);
      memcpy(ac->token_type, res, strlen(res));
      ac->token_type[strlen(res)] = '\0';
    }else if(strstr(line,ei)){
      res = strndup(line+strlen(ei),strlen(line));
      ac->expires_in = realloc(ac->expires_in,strlen(res)+1);
      memcpy(ac->expires_in, res, strlen(res));
      ac->expires_in[strlen(res)] = '\0';
    }else if(strstr(line,rt)){
      res = strndup(line+strlen(rt),strlen(line));
      ac->refresh_token = realloc(ac->refresh_token,strlen(res)+1);
      memcpy(ac->refresh_token, res, strlen(res));
      ac->refresh_token[strlen(res)] = '\0';
    }
    free(res);
  }
  if(line) free(line);
  fclose(fp);
 }
 return 0;
}
int check_file(char *file_name, char **full_path){
  const char *homeDir = getenv("HOME");
  if(homeDir){
    printf("Home directory is: %s\n",homeDir);
    char *fp = malloc(strlen(file_name) + strlen(homeDir) + 2);//one for nt and one for '/' separator
    strcpy(fp,homeDir);
    strcat(fp,"/");
    strcat(fp,file_name);
    *full_path = fp;
  }else{
    return 1; 
  }
  return 0;
}
int read_default_configuration(){
  return read_configuration(".gr8/gr8.ini");
}
int read_configuration(char *file_name){
  configuration config;
  char *full_path;
  check_file(file_name,&full_path);
  if(ini_parse(full_path, handler, &config) < 0){
    printf("Can't load %s\n",full_path);
  }else{
    printf("Config loaded from 'gr8.ini': version=%d, name=%s, email=%s\n", config.version, config.name, config.email);
  }
  free(full_path);
  return 0; //return true
}
