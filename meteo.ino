#include <SoftwareSerial.h>

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

String dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}

//void setupTime() {
//  Time t(2013, 9, 22, 1, 51, 00, Time::kSunday);
//  
//  rtc.writeProtect(false);
//  rtc.halt(false);
//  rtc.time(t);
//  rtc.writeProtect(true);
//}

String getTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  return buf;
}

void loop() {
  float humidity = dht.readHumidity(); 
  float temp1 = dht.readTemperature();
  float temp2 = bmp.readTemperature();
  float pres = bmp.readPressure() / 133.322;
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

