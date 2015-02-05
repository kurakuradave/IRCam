/*
    This is an Arduino Library for DFRobot Positioning Infrared Camera ( SKU: SEN0158 ).
    Basically, it's a camera that can "see" infrared lights and ascertain the coordinates of those lights, just like what's inside a Wiimote.
    It can track up to four infrared lights at a time.
    You can find more info on this sensor at https://www.dfrobot.com/index.php?route=product/product&product_id=1088
    
    HOOKUP:   
            Arduino     Positioning IR Camera
    ===============     =====================
                 5V --> Red wire
                GND --> Black wire
    SDA (A4 on UNO) --> Yellow wire
    SCL (A5 on UNO) --> Green wire

    USAGE:
    See the example code in the examples/ folder.
    
    MODIFICATION HISTORY:
    // modified for http://DFRobot.com by kurakura, Jan 2015.
    // modified for http://DFRobot.com by Lumi, Jan. 2014
    // modified output for Wii-BlobTrack program by RobotFreak http://www.letsmakerobots.com/user/1433
    // Wii Remote IR sensor  test sample code  by kako http://www.kako.com
*/

#ifndef IRCam_h
#define IRCam_h

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"
#include "IRPoint.h"

#define IRCAM_ADDRESS 0x58
#define IRCAM_READ_REGISTER 0x36

class IRCam
{
  public:
    IRCam();
    IRPoint p1;
    IRPoint p2; 
    IRPoint p3; 
    IRPoint p4;
    void begin();
    void update();
  private:
    void write2( byte addr1, byte addr2 );
    byte _dataBuf[ 16 ];
    byte _i;
    int _rawx[4]; 
    int _rawy[4];
    int _s;    
};

#endif








