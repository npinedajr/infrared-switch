// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
 
int RECV_PIN = 10; //The infrared reciever will be connected to pin 10 of the Arduino.
int RELAY = 2; //The relay module will be connected to pin 2 of the Arduino
 
// Define irrecev and results Objects
IRrecv irrecv(RECV_PIN); //Define a IRRecv object, which will be utilizing the infrared reciever.
decode_results results; //Define a decode_results object, which tracks what signal was recieved.
bool longPress;
 
void setup(){
  // Serial Monitor @ 9600 baud
  pinMode(RELAY, OUTPUT); //Set the relay module as an output. 
  digitalWrite(RELAY,LOW);
  irrecv.enableIRIn(); //Allow the infrared reciever to recieve signals. 
  longPress = false;
}

/* The following activates different code blocks, depending on the signal that the infrared reciever
 * recieves, which changes the behaviour of the relay module connected. If the infrared reciver no longer
 * recieves a signal, and the signal that was just recieved implies that a button was pressed down for a long
 * time, it will return the relay module to it's initial state. 
 */
void loop(){
  if(irrecv.decode(&results)){
    if(results.value == 0xFEA857){
      digitalWrite(RELAY, LOW);
      delay(100);
      digitalWrite(RELAY, HIGH);
      delay(4000);
      irrecv.resume();
  } else if(results.value == 0xFECA34){
      digitalWrite(RELAY,HIGH);
      longPress = true;
  } 
  else if(longPress = true){
    digitalWrite(RELAY, LOW);
    longPress = false;
   }
 }
}
