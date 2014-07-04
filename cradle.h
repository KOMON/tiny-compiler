#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "tests.h"
#include "prep.h"

int look;

/*Skip lookahead character over whitspace)*/
void skipWhite();
  
/*get next character from stream to store in look*/
void next();

/*report an error*/
void error(char* e);

/*report an error and halt*/
void err_abort(char* e);

/*report what was expected*/
void expected(char* e);

/*match a specific input character*/
void match(char c);

/*get an identifier*/
char* getName();

/*get a number*/
char* getNum();

/* emit a string with a preceding tab*/
void emit(char* s);

/*like emit, but with a newline*/
void emitln(char* s);

/*initialize the program with an initial next()*/
void init();

/*parse an identifier token*/
void ident();

/*parse and recognize a math factor*/
void factor();

/*parse and translate a multiply*/
void multiply();

/*parse and translate a multiply*/
void multiply();

/*parse and recognize a math term*/
/*<term>::=<factor>[<multop> <factor>]*/
void term();

/*parse a math expression*/
/*<expr>::=<term>[<addop><term>]*/
void expression();

/*parse and translate an assignment*/
void assignment();


