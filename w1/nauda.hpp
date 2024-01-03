#ifndef __NAUDA_HPP_
#define __NAUDA_HPP_

#include <string>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "BMP24.h"


using namespace std;

// Tarpinė reikšmė  
double lerp(double a, double b, double t){
    return a * (1 - t) + b * t;
}
/////////////////////////////////////////////////////////////////////////////////////


// Spalvos klasė ir funkcijos
class Color{
   public:
     uint8_t r;
     uint8_t g;
     uint8_t b;
     Color():r(0),g(0),b(0){}
     Color(uint8_t r=0, uint8_t g=0, uint8_t b=0):r(r),g(g),b(b){}
};


Color lerpColor(Color a, Color b, double t){
    uint8_t r1 = (uint8_t) (a.r * (1 - t) + b.r * t);
    uint8_t g1 = (uint8_t) (a.g * (1 - t) + b.g * t);
    uint8_t b1 = (uint8_t) (a.b * (1 - t) + b.b * t);
    return Color(r1,g1,b1);
}

Color kombinacijaColor(Color a, Color b, Color c, double u, double v, double w){
    uint8_t r1 = (uint8_t) (a.r * u + b.r * v + c.r * w);
    uint8_t g1 = (uint8_t) (a.g * u + b.g * v + c.g * w);
    uint8_t b1 = (uint8_t) (a.b * u + b.b * v + c.b * w);
    return Color(r1,g1,b1);
}

/////////////////////////////////////////////////////////////////////////////////////

// Taško klasė ir funkcijos
class Taskas{
   public:
     double x;
     double y; 
     Taskas():x(0),y(0){}
     Taskas(double x=0, double y=0):x(x),y(y){}
};

double atstumas(Taskas a, Taskas b){
    Taskas d(b.x - a.x, b.y - a.y);
    return sqrt(d.x * d.x  + d.y * d.y);
}

// Vektorių AB ir AC sk. sandauga:
double skaliarineSandauga(Taskas A, Taskas B, Taskas C){
   Taskas AB(B.x-A.x, B.y-A.y);
   Taskas AC(C.x-A.x, C.y-A.y);
   return AB.x * AC.x  + AB.y * AC.y;
}

// Vektorių A ir B sk. sandauga:
double skaliarineSandauga(Taskas A, Taskas B){
   return A.x * B.x  + A.y * B.y;
}

// Vektoriaus AC projekcija į AB:
double projekcija(Taskas A, Taskas B, Taskas C){
   Taskas AB(B.x-A.x, B.y-A.y);
   Taskas AC(C.x-A.x, C.y-A.y);
   double csfi = skaliarineSandauga(A,B,C)/atstumas(A,B)/atstumas(A,C);
   
   return csfi*atstumas(A,C);
}

/////////////////////////////////////////////////////////////////////////////////////

// Spalvotas taškas - koordinatės + spalva
class SpalvotasTaskas{
   public:
     Taskas koordinates;
     Color spalva;
     SpalvotasTaskas():koordinates(Taskas(0,0)),spalva(Color(0,0,0)){}
     SpalvotasTaskas(Taskas k, Color sp):koordinates( k ),spalva(sp){}
     SpalvotasTaskas(double x, double y, uint8_t r, uint8_t g, uint8_t b)
             :koordinates(Taskas(x,y)), spalva(Color(r,g,b)){}

};

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Radialinio gradiento klasė
class RadialinisGradientas{
   public:
     SpalvotasTaskas centras;
     Color krastas;     
     double R;     
     RadialinisGradientas():centras(SpalvotasTaskas(0,0, 0,0,0)),krastas(255,255,255), R(10){}
     RadialinisGradientas(double x, double y, uint8_t rc, uint8_t gc, uint8_t bc, uint8_t rk, uint8_t gk, uint8_t bk, double R = 100 ):
          centras(SpalvotasTaskas(x,y,rc,gc,bc)), krastas(Color(rk,gk,bk)), R(R){}   
     Color skaiciuokSpalva(Taskas p){
        double ats = atstumas(p, this->centras.koordinates);
        double t = ats/R;
        if (t > 1.0)  
            return krastas;
        else 
            return lerpColor(this->centras.spalva, krastas, t);
     }     
};

/////////////////////////////////////////////////////////////////////////////////////

// Tiesinio gradiento klasė
class TiesinisGradientas{
   public:
     SpalvotasTaskas pirmas;
     SpalvotasTaskas antras;
     TiesinisGradientas():pirmas(SpalvotasTaskas(0,0, 0,0,0)),antras(SpalvotasTaskas(100,100, 255,255,255)){}
     TiesinisGradientas(double x1, double y1, uint8_t r1, uint8_t g1, uint8_t b1, 
                        double x2, double y2, uint8_t r2, uint8_t g2, uint8_t b2):
          pirmas(SpalvotasTaskas(x1,y1,r1,g1,b1)), antras(SpalvotasTaskas(x2,y2,r2,g2,b2)){}   
     Color skaiciuokSpalva(Taskas p){
        double ats = atstumas(this->pirmas.koordinates, this->antras.koordinates);
        double pr = projekcija(this->pirmas.koordinates, this->antras.koordinates, p);
        if (pr < 0.0)  
            return this->pirmas.spalva;
        else if (pr > ats)
            return this->antras.spalva;
            else{
                  double t =  pr / ats;
                  return lerpColor(this->pirmas.spalva, this->antras.spalva, t);
                } 
                
     }     
};

/////////////////////////////////////////////////////////////////////////////////////

// Transformacijos klasė
class Transformacija{
   public:
     double  a;
     double  b;
     double  c;
     double  d;
     double  e;
     double  f;
     Transformacija():a(1),b(0),c(0),d(0),e(1),f(0){}
     Transformacija(double a, double b, double c, double d, double e, double f):
         a(a),b(b),c(c),d(d),e(e),f(f){}
    
     void vienetine(){
       a = 1;  b = 0; c = 0; d = 0; e = 1; f = 0;
     }
     void pernesimas(double xc, double yc){
         c += xc;
         f += yc;
     }
     void mastelis(double xm, double ym){
         a *= xm;
         e *= ym;
     }
     void posukis(double laipsniu){
         double rad = laipsniu * M_PI/180;
         double cs = cos(rad);
         double sn = sin(rad);
         double a1 = cs * a - sn * d; 
         double b1 = cs * b - sn * e;  
         double d1 = sn * a + cs * d; 
         double e1 = sn * b + cs * e;  
         a = a1; b = b1; d = d1; e = e1;
     }
     void pritaikyk(Taskas& p){
        double x1 = p.x * a + p.y * b + c; 
        double y1 = p.x * d + p.y * e + f;
        p.x = x1;
        p.y = y1;
     } 


};

/////////////////////////////////////////////////////////////////////////////////////

//  Kavdrato piešimo funkcijos 
// ... pagal spalvą
void kvadratas(BMP24& pav, double did, Color c, Transformacija tr){
   double delta = 0.1;
   
   for(double x = 0; x < did; x+=delta)
     for(double y = 0; y < did; y+=delta){
          Taskas p(x,y);
          tr.pritaikyk(p);           
          pav.dekTaska((uint32_t) p.x, (uint32_t) p.y, c.r, c.g, c.b);  
     }     
}

// ... pagal tiesinį gradientą 
void kvadratas(BMP24& pav, double did, TiesinisGradientas gr, Transformacija tr){
   double delta = 0.1;
   
   for(double x = 0; x < did; x+=delta)
     for(double y = 0; y < did; y+=delta){
          Taskas p(x,y);
          tr.pritaikyk(p);           
          Color c = gr.skaiciuokSpalva(p);
          pav.dekTaska((uint32_t) p.x, (uint32_t) p.y, c.r, c.g, c.b);  
     }     
}


/////////////////////////////////////////////////////////////////////////////////////
// Elipsės piešimo funkcijos

void elipse(BMP24& pav, double a, double b, Color c, Transformacija tr){
   double delta = 0.1;
   
   for(double x = -a; x < a; x+=delta)
     for(double y = -b; y < b; y+=delta){
          if ((x*x/a/a + y*y/b/b)<=1.0){
             Taskas p(x,y);
             tr.pritaikyk(p);           
             pav.dekTaska((uint32_t) p.x, (uint32_t) p.y, c.r, c.g, c.b);  
          }   
     }     
}

/////////////////////////////////////////////////////////////////////////////////////
// Atkarpos piešimo funkcija

void atkarpa(BMP24& pav, Taskas a, Taskas b, Color c){
   double lx = fabs(a.x-b.x);
   double ly = fabs(a.y-b.y);
   double dt = 1.0/(1.0+2 * lx + 2 * ly);
   
   for(double t=0; t<=1.0;t+=dt){
      Taskas p(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
      pav.dekTaska((uint32_t) p.x, (uint32_t) p.y, c.r, c.g, c.b);  
   }
}


/////////////////////////////////////////////////////////////////////////////////////

// Trikampio piešimo funkcijos
// ... pagal spalvą ir viršūnes 
void trikampis(BMP24& pav, Taskas a, Taskas b, Taskas c, Color sp, Transformacija tr){
   double lx = fabs(a.x-b.x);
   double ly = fabs(a.y-b.y);
   double dt = 1.0/(1.0+2 * lx + 2 * ly);
   tr.pritaikyk(c);          
   for(double t=0; t<=1.0;t+=dt){
      Taskas p(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
      tr.pritaikyk(p);          
      atkarpa(pav, c, p, sp);  
   }
}

// ... pagal radialinį gradientą ir viršūnes 
void trikampis(BMP24& pav, Taskas a, Taskas b, Taskas c, RadialinisGradientas gr, Transformacija tr){
   double lx = fabs(a.x-b.x);
   double ly = fabs(a.y-b.y);
   double dt = 1.0/(1.0+2 * lx + 2 * ly);
   tr.pritaikyk(c);          
   for(double t=0; t<=1.0;t+=dt){
      Taskas p(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
      tr.pritaikyk(p);          
      Color sp = gr.skaiciuokSpalva(p);
      atkarpa(pav, c, p, sp);  
   }
}


void baricentrinesKoordinates(Taskas p, Taskas a, Taskas b, Taskas c, double &u, double &v, double &w)
{
    Taskas v0(b.x - a.x, b.y - a.y);
    Taskas v1(c.x - a.x, c.y - a.y);
    Taskas v2(p.x - a.x, p.y - a.y);

    double d00 = skaliarineSandauga(v0, v0);
    double d01 = skaliarineSandauga(v0, v1);
    double d11 = skaliarineSandauga(v1, v1);
    double d20 = skaliarineSandauga(v2, v0);
    double d21 = skaliarineSandauga(v2, v1);
    double denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0 - v - w;
    //cout << u << " " << v << " " << w << endl;
}

// ... pagal spalvotas viršūnes  (naudojamos baricentrinės koordinatės)
void trikampis(BMP24& pav, SpalvotasTaskas a, SpalvotasTaskas b, SpalvotasTaskas c, Transformacija tr){
   tr.pritaikyk(a.koordinates);
   tr.pritaikyk(b.koordinates);
   tr.pritaikyk(c.koordinates);          
   double xmin = min(a.koordinates.x,min(b.koordinates.x,c.koordinates.x));
   double ymin = min(a.koordinates.y,min(b.koordinates.y,c.koordinates.y));
   double xmax = max(a.koordinates.x,max(b.koordinates.x,c.koordinates.x));
   double ymax = max(a.koordinates.y,max(b.koordinates.y,c.koordinates.y));
   for (double x=xmin;x<=xmax;x+=0.1)
     for (double y=ymin;y<=ymax;y+=0.1){
        Taskas p(x,y);
        double u,v,w;
        baricentrinesKoordinates(p, a.koordinates,  b.koordinates, c.koordinates, u, v, w);
        if((u>=0)&&(v>=0)&&(w>=0)){ 
           Color sp = kombinacijaColor(a.spalva, b.spalva, c.spalva, u, v, w);
           pav.dekTaska((uint32_t) x,(uint32_t) y, sp.r, sp.g,sp.b);  
        }     
    }

}


/////////////////////////////////////////////////////////////////////////////////////
#endif
