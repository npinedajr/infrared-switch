// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
 
int RECV_PIN = 10; //The infrared reciever will be connected to pin 10 of the Arduino.
int RELAY = 4; //The relay module will be connected to pin 2 of the Arduino
 
// Define irrecev and results Objects
IRrecv irrecv(RECV_PIN); //Define a IRRecv object, which will be utilizing the infrared reciever.
decode_results results; //Define a decode_results object, which tracks what signal was recieved.
 
void setup(){
  pinMode(RELAY, OUTPUT); //Set the relay module as an output. 
  pinMode(RECV_PIN, INPUT);
  digitalWrite(RELAY,LOW);
  irrecv.enableIRIn(); //Allow the infrared reciever to recieve signals. 
}

/* The following activates different code blocks, depending on the signal that the infrared reciever
 * recieves, which changes the behaviour of the relay module connected.
 */
void loop(){
  if(irrecv.decode(&results)){
    switch (results.value){
      case 0xFE8A75:
        digitalWrite(RELAY, LOW);
        delay(100);
        digitalWrite(RELAY, HIGH);
        delay(4000);
        irrecv.resume();
        break;
        
       case 0xFECA35:
        digitalWrite(RELAY,HIGH);
        delay(10000);
        digitalWrite(RELAY,LOW);
        irrecv.resume();
        break;

       default:
        irrecv.resume();
        break;
      }
    }
}
