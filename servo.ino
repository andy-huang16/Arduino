#include <Servo.h>                           // Include servo library
 
Servo servoRight;                            // Declare right servo
Servo servoLeft;

int photocellLeftPin = 0;
int photocellRightPin = 1;

int photocellLeftReading;
int photocellRightReading;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servoRight.attach(11);
  servoLeft.attach(12);
}

void loop() {
  
  photocellLeftReading =  analogRead(photocellLeftPin);
  photocellRightReading =  analogRead(photocellRightPin);

  //Serial.println(photocellRightReading);
  
  float i1, i2;

  i1 = photocellLeftReading;
  i2 = photocellRightReading;

  Serial.println(i1);
    
  float net1, net2, net3, net4, i3, i4, leftout, rightout;  

  i1 = (i1 - 0) / (300 - 0) ;
  i2 = (i2 - 0) / (300 - 0);
  
  net1 = (1 * -3.72238) + (i1 * 11.7148) + (i2 * -5.94883);
  net2 = (1 * 5.28202) + (i1 * -15.6578) + (i2 * 7.662);

  i3 = (1 / (1 + exp(net1)));
  i4 = (1 / (1 + exp(net2)));

  net3 = (1 * 1.40903) + (i3 * 13.9601) + (i4 * -18.0954);
  net4 = (1 * 7.05031) + (i3 * -15.0944) + (i4 * 25.7227);

  
  leftout = (1 / (1 + exp(net3)));
  rightout = (1 / (1 + exp(net4)));

  
  leftout = 1525 + (200 * leftout);
  rightout = 1475 - (200 * rightout); 

  
  
  servoRight.writeMicroseconds(rightout);       
  servoLeft.writeMicroseconds(leftout);
  
  
}