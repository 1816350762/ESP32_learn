/*
//------【关注我学ESP32】--------
//｜｜B站：伊娃老师来了 ｜｜ 公众号：伊娃来了//

//////////////功能介绍///////////////////

这段代码是一个基于Arduino平台的时钟和天气信息显示程序。
以下是主要功能的介绍：

- 时钟和日期显示： 通过连接到WiFi网络，并利用NTP服务器获取精准的网络时间，代码实时更新并显示年、月、日、星期、时、分、秒等时钟信息。
- 天气信息获取和显示： 通过HTTP请求连接到心知天气API，获取北京地区的实时天气信息（温度和天气状况），并将其显示在屏幕上。
- 动画显示： 利用屏幕上的动画效果，展示了无牙仔的动画。

///////////////////////////////////////
*/

//引入字体与图片的头文件

#include "number.h"
#include "number2.h"
#include "noto10.h"
#include "toothlessWhite80.h"
//引入tft库
#include <TFT_eSPI.h>
// TFT 屏幕和精灵对象
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);


// 引入网络时间相关库
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// WiFi连接信息
const char *ssid = "Xiaomi";           // WiFi账号，需自行修改
const char *password = "ycy750510";  // WiFi密码，需自行修改
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com");  // NTP服务器地址

//引入JSON解析库
#include <ArduinoJson.h>
#include <HTTPClient.h>
// 天气API信息
String key = "S7_LRrH-T5QjS8gan"; //需自行修改
String city = "chongqing"; //可修改城市的全拼，获取城市的天气
String api = "https://api.seniverse.com/v3/weather/now.json?key=" + key + "&location=" + city + "&language=zh-Hans&unit=c";
HTTPClient http;
String weatherText;
int temperature;

// 星期名称定义
const char weekdays_cn[8][10] = { "0", "周一", "周二", "周三", "周四", "周五", "周六", "周日" };
const char weekdays_en[8][10] = { "0", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat", "Sun" };

// 时间变量
int currentYear = 0;
int currentWeekDay = 0;
int currentMonth = 0;
int currentMonthDay = 0;
int currentHour = 0;
int currentMin = 0;
int currentSec = 0;

// 动画变量
int currentFrame = 0;



void animation();
void getWeather();
void updateFunction(unsigned long interval, void (*func)());
void updateTime();


// 函数定义
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // 等待WiFi连接
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  timeClient.setTimeOffset(28800);

  // 初始化 TFT 屏幕和精灵
  tft.begin();
  tft.setRotation(0);
  sprite.setColorDepth(16);
  sprite.setSwapBytes(true);
  sprite.createSprite(128, 160);

  // 获取天气信息
  getWeather();
}

void loop() {
  // 定时更新动画、时间和天气
  updateFunction(100, animation);
  updateFunction(300000, getWeather);
}

void animation() {
  // 每0.1秒更新一次动画
  updateTime();
  sprite.fillScreen(TFT_WHITE);
  sprite.pushImage(24, 65, 80, 80, toothlessWhite[currentFrame]);
  
  // 显示时间
  sprite.loadFont(number);
  sprite.setTextColor(TFT_BLACK);
  sprite.setCursor(20, 20);
  sprite.print(currentHour);
  sprite.print(" : ");
  sprite.print(currentMin);

  // 显示秒钟
  sprite.setCursor(105, 34);
  sprite.loadFont(number2);
  sprite.print(currentSec);

  // 显示日期和星期
  sprite.loadFont(noto10);
  sprite.setCursor(18, 50);
  sprite.print(currentYear);
  sprite.print("年");
  sprite.print(currentMonth);
  sprite.print("月");
  sprite.print(currentMonthDay);
  sprite.print("日  ");
  sprite.println(weekdays_cn[currentWeekDay]);
  
  // 显示天气信息
  sprite.setCursor(18, 63);
  sprite.print("北京温度:");
  sprite.print(temperature);
  sprite.print("   天气:");
  sprite.print(weatherText);

  // 将精灵内容推送到屏幕
  sprite.pushSprite(0, 0);
  currentFrame = (currentFrame + 1) % frames;  // 更新动画帧
}

void getWeather() {
  // 获取天气信息
  DynamicJsonDocument doc(1024);
  Serial.println(api);
  http.begin(api);
  int httpGet = http.GET();
  if (httpGet > 0) {
    Serial.printf("HTTPGET is %d", httpGet);
    if (httpGet == HTTP_CODE_OK) {
      String json = http.getString();
      Serial.println(json);
      deserializeJson(doc, json);
      weatherText = doc["results"][0]["now"]["text"].as<String>();
      temperature = doc["results"][0]["now"]["temperature"];
      Serial.print("占用字节数量：");
      Serial.println(measureJsonPretty(doc));
      Serial.print("天气");
      Serial.println(weatherText);
      Serial.print("温度");
      Serial.println(temperature);
    } else {
      Serial.println("服务器错误");
    }
  } else {
    Serial.printf("服务器响应失败");
  }
  http.end();
}

void updateFunction(unsigned long interval, void (*func)()) {
  // 定时执行更新函数
  unsigned long currentMillis = millis();
  static unsigned long lastUpdate = 0;
  if (currentMillis - lastUpdate >= interval) {
    lastUpdate = currentMillis;
    func();
  }
}

void updateTime() {
  // 更新时间信息
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  currentYear = ptm->tm_year + 1900;
  currentMonth = ptm->tm_mon + 1;
  currentMonthDay = ptm->tm_mday;
  currentWeekDay = ptm->tm_wday;
  if (currentWeekDay < 0) {
    currentWeekDay += 7;
  }
  currentHour = ptm->tm_hour;
  currentMin = ptm->tm_min;
  currentSec = ptm->tm_sec;
}