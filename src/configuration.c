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


int read_configuration(char *file_name){
  configuration config;
  if(ini_parse(file_name, handler, &config) < 0){
    printf("Can't load %s\n",file_name);
    return 0;
  }
  printf("Config loaded from 'gr8.ini': version=%d, name=%s, email=%s\n", config.version, config.name, config.email);
  return 1; //return true
}
