#ifndef NETWORKING_STRUCTS
#define NETWORKING_STRUCTS

#include <curl/curl.h>

typedef struct request_param {
  char *name;
  char *value;
} request_param;

typedef struct response {
  char *ptr;
  size_t len;
} response;

/**
 * Builds query from a number of request_param objects
 * 
 * @param result - final url with all query parameters will be stored at this address
 * @param curl - CURL object necessary for escaping parameter values
 * @param param_count - number of request_param strcuts passed to function
 * @param params - array of request_param pointers 
 **/
int build_query(char **result, CURL *curl, int param_count, request_param *params[]);

/** 
 * Allocates memory for incoming response. Used by the CURL library to store 
 * the received response from the server while executing requests 
 **/
void init_empty_response(response *r);

/**
 * Fills the response object with the content received from the server
 * Used as a callback function by CURL operations
 * @param ptr
 * @param size
 * @param count
 * @param resonse
 **/
size_t read_response(void *ptr, size_t size, size_t count, response *r);

/**
 * Actuall server call (POST/GET), this method initialize CURL object
 * and executes prepared queries against the network
 **/
int execute_request(int use_post,const char *base_url, const int param_count, request_param *params[], int(*process_received_response)(response*) );

#endif

