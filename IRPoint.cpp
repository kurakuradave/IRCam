#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "IRPoint.h"

IRPoint::IRPoint(){
    x=1023;
    y=1023;
}

void IRPoint::update( int rawx, int rawy ){
  x = rawx;
  y = rawy;
}


