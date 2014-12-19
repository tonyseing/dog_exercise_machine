# How to make an exercise machine for your dog

(note: there is still a lot of documentation coming for the casing section)

###Introduction

The good folks at Intel Mashery were nice enough to send me a free Intel Edison. They asked me to make something cool with it. 

For those who haven't seen one before, it looks like this:

![enter image description here](https://lh3.googleusercontent.com/rItpu_llC82tZCDVt9SdKmqkgdu7_-t1pc7ZGD2YhPY=s0 "intel_edison.jpg")


My dog is currently away at my parents' home in Connecticut, so I have missed her a lot. I decided to make her a gift for Christmas. The device is an exercise machine to keep her occupied when I have to leave her at home alone.


![Adorable dog](https://lh5.googleusercontent.com/vhjw43EExjB106SXdVR69AvfhZDvd2EMwYQKb2v1rrs=s0 "Adorable Dog")

### How it works

I thought of a dozen other contraptions before I settled on what I realize now was probably the simplest, most practical design. The requirements for the machine were: automatically provide food for the dog when she proved that she had done some physical work. This machine be flexible enough to work in both large and confined spaces. I live in a smallish apartment in the New York City area, so it would be unfeasible for me to have such a contraption if it required ownership of a yard.

I thought of systems requiring rope and pulleys to dangle something my dog would chase, but I decided that they were too large and that constant jumping could lead to back problems for dogs.

I decided to place two boxes far apart from each other, and affix ultrasonic sensors to the top of them. The sensors would detect when the dog was passing through, and when she has passed through both, the machine would use a servo motor to open the mouth to a funnel of dog food for a quick moment, releasing a small parcel of dog treats.


###What you'll need



* 1 bored dog
* 3 moderately large boxes
* 1 Arduino board -- I used an Intel Edison microprocessor with an Arduino breakout board
* 2 HC-SR04 ultrasonic sensors
* 1 standard servo
* Duct tape
* 3 breadboards
* Insulated 22cm copper wire
* Scissors



![enter image description here](https://lh3.googleusercontent.com/WprsjVgsSoqMPuO1lXXCxjHPJlBacOwuGl-OFYkjNVA=s0 "The bare necessities")



### Electronics

I've provided a schematic of how the machine is wired below. I created this in Fritzing, a neat schematic-drawing tool. Essentially, you'll affix two ultrasonic sensors to breadboards and your breakout board. The HC-SR04 has four pins:

VCC: +5V DC
Trig : Trigger (INPUT)
Echo: Echo (OUTPUT)
GND: GND

We're going to send out a pulse through the echo and track the time required for the sound to come back to the sensor. This will give us an idea of how far away an object is from the sensor, which in our case, is a dog. 

![enter image description here](https://lh3.googleusercontent.com/-cU0Vz-ATYDs/VJHSWeUkBII/AAAAAAAANp8/_ufhjH-woM8/s0/blueprint.jpg "blueprint.jpg")

The accompanying setup code to make these sensors work looks like this:

    int echo_pins[2] = {7, 12};
    int trig_pins[2] = {8, 13};
    pinMode(trig_pins[0], OUTPUT);
    pinMode(echo_pins[0], INPUT);  
    pinMode(trig_pins[1], OUTPUT);
    pinMode(echo_pins[1], INPUT);  

In your loop function, your code will look like this:

    digitalWrite(trig_pins[boxNumber], LOW); 
    delayMicroseconds(2); // low for 2 microseconds
    digitalWrite(trig_pins[boxNumber], HIGH);
    delayMicroseconds(10); // high for 10 microseconds
    digitalWrite(trig_pins[boxNumber], LOW);
    duration = pulseIn(echo_pins[boxNumber], HIGH); // measure the time to the echo
    distance = (duration / 2) / 29.1;  

This block of code shoots a soundwave out from our sensor and tracks the time it takes to echo back. You'll then use this distance to make decisions about triggering the servo.

Here is the entire function detecting if your dog has passed through both box checkpoints:

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


### Casing



![enter image description here](https://lh6.googleusercontent.com/-BZDf3E9ZlZR9uT-xFA7ncm2QMgnGlYSLEgUXs_CMMM=s0 "20141210_164612.jpg")


![enter image description here](https://lh3.googleusercontent.com/sdzsrf_BGX0__iJMzVbMTZVnpR5xLw-ho-VbQfxzJn8=s0 "20141210_190824.jpg")



![enter image description here](https://lh5.googleusercontent.com/IkgYOtmEOoKX95WudQtcmybMj7q3aKzAWlSasCg5M3Q=s0 "20141210_190816.jpg")

![enter image description here](https://lh5.googleusercontent.com/qtAqi9fpmuQ7tFMtqOWUZMftpEIaJ879D_7h0F6kc2k=s0 "20141217_085127.jpg")

![enter image description here](https://lh6.googleusercontent.com/iKIlAFrzudKUD-lK_DaH4c5DcDxeXA2z2v9OS83looo=s0 "20141210_202219.jpg")

![enter image description here](https://lh3.googleusercontent.com/1e8fStzHCpkD0gILHZ6HP1l3MBkRqkrHBPnttjBth_k=s0 "20141217_043921.jpg")

![enter image description here](https://lh6.googleusercontent.com/HWXQz1YFk0W7YIWMntMx18t4LerNBEYHT96Xh_CLbV4=s0 "20141217_082503.jpg")

![enter image description here](https://lh3.googleusercontent.com/mn7EhwvmftcSfnILcjn0Nznl5vMJl9Gi9FPbOkCNnX8=s0 "20141217_082332.jpg")

![enter image description here](https://lh4.googleusercontent.com/91CZMa7hF84xfDJ5r3qMpKmigqzNBXKzq80-mo7AuGo=s0 "20141217_083135.jpg")

![enter image description here](https://lh4.googleusercontent.com/9AKlkpCMwqVglXlxDJ81SVDJ8I2bM47OP_cP9LWuMPU=s0 "20141217_084228.jpg")

![enter image description here](https://lh5.googleusercontent.com/3HYEo6nxTK81OvK4IsFFuWNbZkzXoyB1prPqVymmgoY=s0 "20141217_085035.jpg")

![enter image description here](https://lh6.googleusercontent.com/y3ULCd7g-yuJgScaZ160mX5akqW2g8CskQSkpFs38O4=s0 "20141217_085503.jpg")

<a href="http://www.youtube.com/watch?feature=player_embedded&v=shv30x-xJkk" target="_blank"><img src="http://img.youtube.com/vi/shv30x-xJkk/0.jpg" 
 width="240" height="180" border="10" /></a>


