#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.display();
   display.clearDisplay();
 // display.setFont(&FreeSans9pt7b);
   display.setTextSize(2);
  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,0);
  display.println("T: 34,5  C");display.drawCircle(102,2,2,WHITE);
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(0,16);
  display.println("U: 24,98 V");
   display.setCursor(0,36);
  display.println("I: 13,74 A");
  display.setTextSize(1);
   display.setCursor(30,55);
  // display.setFont();
  display.println("Home made test");
  //display.setTextSize(2);
 // display.setTextColor(WHITE);
  //display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
  display.clearDisplay();
}
   void loop() {
  
}

