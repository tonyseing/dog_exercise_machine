
int echoPin = 7;
int trigPin = 8;
int sensorValue = 1000;  
int triggerBoundary = 4;   // you should calibrate--this is the distance boundary of a physical object from the sensor to trigger some action


void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}

void loop() {
  long duration, distance;

  // send the pulse
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); // low for 2 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // high for 10 microseconds
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // measure the time to the echo
  distance = (duration/2) / 29.1;  // calculate the distance in cm
  
   
  if (distance < triggerBoundary) {
    Serial.println("DOG DETECTED");  
  }
  else {
    Serial.println("NO DOG DETECTED");
  }
  
  
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range; reading invalid");
  }
  else {
    //Serial.print(distance);
    //Serial.println(" cm");
  }
  delay(1000);         
}
