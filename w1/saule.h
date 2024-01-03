#ifndef __SAULE_H_
#define __SAULE_H_

#include <string>
#include <stdio.h>
#include <cstdint>
#include "BMP24.h"

using namespace std;

class Saule{
   public:
     BMP24* paveikslas;
     int32_t cx; // centro x
     int32_t cy; // centro x

     uint8_t cr; // centro r
     uint8_t cg; // centro g
     uint8_t cb; // centro b

     int32_t R;  // spindulys

     uint8_t kr; // krašto r
     uint8_t kg; // krašto g
     uint8_t kb; // krašto b
     
     Saule(BMP24* pav, int32_t cx, int32_t cy, 
                       uint8_t cr, uint8_t cg, uint8_t cb, 
                       int32_t R, 
                       uint8_t kr, uint8_t kg, uint8_t kb):paveikslas(pav), 
                       cx(cx), cy(cy), 
                       cr(cr), cg(cg), cb(cb),
                       R(R),
                       kr(kr), kg(kg), kb(kb){}
     void vaizduok();                        


}; 


#endif


