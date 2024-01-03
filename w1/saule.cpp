#include <string>
#include <stdio.h>
#include <cstdint>
#include "BMP24.h"
#include "saule.h"
#include <cmath>
#include <iostream>
using namespace std;

#define DELTA 0.1

void Saule::vaizduok(){
   BMP24* pav = this->paveikslas;
   double H = pav->aukstis;
   double W = pav->plotis;   
   double nuoX = this->cx - this->R;
   double nuoY = this->cy - this->R;
   double ikiX = this->cx + this->R;
   double ikiY = this->cy + this->R;
   // Ribojimai
   if(nuoX<0) nuoX = 0;
   if(nuoY<0) nuoY = 0;
   if(nuoX>W) return;
   if(nuoY>H) return;
   
   if(ikiX>=W) ikiX = W-1;
   if(ikiY>=H) ikiY = H-1;
   if(ikiX<0) return;
   if(ikiY<0) return;

   //Piešimas 
   double dx = DELTA;
   double dy = DELTA;
   //double R2 = this->R * this->R;
   for(double x = nuoX; x<ikiX; x+=dx)    
     for(double y = nuoY; y<ikiY; y+=dy){
         double atstumasIkiCentro = sqrt((x-this->cx)*(x-this->cx) + (y-this->cy)*(y-this->cy));
         if (atstumasIkiCentro <= R) {
            double alphaK = atstumasIkiCentro / R;         // krašto spalvos koeficientas
            double alphaC = 1.0 - alphaK;   // centro spalvos koeficientas
            //cout << alphaK << " " << alphaC << endl;
            uint8_t tr = (uint8_t) (alphaK * this->kr + alphaC * this->cr);  // einamojo taško spalva
            uint8_t tg = (uint8_t) (alphaK * this->kg + alphaC * this->cg);  // ...
            uint8_t tb = (uint8_t) (alphaK * this->kb + alphaC * this->cb);  // ...
            //cout << (int) tr << " " << (int) tg << " " << (int) tb << endl;
            uint32_t ix = (int32_t) x;
            uint32_t iy = (int32_t) y;
            if((ix<0) || (iy<0) || (ix>=W) || (iy>=H))
                continue; 
            pav->dekTaska((int32_t) x, (int32_t) y,  tr,  tg,  tb);
            //pav->dekTaska((int32_t) x, (int32_t) y, this->kr, this->kg, this->kb);
            
         }         
     
     }    
   

}; 


