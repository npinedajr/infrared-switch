// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>

IRsend irsend;

unsigned long pressedMillis = 0; //Will track at what millisecond the button connected to pin 8 has been pressed. 
const unsigned holdPeriod = 1500; //The button must be held for 1.5 seconds to be considered a long press. Can be adjusted based on needs.
bool longPress; 
int currentState;
int previousState; //previousState tracks if currentState is HIGH or LOW in the previous loop.

void setup(){
  pinMode(2, INPUT); //Pin 8 of an Arduino will have a button connected, which will serve as input.
  longPress = false; 
  currentState = LOW;
  previousState = LOW;
}

/* The following activates different blocks of code depending on the state of the button connected to 
 * pin 8. If the button is pressed down for at least 1.5 seconds, then the infrared led connected 
 * to the Arduino will send a signal that a infrared reciever will decode. If the button is pressed for 
 * less than 1.5 seconds, then the infrared led will send a different signal for the infrared reciever to decode. 
 */
void loop(){
  currentState = digitalRead(2); // When the button connected to pin 8 in the Arduino is pressed, currentState will be HIGH. Otherwise, it will be LOW. 
  if(currentState == HIGH && previousState == LOW){
    pressedMillis = millis();
  }
  if(currentState == HIGH && (millis()-pressedMillis)>=holdPeriod){
    irsend.sendNEC(0xFECA35,32);
    longPress = true;
  }
  if(currentState == LOW && previousState == HIGH && longPress == false && (millis()-pressedMillis)<holdPeriod ){
    irsend.sendNEC(0xFE8A75,32);
  } else {
    longPress = false;
  }
  previousState = currentState; 
}
