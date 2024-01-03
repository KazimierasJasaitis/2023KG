#include <math.h>
#include "BMP24.h"
#include "saule.h"
#include "dangus.h"
#include <random>
#include <cstdlib>
#include <ctime>


using namespace std;

void taskavimas(BMP24* pav, int kiek, uint8_t r, uint8_t g, uint8_t b, 
                            uint32_t aX, uint32_t aY,
                            uint32_t bX, uint32_t bY){

   default_random_engine generatorius;
   generatorius.seed(12345);

   uniform_int_distribution<uint32_t> distributionX(aX+1,bX-1);      
   uniform_int_distribution<uint32_t> distributionY(aY+1,bY-1);      
   for(int i=0; i<kiek; i++){
   
      uint32_t x = distributionX(generatorius);
      uint32_t y = distributionY(generatorius);
      pav->dekTaska(x,y,r,g,b);
      pav->dekTaska(x-1,y,r,g,b);
      pav->dekTaska(x,y-1,r,g,b);
      pav->dekTaska(x,y+1,r,g,b);

   }


}

void linijavimas(BMP24* pav, uint8_t r, uint8_t g, uint8_t b, 
                             uint32_t aX, uint32_t aY,
                             uint32_t bX, uint32_t bY){

   default_random_engine generatorius;
   generatorius.seed(1234);
   uniform_int_distribution<uint32_t> distributionY(aY,bY-1);      
   for(uint32_t ix=aX; ix<bX; ix++){
   
      uint32_t x = ix;
      uint32_t ikiY = distributionY(generatorius);
      for(uint32_t y = aY; y < ikiY; y++)
        pav->dekTaska(x,y,r,g,b);
  
   }


}



int main(){
   BMP24 pav(800, 600);
   pav.valyk(0,128,0);

   Dangus dangus(&pav, 300, 799, 255, 255,255,  0, 0, 255);
   dangus.vaizduok(); 

   Saule saule(&pav, 200, 500, 255, 255,255, 50, 255, 255, 0);
   saule.vaizduok(); 

   Dangus dangus2(&pav, 0, 300, 0, 128, 0,  0, 255, 0); // Žemė
   dangus2.vaizduok(); 

   

   taskavimas(&pav,500, 255,255,0, 0,0, 799, 299); 

   linijavimas(&pav, 0,64,0,  0,300, 400,330);
   linijavimas(&pav, 0,164,0,  0,300, 400,320);

   pav.rasykIByla("a.bmp");
   return 0;  
}

