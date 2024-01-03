#ifndef __DANGUS_H_
#define __DANGUS_H_

#include <string>
#include <stdio.h>
#include <cstdint>
#include "BMP24.h"
#define DELTA 0.1

using namespace std;

class Dangus{
   public:
     BMP24* paveikslas;
     int32_t nuoY; // nuo kurio Y
     int32_t ikiY; // iki kurio Y
     
     uint8_t nuoR; // viršutinė spalva
     uint8_t nuoG; // viršutinė spalva
     uint8_t nuoB; // viršutinė spalva

     uint8_t ikiR; // apatinė spalva
     uint8_t ikiG; // apatinė spalva
     uint8_t ikiB; // apatinė spalva

     
     Dangus(BMP24* pav, int32_t nuoY, int32_t ikiY, 
                       uint8_t nuoR, uint8_t nuoG, uint8_t nuoB, 
                       uint8_t ikiR, uint8_t ikiG, uint8_t ikiB):paveikslas(pav), 
                       nuoY(nuoY), ikiY(ikiY), 
                       nuoR(nuoR), nuoG(nuoG), nuoB(nuoB),
                       ikiR(ikiR), ikiG(ikiG), ikiB(ikiB) {}
     void vaizduok();                        

}; 


#endif


