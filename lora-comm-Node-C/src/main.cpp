/*NODE B*/
#include <Arduino.h>
int voltage_reader = A3;  // Analog pin for voltage measurement
const int red = 4;
const int yellow = 3;
const int green = 2;
void signal_led(String s){
  if (s.equals("good")){
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  }else if(s.equals("low")){
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  }else{
  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  }
};
void setup() {
  Serial.begin(115200);  // Initialize serial communication
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}
void loop() {
  int sensorValue = analogRead(voltage_reader);  // Read the analog input voltage
  float voltage = sensorValue * (5.0 / 1023.0);  // Convert sensor value to voltage (0-5V range)
  
  if (voltage >= 3.5 && voltage <= 5.0) {
     signal_led("good");
     Serial.println("AT+SEND=4,4,C_on");
  } else if (voltage > 0.9 && voltage < 3.5) {
      signal_led("low");
     Serial.println("AT+SEND=4,5,C_low");
  } else {
    signal_led("down");
    Serial.println("AT+SEND=4,6,C_down");
  }
  delay(4000);  // Delay for stability (you can adjust this as needed)
}