#include "defs.h"

const int FREQUENCY = 500;

void setup()   {                
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.display();
  
  dht.begin();
  
  lightMeter.begin();

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
}

void setupTime() {
  Time t(2013, 9, 22, 1, 51, 00, Time::kSunday);
  
  rtc.writeProtect(false);
  rtc.halt(false);
  rtc.time(t);
  rtc.writeProtect(true);
}

String getTime() {
  Time t = rtc.time();

  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  return buf;
}

void loop() {
  float humidity = dht.readHumidity(); 
  float temp1 = dht.readTemperature();

  float temp2;
  float pres;
  bmp.getTemperature(&temp2);
  bmp.getPressure(&pres);
  pres = pres / 133.322;
  
  uint16_t lux = lightMeter.readLightLevel();
  String datetime = getTime();
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.print("Hum   ");
  display.print(humidity);
  display.println("%");
  
  display.print("Temp1 ");
  display.print(temp1);
  display.println(" C");
  
  display.print("Pres  ");
  display.print(pres);
  display.println(" mm");
  
  display.print("Temp2 ");
  display.print(temp2);
  display.println(" C");
  
  display.print("Light ");
  display.print(lux);
  display.println(" lux");
  
  display.println(datetime);

  display.display();
  delay(FREQUENCY);
}

