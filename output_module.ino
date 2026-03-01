#include <M5Stack.h>
#include <Arduino.h>

int freqlvl = 1; //input1;
int ampllvl = 1; //input2;
float i = 0;
float j = 0;
void setup() {
  M5.begin();
  M5.Lcd.begin();
  ledcSetup(1, 1000, 8);
  ledcSetup(2, 1000, 8);
  ledcAttachPin(12, 1);
  ledcAttachPin(15, 2);
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setTextSize(2);  //appropriate text size to ensure text fits within the screen
}

void loop() {
  M5.update();
  M5.Lcd.fillScreen(PINK); //sets background to pink to erase previous text on screen
  M5.Lcd.setCursor(10 , 10); //set cursor to same position every time so relevant texts print on same positions as previously

//if statement to check if frequency level value is valid or not
  if(freqlvl<6 && freqlvl>0){   
    i = 0.2+0.15*(freqlvl-1); //formula derived to match given specifications in MainTaskDetails_2021.pdf
    M5.Lcd.print("Frequency(Hz) = ");
    M5.Lcd.println(i);
    ledcWrite(1, 51*(freqlvl-1)); //formula derived to generate PMW signal that matches input frequency level
  } else {M5.Lcd.fillScreen(PINK); M5.Lcd.setCursor(10 , 10); M5.Lcd.print("Invalid Frequency Input");};
  
  M5.Lcd.setCursor(10 , 80);
  
  if(ampllvl<6 && ampllvl>0){  
    j = ampllvl*10;
    M5.Lcd.print("Amplitude(%) = ");
    M5.Lcd.println(j);
    ledcWrite(2, 51*(ampllvl-1));
  } else {M5.Lcd.setCursor(10 , 80); M5.Lcd.print("Invalid Amplitude Input");};

  delay(100); //10ms delay is appropriate for implementing output according to changes in heartbeat&sound
}
