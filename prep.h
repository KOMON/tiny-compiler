#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>


/*change a character to a string*/
char* ch_string(char c);

/*compile a string from format, because apparently varargs is f*cked*/
char* compile_string(char* fmt, ...);
