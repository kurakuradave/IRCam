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

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "IRCam.h"
#include "IRPoint.h"

IRCam::IRCam(){
}

void IRCam::begin(){
    Wire.begin();
    // initialize IR camera
    delay( 100 );
    write2(0x30,0x01); delay(10);
    write2(0x30,0x08); delay(10);
    write2(0x06,0x90); delay(10);
    write2(0x08,0xC0); delay(10);
    write2(0x1A,0x40); delay(10);
    write2(0x33,0x33); delay(10);
    delay(100);
}

void IRCam::update(){ 
// update() must be called from within loop() to get updated coordinate values.
// After calling update(), simply access the updated values like so, sensor.p1.x, sensor.p3.y, etc.
// And that's it! :)
// If both x and y values of a point are 1023, it means that point is out of the scope of the camera.

    //read IR sensor 
    Wire.beginTransmission(IRCAM_ADDRESS);
    Wire.write(IRCAM_READ_REGISTER);
    Wire.endTransmission();
 
    Wire.requestFrom(IRCAM_ADDRESS, 16);        // Request the 2 byte heading (MSB comes first)
    for (_i=0; _i<16; _i++) { _dataBuf[_i]=0; }
    _i=0;
    while(Wire.available() && _i < 16) {
        _dataBuf[_i] = Wire.read();
        _i++;
    }
 
    _rawx[0] = _dataBuf[1];
    _rawy[0] = _dataBuf[2];
    _s   = _dataBuf[3];
    _rawx[0] += (_s & 0x30) <<4;
    _rawy[0] += (_s & 0xC0) <<2;
 
    _rawx[1] = _dataBuf[4];
    _rawy[1] = _dataBuf[5];
    _s   = _dataBuf[6];
    _rawx[1] += (_s & 0x30) <<4;
    _rawy[1] += (_s & 0xC0) <<2;
 
    _rawx[2] = _dataBuf[7];
    _rawy[2] = _dataBuf[8];
    _s   = _dataBuf[9];
    _rawx[2] += (_s & 0x30) <<4;
    _rawy[2] += (_s & 0xC0) <<2;
 
    _rawx[3] = _dataBuf[10];
    _rawy[3] = _dataBuf[11];
    _s   = _dataBuf[12];
    _rawx[3] += (_s & 0x30) <<4;
    _rawy[3] += (_s & 0xC0) <<2;
    
    p1.update( _rawx[0], _rawy[0] );
    p2.update( _rawx[1], _rawy[1] );
    p3.update( _rawx[2], _rawy[2] );
    p4.update( _rawx[3], _rawy[3] );
}

void IRCam::write2( byte addr1, byte addr2 ){
    Wire.beginTransmission(IRCAM_ADDRESS);
    Wire.write(addr1); Wire.write(addr2);
    Wire.endTransmission();
}
