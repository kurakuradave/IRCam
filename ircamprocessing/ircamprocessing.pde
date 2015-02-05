/*
    This is the accompanying Processing example code for DFRobot Positioning IR Camera ( SKU: SEN0158 ).
    Basically, it's a camera that can "see" infrared lights and ascertain the coordinates of those lights, just like what's inside a Wiimote.
    It can track up to four infrared lights at a time.
    You can find more info on this sensor at https://www.dfrobot.com/index.php?route=product/product&product_id=1088
    
    WHAT THIS SKETCH DOES:
    Draws any detected infrared lights as circles onto the screen
    
    HOOKUP:
    IRCam+Arduino --USB cable--> computer running Processing   
    See how to hookup the IRCam to Arduino in the Wiki.
    
    MODIFICATION HISTORY:
    // Modified for http://www.DFRobot.com by kurakura, Jan. 2015 
    // Modified for http://www.DFRobot.com by Lumi, Jan. 2014
    // Example by Tom Igoe
*/
 
import processing.serial.*;
 
 
 
 
int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

// declare variables to hold coordinates for four points, and initialize them with the value of 1023
int p1x = 1023;
int p1y = 1023;
int p2x = 1023;
int p2y = 1023;
int p3x = 1023;
int p3y = 1023;
int p4x = 1023;
int p4y = 1023;
 
 // declare variables to hold color for the four points
 color p1color = color( 255, 0, 0 ); // RED
 color p2color = color( 0, 255, 0 ); // GREEN
 color p3color = color( 0, 0, 255 ); // BLUE
 color p4color = color( 255, 0, 255 ); // PURPLE
 
 
 
 
void setup() {
  // List all the available serial ports
  println(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  size(1023,768);
  frameRate(30);
}



 
void draw() {
  // preparation stage
  while( myPort.available() > 0 ) {
      myString = myPort.readStringUntil(lf);
     if( myString != null ) {
       convertmyStringToCoordinates();
     } 
  }
  
  // drawing stage   
  background(77); // repaint the whole drawing area with dark grey color (77,77,77), making the whole window clear and clean
  // immediately draw the circles after clearing, we've done the time-consuming preparation beforehand in convertmyStringToCoordinates() so this will give us minimal lag ( hopefully no flickering ).
  drawCircle( p1x, p1y, p1color );
  drawCircle( p2x, p2y, p2color );
  drawCircle( p3x, p3y, p3color );
  drawCircle( p4x, p4y, p4color );
}  



    
void drawCircle( int xval, int yval, color c ){ 
  if( xval != 1023 && yval != 1023 ){ // only draw when both x and y is not 1023. When x=1023 and y=1023, the point is NOT detected by the IR camera, i.e. out of range
    ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
    fill( c );  // Set the fill color
    ellipse(xval, yval, 20, 20); //draws an ellipse with with horizontal diameter of 20px andvertical diameter of 20px. 
  }
}




void convertmyStringToCoordinates() {
  println(myString); // display the incoming string

  // the next line does many things - it creates an array of integers named output, splits the string into 8 pieces of text, using comma as the delimiter, converts each of the 8 pieces of text into numbers and store them into the array in a sequential manner.  
  int[] output = int (split(trim(myString), ',')); 
  
  // now we need to copy the values from the array into global variables p1x..p4y, and make them available outside of this procedure.
  // because we need to access them at the drawing stage, later in the draw() cycle
  p1x = output[0];
  p1y = output[1];
       
  p2x = output[2];
  p2y = output[3];
       
  p3x = output[4];
  p3y = output[5];
       
  p4x = output[6];
  p4y = output[7];
}
