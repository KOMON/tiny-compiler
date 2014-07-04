#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "tests.h"
#include "prep.h"

/*variable declarations*/
int look;


/*get next character from stream to store in look*/
void next(){

  look = getc(stdin);
}

/*Skip lookahead character over whitspace)*/
void skipWhite(){

  while(isWhite(look)){
    next();
  }
}

/*report an error*/
void error(char* e){

  printf("Error: %s\n", e);
  printf("Lookahead = %c\n",look);
}

/*report an error and halt*/
void err_abort(char* e){

  error(e);
  exit(1);
}

/*report what was expected*/
void expected(char* e){
 
  char* fmt = "Expected: %s";
  char* error = compile_string(fmt,e);
  err_abort(error);
  free(error);
}

/*match a specific input character*/
void match(char c){

  if(look == c){
    next();
    skipWhite();
  }
  else {
    char* e = ch_string(c);
    expected(e);  
    free(e);
  }
}

/*get an identifier*/
char* getName(){

  char* buf;
  int   i = 0;
  if(!isalpha(look)){
    expected("Name");
  }
  buf = calloc(9, sizeof(char));
  if(!buf){
      printf("Problem allocating memory for getName()");
      exit(-1);
    }
  while(isAlNum(look) && i<8){
    buf[i] = toupper(look);
    i++;
    next();
  }
  skipWhite();
  return buf;
}

/*get a number*/
char* getNum(){

  char* buf;
  int   i = 0;

  if(!isdigit(look)){
    expected("Integer");
  }

  buf = calloc(11, sizeof(char));
  
  if(!buf){
    printf("Problem allocating memory for getNum()");
    exit(-1);
  }
  while(isdigit(look) && i < 10){
    buf[i] = look;
    i++;
    next();
    }
  skipWhite();
  return buf;
}

/* emit a string with a preceding tab*/
void emit(char* s){

  printf("%c%s",TAB,s);
}

/*like emit, but with a newline*/
void emitln(char* s){
  emit(s);
  printf("\n");
}

/*initialize the program with an initial next()*/
void init(){

  next();
  skipWhite();
}


/*parse an identifier token*/
void ident(){

  char* name = getName();
  char* fmt;
  if(look == '('){

    match('(');
    match(')');
   
    fmt = "CALL %s";
  }
  else{
    fmt = "MOV EAX, %s";
  }
  char* str = compile_string(fmt,name);
  emitln(str);
  free(str);
  free(name);
}

/*a function prototype, since we need expression() now*/
void expression();

/*parse and recognize a math factor*/
void factor(){
  if(look == '('){

    match('(');
    expression();
    match(')');
  }
  else if(isalpha(look)){
    ident();
  }
  else{
    char*  fmt  = "MOV EAX,%s";
    char*  expr = getNum(); 
    char*  str  = compile_string(fmt,expr);

    emitln(str);

    free(expr);
    free(str);
  }
}
/*parse and translate a multiply*/
void multiply(){
  
  match('*');
  factor();
  emitln("POP EBX");
  emitln("IMUL EAX, EBX");
}

void divide(){

  match('/');
  factor();
  emitln("PUSH EAX");
  emitln("POP EBX");
  emitln("POP EAX");
  emitln("CDQ");
  emitln("IDIV EBX");
}
/*parse and recognize a math term*/
/*<term>::=<factor>[<multop> <factor>]*/
void term(){ 

  factor();
  while(look == '*' || look == '/'){
    emitln("PUSH EAX");
    switch(look){
    case '*':
      multiply();
      break;
    case '/':
      divide();
      break;
    default:
      expected("Multop");
    }
  }
}

void add(){

  match('+');
  term();
  emitln("POP EBX");
  emitln("ADD EAX,EBX");
}

void subtract(){

  match('-');
  term();
  emitln("POP EBX"); 
  emitln("SUB EAX,EBX");
  emitln("NEG EAX");
}

/*parse a math expression*/
/*<expr>::=<term>[<addop><term>]*/
void expression(){

  if(isAddop(look)){
    emitln("XOR EAX,EAX");
  }
  else{
    term();
  }
  while(look == '+' || look == '-'){
    emitln("PUSH EAX");
    switch(look){
    case '+':
      add();
      break;
    case '-':
      subtract();
      break;
    default:
      expected("Addop");
    }
  }
}
/*parse and translate an assignment*/
void assignment(){

  char* name = getName();
  match('=');
  expression();
  char* str = compile_string("MOV %s, EAX", name);
  emitln(str);

  free(str);
  free(name);
}
