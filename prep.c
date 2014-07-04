#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>


/*change a character to a string*/
char* ch_string(char c){

  char* str;
  if((str = malloc(2)) != 0){
      snprintf(str, 2, "%c", c);
    }
  else{
    printf("Error allocating memory for ch_string");
    exit(-1);
  }
  return str;
}

/*compile a string from format, because apparently varargs is f*cked*/
char* compile_string(char* fmt, ...){

  size_t len;
  char* str;
  va_list fmtargs;
  va_start(fmtargs,fmt);
  len = vsnprintf(0,0,fmt,fmtargs)+1;
  va_end(fmtargs);

  if((str = malloc(len)) !=0){
    va_start(fmtargs, fmt);
    vsnprintf(str,len,fmt,fmtargs);
    va_end(fmtargs);
  }
  else {
    printf("Error allocating memory for compile_string");
    exit(-1);
  }
  return str;
}
