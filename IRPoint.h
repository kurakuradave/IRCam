#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #endif
 
#ifndef IRPoint_h
#define IRPoint_h

class IRPoint
{
  public:
    IRPoint();
    void update( int rawx, int rawy );
    int x;
    int y;
  private:
  
};

#endif
