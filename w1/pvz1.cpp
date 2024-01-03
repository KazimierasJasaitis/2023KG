#include <math.h>
#include "BMP24.h"


int main(){
   BMP24 pav(640, 480);
   //pav.valyk(128,128,128);
   pav.dekTaska(320,240, 255,0,0);
   pav.rasykIByla("a.bmp");
   return 0;  
}

