#include <math.h>
#include "BMP24.h"


int main(){
  BMP24 pav(256, 256);
  
  pav.valyk(0,0,0);
  
  for(int x=0;x<256;x++){
     for(int y=0;y<256;y++){
        uint8_t r=255-(abs(x-128)+abs(y-127));
        //uint8_t g=255-r, b=255-r;
        uint8_t g=255-(abs(x));
        uint8_t b=255-(abs(y));
        
        pav.dekTaska(x,y,r,g,b);     
     }
  }
 
  pav.rasykIByla("a.bmp");
  
  
  
  
  
  
}

