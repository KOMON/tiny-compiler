#include "cradle.h"

int main(int argc, char** argv){

 init();
 assignment();
 if(look != NEWL){
   expected("Newline");
 }
 printf("Lookahead = %c\n",look);
 return 0;
}
