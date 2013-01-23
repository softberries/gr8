/* file minunit_tests.c */
 
#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "googlereader.h"

 int tests_run = 0;
 
 int foo = 7;
 int bar = 5;

 char *str1 = "hello world!";
 char *str2 = "hello world!";

 static char * test_strs(){
    int length = strlen(str1) > strlen(str2) ? strlen(str1) : strlen(str2);
    printf("length: %d\n",length);
    mu_assert("error, strings are not equal", strncmp(str1,str2,length) == 0);
    return 0;
 }
 
 static char * test_foo() {
     int result = add(2,2);
     mu_assert("error, foo != 4", result == 4);
     return 0;
 }
 
 static char * test_bar() {
     mu_assert("error, bar != 5", bar == 5);
     return 0;
 }
 
 static char * all_tests() {
     mu_run_test(test_strs);
     mu_run_test(test_foo);
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

