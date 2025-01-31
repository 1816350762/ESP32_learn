/*
  Ellipse drawing example
  
  This sketch does not use any fonts.
*/

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
int evacolor=TFT_BLACK;
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

char randomChar(int i);
const int maxDrops=30;
int dropX[maxDrops];
int dropY[maxDrops];
char randomC[maxDrops];
int dropspeed[maxDrops];


void setup(void) {
  Serial.begin(112500);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_DARKGREEN);
  tft.setCursor(10, 0);
 // tft.println("TEST_EVA");
  randomSeed(analogRead(1));
  for(int i=0;i<maxDrops;i++){
    dropX[i]=random(0,128);
    dropY[i]=random(0,160);
    randomC[i]=randomChar(1); 
    dropspeed[i]=random(1,5);
  }
}

void loop() {
  tft.fillScreen(TFT_BLACK);

  for(int i=0;i<maxDrops;i++){
    tft.setCursor(dropX[i],dropY[i]);
    tft.println(randomC[i]);
    dropY[i]=dropY[i]+dropspeed[i];
      if(dropY[i]>160){
        dropX[i]=random(0,128);
        dropY[i]=random(0,160);
        randomC[i]=randomChar(1); 
        dropspeed[i]=random(1,5);
    }
 // delay(100);

  }


  delay(100);
  Serial.println(analogRead(1));
}

char randomChar(int i){
  if(i==1){
    int charIndex=random(0,95);
    return char(charIndex+32);
  }
  else if(i==2){
    int charIndex=random(0,2);
    return char(charIndex+'0');
  }
}
 

