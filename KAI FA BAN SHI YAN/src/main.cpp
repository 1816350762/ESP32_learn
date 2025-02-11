#include <Arduino.h>
#include <FastLED.h>
#include <TFT_eSPI.h>
#include <DHT.h>

// 硬件配置
#define DHTPIN 16
#define DHTTYPE DHT11
#define LED_PIN 48
#define NUM_LED 1
#define POT 17

// 外设对象
CRGB leds[NUM_LED];
DHT dht(DHTPIN, DHTTYPE);
TFT_eSPI tft = TFT_eSPI();

// 中断相关变量
volatile bool btn1Pressed = false;
volatile bool btn2Pressed = false;
volatile bool btn3Pressed = false;
volatile uint16_t potValue = 0;
hw_timer_t *timer = NULL;

// 按钮中断服务程序
IRAM_ATTR void handleButton1() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 200) { // 简单防抖
    btn1Pressed = true;
    lastMillis = millis();
  }
}

IRAM_ATTR void handleButton2() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 200) {
    btn2Pressed = true;
    lastMillis = millis();
  }
}

IRAM_ATTR void handleButton3() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 200) {
    btn3Pressed = true;
    lastMillis = millis();
  }
}

// 电位器定时读取中断
IRAM_ATTR void readPotentiometer() {
  potValue = analogRead(POT);
}

// 画蛇函数
void drawSnake() {
  // 蛇的颜色
  uint16_t snakeColor = TFT_GREEN; // 蛇的身体颜色
  uint16_t eyeColor = TFT_RED;     // 蛇的眼睛颜色
  uint16_t tongueColor = TFT_RED;  // 蛇的舌头颜色

  // 蛇的身体（更复杂的形状）
  tft.fillRoundRect(40, 80, 20, 20, 5, snakeColor);  // 蛇头
  tft.fillRoundRect(20, 80, 20, 20, 5, snakeColor);  // 蛇身
  tft.fillRoundRect(0, 80, 20, 20, 5, snakeColor);   // 蛇尾

  // 蛇的眼睛
  tft.fillCircle(50, 90, 3, eyeColor);  // 右眼
  tft.fillCircle(50, 100, 3, eyeColor); // 左眼

  // 蛇的舌头
  tft.fillTriangle(60, 90, 65, 95, 60, 100, tongueColor); // 舌头
}

// 写“蛇年大吉”函数
void drawText() {
  tft.setCursor(10, 130); // 文字起始位置
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); // 文字颜色为黄色，背景为黑色
  tft.setTextSize(2); // 文字大小
  tft.println("蛇年大吉");
}

void setup() {
  // 初始化LED
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LED);
  FastLED.setBrightness(10);
  FastLED.clear();
  FastLED.show();

  // 初始化串口
  Serial.begin(115200);

  // 初始化按钮（使用内部上拉）
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);

  // 设置按钮中断
  attachInterrupt(digitalPinToInterrupt(37), handleButton1, FALLING);
  attachInterrupt(digitalPinToInterrupt(38), handleButton2, FALLING);
  attachInterrupt(digitalPinToInterrupt(39), handleButton3, FALLING);

  // 初始化电位器定时器中断（每100ms读取一次）
  timer = timerBegin(0, 80, true); // 80MHz分频
  timerAttachInterrupt(timer, &readPotentiometer, true);
  timerAlarmWrite(timer, 100000, true); // 100ms
  timerAlarmEnable(timer);

  // 初始化DHT传感器
  dht.begin();

  // 初始化TFT屏幕
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  // 画蛇和文字
  drawSnake();
  drawText();
}

void loop() {
  // 温度显示部分
  tft.setCursor(0, 0);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.println("Now Temperature:");

  tft.fillRect(0, 10, tft.width(), 16, TFT_BLACK);
  float t = dht.readTemperature();
  tft.setCursor(0, 10);
  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(2);
  tft.print(t);

  // 处理按钮事件
  if (btn1Pressed) {
    leds[0] = CRGB::Red;
    FastLED.show();
    btn1Pressed = false;
  } else if (btn2Pressed) {
    leds[0] = CRGB::Blue;
    FastLED.show();
    btn2Pressed = false;
  } else if (btn3Pressed) {
    leds[0] = CRGB::Yellow;
    FastLED.show();
    btn3Pressed = false;
  }

  // 显示电位器值
  float potPercent = potValue / 4095.0 * 100;
  tft.setCursor(0, 40);
  tft.setTextColor(TFT_PINK);
  tft.setTextSize(2);
  tft.print(potPercent);

  // 仅清除电位器数值区域
  delay(100);
  tft.fillRect(0, 40, tft.width(), 20, TFT_BLACK);

  // 每次循环重新绘制小蛇和文字
  drawSnake();
  drawText();
}