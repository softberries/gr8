#ifndef NETWORKING_STRUCTS
#define NETWORKING_STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

typedef struct {
  int version;
  const char *name;
  const char *email;
} configuration;


int read_configuration(char *file_path);

#endif


