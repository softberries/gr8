#ifndef CONFIGURATION_STRUCTS
#define CONFIGURATION_STRUCTS

#define ACCESS_TOKEN_FILE ".gr8/.act"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

typedef struct {
  int version;
  const char *name;
  const char *email;
} configuration;

typedef struct {
  char *device_code;
  char *user_code;
  char *verification_url;
  int expires_in;
  int interval;
} user_code;

typedef struct {
  char *acc_token;
  char *token_type;
  char *expires_in;
  char *refresh_token;
} access_token;

int save_access_token(access_token *token);
int read_access_token(access_token *token);
int read_configuration(char *file_path);
int read_default_configuration();

#endif


