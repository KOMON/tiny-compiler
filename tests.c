#include <ctype.h>

/*constant declarations*/
#define TAB '\t'
#define NEWL '\n'
#define SPC ' '


/*Compare look to whitespace*/
int isWhite(char c){
  if(c == SPC || c == TAB){
    return 1;
  }
  return 0;
}

/*compare c to alphanumeric characters*/
int isAlNum(char c){

  if(isalpha(c) || isdigit(c)){
    return 1;
  }
  return 0;
}

/*compare c to list of addops*/
int isAddop(char c){

  if(c == '+' || c == '-'){
    return 1;
  }
  return 0;
}

/*compare c to list of multops*/
int isMultop(char c){

  if(c == '*' || c == '/'){
    return 1;
  }
  return 0;
}
