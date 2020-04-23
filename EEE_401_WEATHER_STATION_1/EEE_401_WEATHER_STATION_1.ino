 #include <Arduino.h>
#include <U8g2lib.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif




#include "DHT.h"

#define DHTPIN 13 

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);




U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display





void setup(void) {

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();

  u8g2.begin();
  u8x8.begin();  
  u8x8.setPowerSave(0);
}



void loop(void) {
  //delay(2000);
  

 float hum,tem,ftem,hic;

 
  hum = dht.readHumidity();
  // Read temperature as Celsius (the default)

  tem = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)

  ftem = dht.readTemperature(true);

  hic = dht.computeHeatIndex(tem, hum, false);






 

  
  char h[5];
  char t[5];
  char f[5];
  char n[5];

  itoa(hum, h, 10);
  itoa(tem, t, 10);
  itoa(ftem, f, 10);
  itoa(hic, n, 10);





u8g2.clearBuffer();          // clear the internal memory
u8g2.setFont(u8g2_font_inb16_mf);
u8g2.drawStr(30,20,"TEMP"); // write something to the internal memory
u8g2.drawUTF8(25, 50, t);
u8g2.drawStr(70,50,"*C");
u8g2.sendBuffer();          // transfer internal memory to the display
delay(3000);
u8g2.clear();
u8g2.nextPage();



u8g2.drawStr(0,20,"HUMIDITY"); // write something to the internal memory
u8g2.drawUTF8(25, 50, h);
u8g2.drawStr(70,50,"%");
u8g2.sendBuffer();          // transfer internal memory to the display
delay(3000);
u8g2.clear();
u8g2.nextPage();




u8g2.drawStr(15,20,"H INDEX"); // write something to the internal memory
u8g2.drawUTF8(25, 50, n);
u8g2.drawStr(70,50,"*C");
u8g2.sendBuffer();          // transfer internal memory to the display
delay(3000);
u8g2.refreshDisplay();    // only required for SSD1606/7  
delay(3000);
u8x8.clear();
}
//git commit -m
