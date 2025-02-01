#include <TFT_eSPI.h>
#include "nanshen10.h"  //加载自定义字体
#include "shou14.h"
#include "deyihei20.h"
#include "yuan24.h"
#include "1.h"

TFT_eSPI tft;

void setup() {
  tft.begin();                //初始化TFT屏幕
  tft.fillScreen(TFT_BLACK);  //刷屏底色为黑色
}

void loop() {

  tft.setCursor(0, 10);  //设置光标位置


  tft.setTextColor(TFT_PINK);  
  tft.loadFont(font_data);  //加载默认字体
  tft.println("顽疾猖狂");

  tft.setCursor(0, 60);
  tft.setTextColor(TFT_PINK); 
  tft.println("NB");
}