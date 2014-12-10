
#include <Servo.h> 

int echo_pin = 7;
int trig_pin = 8;
int servo_pin = 9;
int servo_angle = 0;
const int power_button_pin = 4;     

int sensorValue = 1000;  
int triggerBoundary = 19;   // you should calibrate--this is the distance boundary of a physical object from the sensor to trigger some action

Servo servo;  

boolean power_state = false; // power off until button pressed

void setup() {
  
  servo.attach(servo_pin); 

  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);

  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);  
}

// choose any nonzero amount less than 1
// 1 being a full feed, close to zero to mean a tiny feed
void feedDog(int amount) {
  // turn 180 degrees in one direction
  for(servo_angle = 0; servo_angle < 180; servo_angle++)  
  {                                  
    servo.write(servo_angle);               
    delay(2);                   
  } 
  
  // now turn back 180 degrees to 0 degrees
  for(servo_angle = 180; servo_angle > 0; servo_angle--)    
  {                                
    servo.write(servo_angle);           
    delay(2);       
  } 
}

void swap_power_state() {
  if (power_state == true)
  {
    power_state = false;
  } else {
    power_state = true;
  }
}

void loop() {
  Serial.println("-------------------");
  Serial.println(digitalRead(power_button_pin));
  if (digitalRead(power_button_pin) == LOW)
  {
    swap_power_state();
    Serial.println("Power state changed");
    Serial.println(power_state);
  }
  
   
  if (power_state == true) {
    
    long duration, distance;
  
    // send the pulse
    digitalWrite(trig_pin, LOW); 
    delayMicroseconds(2); // low for 2 microseconds
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10); // high for 10 microseconds
    digitalWrite(trig_pin, LOW);
    duration = pulseIn(echo_pin, HIGH); // measure the time to the echo
    distance = (duration / 2) / 29.1;  // calculate the distance in centimeters
    
     
    if (distance < triggerBoundary) {
      Serial.println("DOG DETECTED");  
      Serial.println(distance);
      feedDog(1);
    }
    else {
      Serial.println("NO DOG DETECTED");
      Serial.println(distance);
    }
    
     delay(150);   
  }
 
  delay(100);      
}
