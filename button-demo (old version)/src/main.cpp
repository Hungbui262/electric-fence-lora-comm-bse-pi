#include <Arduino.h>
#include <SPI.h>
const int led = 2;
const int button = 3;
bool ledState = false;
bool buttonState = false; 

long lastDebouncetime = 0;
long debounceDelay = 200;
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}
void loop() {
  buttonState = digitalRead(button); // read the button state
  if((millis() - lastDebouncetime) > debounceDelay){
    if (buttonState == HIGH) { // if the button is pressed
      ledState = !ledState; // toggle the LED state
      digitalWrite(led, ledState); // set the LED pin to the new state
      if(ledState){
        Serial.println("AT+SEND=2,5,ledOn");
      }else{
        Serial.println("AT+SEND=2,6,ledOff");
      }
      lastDebouncetime = millis();
    }
  }
}