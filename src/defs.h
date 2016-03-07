#include <SPI.h>
#include <Wire.h>

///////////////////////////// DISPLAY /////////////////////////////////////
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Check library. It must define proper value, if not, you should edit it
#if (SSD1306_LCDHEIGHT != 64)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

// Create display
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

///////////////////////////// HUMIDITY SENSOR /////////////////////////////////////
#include <DHT.h>
#define DHTPIN 2 
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);


///////////////////////////// PRESSURE SENSOR /////////////////////////////////////
#include <Adafruit_BMP085_U.h>
Adafruit_BMP085_Unified bmp;
// SDA to SDA (20)
// SLC to SLC (21)


///////////////////////////// Luxmeter /////////////////////////////////////
#include <BH1750.h>
BH1750 lightMeter;


///////////////////////////// Clock /////////////////////////////////////
#include <stdio.h>
#include <DS1302.h>
const int kCePin   = 5;  // RST
const int kIoPin   = 6;  // DAT
const int kSclkPin = 7;  // CLK
DS1302 rtc(kCePin, kIoPin, kSclkPin);

