#ifndef JSON_CONVERTER
#define JSON_CONVERTER

#include "gr8_networking.h"
#include "configuration.h"

int convert_user_code(response *r, user_code *uc);
int convert_access_token(response *r, access_token *ac);

#endif
