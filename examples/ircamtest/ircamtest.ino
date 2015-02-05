/*
    This is an example Arduino code for DFRobot Positioning Infrared Camera ( SKU: SEN0158 ).
    Basically, it's a camera that can "see" infrared lights and ascertain the coordinates of those lights, just like what's inside a Wiimote.
    It can track up to four infrared lights at a time.
    You can find more info on this sensor at https://www.dfrobot.com/index.php?route=product/product&product_id=1088
    
    WHAT THIS SKETCH DOES:
    Outputs x and y coordinate values for four points to Serial out.
    When a point is not detected ( blocked, out of range, etc ), the sensor outputs 1023 for both x and y values.
    
    HOOKUP:   
            Arduino     Positioning IR Camera
    ===============     =====================
                 5V --> Red wire
                GND --> Black wire
    SDA (A4 on UNO) --> Yellow wire
    SCL (A5 on UNO) --> Green wire
    
    MODIFICATION HISTORY:
    // modified for http://DFRobot.com by kurakura, Jan 2015.
    // modified for http://DFRobot.com by Lumi, Jan. 2014
    // modified output for Wii-BlobTrack program by RobotFreak http://www.letsmakerobots.com/user/1433
    // Wii Remote IR sensor  test sample code  by kako http://www.kako.com
*/

#include <Wire.h>       // include the Wire library
#include <IRCam.h>      // include the IRCam library   

IRCam myCam;            // declare a IRCam object

void setup() {
    myCam.begin();      // initialize the object in setup()
    Serial.begin(9600); 
    while( !Serial );
}

void loop() {
    myCam.update();      // don't forget to call update() in loop(), otherwise you'll get coordinate values that are constant/unchanging.
    // then you can obtain the coordinate values by simply accessing p1.x, p1.y and so on to p4.x, p4.y (The camera only tracks up to four points )
    // when you get x=1023, y=1023 for a point, that means that point is not detected by the camera. It could be out of range, blocked, IR LED not lit, etc.
    // TIP : You can verify whether your IR LED is lit or not by looking at it through your smartphone camera ( or through a polarized sunglasses and then through the smartphone camera ).
    // If it's lit, it looks pretty close to a normal white LED. We can't tell whether the IR LED is lit or not through naked eyes, because the IR light spectrum is below the visible spectrum, but most smartphone cameras has a special filter that can see it.
    Serial.print( myCam.p1.x );
    Serial.print( "," );
    Serial.print( myCam.p1.y );
    Serial.print( "," );
    Serial.print( myCam.p2.x );
    Serial.print( "," );
    Serial.print( myCam.p2.y );
    Serial.print( "," );
    Serial.print( myCam.p3.x );
    Serial.print( "," );
    Serial.print( myCam.p3.y );
    Serial.print( "," );
    Serial.print( myCam.p4.x );
    Serial.print( "," );
    Serial.print( myCam.p4.y );
    Serial.println();
    delay( 20 );
    // TIP : Use the accompanying Processing example code in the ircamprocessing/ folder to see the detected points plotted on the screen. If you don't already have Processing installed on your computer, you can download it from www.processing.org
}
