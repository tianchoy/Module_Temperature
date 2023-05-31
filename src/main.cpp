#include "DHT.h"
#include <Adafruit_Sensor.h>

int fengshan = 9;

int wendu=25;
#define DHTPIN 2

#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(fengshan,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHT test!"));
  
  //初始化模块
  dht.begin();
}

void loop() {
  // 测量之间等待2秒钟。
  delay(2000);

  float h = dht.readHumidity();
  // 以摄氏度读取温度(默认值)
  float t = dht.readTemperature();
  // 将温度读取为华氏温度(isFahrenheit = true)
  float f = dht.readTemperature(true);

  // 检查是否有读取失败并提前退出(再试一次)。
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // 计算华氏热度指数(默认值)
  float hif = dht.computeHeatIndex(f, h);
  // 以摄氏度计算热指数(isfahrenheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  //打印数值(华氏度的注释掉了)
  //打印湿度
  Serial.print(F("Humidity: "));
  Serial.print(h);
  //打印温度
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));

  if(t > wendu ){
    digitalWrite(fengshan,HIGH);
    Serial.print(F("HIGH: "));
  }else{
    digitalWrite(fengshan,LOW);
    Serial.print(F("LOW: "));
  }
  delay(1000);
  //Serial.print(f);
  //Serial.println(F("°F"));
  //打印热指数
  Serial.print(F("  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.println();
  //Serial.print(hif);
  //Serial.println(F("°F"));
}
