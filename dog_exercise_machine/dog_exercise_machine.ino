
#include <Servo.h> 

//------

// initialize pins for two boxes/dog sensors
// you can chane this to acommodate more boxes
int echo_pins[2] = {7, 12};
int trig_pins[2] = {8, 13};
int last_box_passed = -1;

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

  pinMode(trig_pins[0], OUTPUT);
  pinMode(echo_pins[0], INPUT);  

  pinMode(trig_pins[1], OUTPUT);
  pinMode(echo_pins[1], INPUT);  
}

// choose any nonzero amount less than 1
// 1 being a full feed, close to zero to mean a tiny feed
void feedDog(int amount) {
  // turn 180 degrees in one direction
  for(servo_angle = 0; servo_angle < 180; servo_angle++)  
  {                                  
    servo.write(servo_angle);               
    delay(20);                   
  } 
  
  // now turn back 180 degrees to 0 degrees
  for(servo_angle = 180; servo_angle > 0; servo_angle--)    
  {                                
    servo.write(servo_angle);           
    delay(20);       
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

boolean is_something_there (int boxNumber) {
   long duration, distance;
 
  // send the pulse
   boolean dog_detected = false;
   digitalWrite(trig_pins[boxNumber], LOW); 
   delayMicroseconds(2); // low for 2 microseconds
   digitalWrite(trig_pins[boxNumber], HIGH);
   delayMicroseconds(10); // high for 10 microseconds
   digitalWrite(trig_pins[boxNumber], LOW);
   duration = pulseIn(echo_pins[boxNumber], HIGH); // measure the time to the echo
   distance = (duration / 2) / 29.1;  // calculate the distance in centimeters
      
       
   if (distance < triggerBoundary) {
     Serial.println("DOG DETECTED");  
     Serial.println(distance);   
     dog_detected = true;
   }
   else {
     Serial.println("NO DOG DETECTED");
     Serial.println(distance);
   }
      
   return dog_detected;
}

void loop() {
  Serial.println("-------------------");
   int i;
    // loop through both sensors and check if a dog has passed through, triggering a feeding if it ha
    for (i = 0; i < 2; i = i + 1) {
       if (is_something_there(i) == true) {
         
         if (i == 0) { // dog has entered the first box
           last_box_passed = 0;
         }
         else if (i == 1 && last_box_passed == 0) // dog has entered the second box
         {
           feedDog(1);
           last_box_passed = -1;
         }        
         
       }
    }

 
  delay(1000);      
}
