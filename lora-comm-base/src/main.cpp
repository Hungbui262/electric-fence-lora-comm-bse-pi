
#include <Arduino.h>
#include <LiquidCrystal.h>
int status[] = {0,0,0};
String incommingString;
String result_on  = "";
String result_off = "";
String result_low = "";
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void checkStatus(String s){
  if(s == "A_low"){
    status[0] = 1;
  } else if(s == "A_down"){
    status[0] = 0;
  } else if(s == "A_on"){
    status[0] = 2;
  } else if (s == "B_low"){
    status[1] = 1;
  } else if( s =="B_down"){
    status[1] = 0;
  } else if(s == "B_on"){
    status[1] = 2;
  }else if (s == "C_low"){
    status[2] = 1;
  } else if( s =="C_down"){
    status[2] = 0;
  } else if(s == "C_on"){
    status[2] = 2;
  }
}

void lcdResult(){
  result_on  = "";
  result_off = "";
  result_low = "";
  for (int i = 0; i < 3; i++){
    if(status[i] == 2 && i == 0){
      result_on = result_on + "A";
    } else if(status[i] == 1 && i == 0){
      result_low = result_low + "A";
    } else if(status[i] == 0 && i == 0){
      result_off = result_off + "A";
    } else if(status[i] == 2 && i == 1){
      result_on = result_on + "B";
    } else if(status[i] == 1 && i == 1){
      result_low = result_low + "B";
    } else if(status[i] == 0 && i == 1){
      result_off = result_off + "B";
    } else if(status[i] == 2 && i == 2){
      result_on = result_on + "C";
    } else if(status[i] == 1 && i == 2){
      result_low = result_low + "C";
    } else if(status[i] == 0 && i == 2){
      result_off = result_off + "C";
    }
  }
}
void printLcd(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ON: ");
  lcd.print(result_on);
  lcd.setCursor(8,0);
  lcd.print("LOW: ");
  lcd.print(result_low);
  lcd.setCursor(0,1);
  lcd.print("Down: ");
  lcd.print(result_off);
}
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  
}
void loop() {
  if(Serial.available()){
    incommingString = Serial.readString();
    int firstComma = incommingString.indexOf(",");
    int secondComma = incommingString.indexOf(",", firstComma + 1);
    int thirdComma = incommingString.indexOf(",", secondComma + 1);
    String result = incommingString.substring(secondComma + 1, thirdComma);
    Serial.println(result);
    checkStatus(result);
    lcdResult();
    printLcd();
    }
}