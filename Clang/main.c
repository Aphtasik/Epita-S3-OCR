#include <stdio.h>
//#include "base.h"
//#include <SDL.h>

#define IMG_HEIGHT 192
#define IMG_WIDTH 100

int CoordCalc(int x,int y){
   return (x * IMG_HEIGHT + (y % IMG_WIDTH));
}

int main(){
    
    int tableau[19200] = {0};
    tableau[102] = 12;
    printf("coordcalc(2,2)= %n \n coordcalc(3,2)= %n",CoordCalc(2,2), CoordCalc(3,2));
   // print_world();
   // print_goodbye();
}
