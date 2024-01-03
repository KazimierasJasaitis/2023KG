#include <string>
#include <stdio.h>
#include <cstdint>
#include <iostream>

#include "BMP24.h"
#include "dangus.h"

using namespace std;


void Dangus::vaizduok(){
   BMP24* pav = this->paveikslas;
   double H = pav->aukstis;
   double W = pav->plotis;   
   double aX = 0;
   double aY = this->nuoY;
   double bX = W-1;
   double bY = this->ikiY;
   // Ribojimai
   if(aY < 0) aY = 0;
   if(aY >= H) return;
   
   if(bY >= H) bY = H-1;
   if(bY < 0) return;

   //Piešimas 
   double dx = DELTA;
   double dy = DELTA;
   double dH = ikiY - nuoY + 1;
   //double R2 = this->R * this->R;
   // cout << aX << " " << aY << " " << bX << " " << bY << endl; 
   for(double x = aX; x < bX; x += dx)    
     for(double y = aY; y < bY; y += dy){
            double alphaA = (bY - y) / dH;         // krašto spalvos koeficientas
            double alphaB = 1.0 - alphaA;   // centro spalvos koeficientas
            //cout << alphaK << " " << alphaC << endl;
            uint8_t tr = (uint8_t) (alphaA * this->nuoR + alphaB * this->ikiR);  // einamojo taško spalva
            uint8_t tg = (uint8_t) (alphaA * this->nuoG + alphaB * this->ikiG);  // einamojo taško spalva
            uint8_t tb = (uint8_t) (alphaA * this->nuoB + alphaB * this->ikiB);  // einamojo taško spalva

            uint32_t ix = (int32_t) x;
            uint32_t iy = (int32_t) y;
            //cout << ix << " " << iy << endl; 
            if((ix<0) || (iy<0) || (ix>=W) || (iy>=H))
                continue; 
            pav->dekTaska((int32_t) x, (int32_t) y,  tr,  tg,  tb);
     
     }    
   
}


