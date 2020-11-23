#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans12pt7b.h>

 Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

// Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
   ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
   display.begin(SSD1306_SWITCHCAPVCC);
  // display.display();
   display.clearDisplay();
  delay(10);
  ads.begin();
}

void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3;
display.setFont(&FreeSans12pt7b);
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  Serial.print("AIN0: "); Serial.println(((adc0*0.0625*22.9933)/1000),3);
  Serial.print("AIN1: "); Serial.println(adc1*0.0625);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");
  float u=((adc0*0.0625*22.9933)/1000);
  float i=(adc1*0.0625)/43.47;
  delay(500);
   display.setTextColor(WHITE);
  display.setCursor(0,30);
  display.println("U:");display.setTextColor(WHITE,BLACK);
  display.fillRect(26, 10, 75, 25, BLACK);display.display();
  //delay(3000);
   display.setCursor(28,30);display.setTextColor(WHITE);
   display.println(u,3);display.display();
    display.setCursor(105,30); display.println(" V");
  //display.setFont();
  
  display.setCursor(3,55);
  
   
  display.println("I :");
  display.setCursor(26,55);display.setTextColor(WHITE);
  display.fillRect(26, 35, 75, 25, BLACK);display.display();
   display.println(i,3);display.display();
   display.setCursor(110,55); display.println("A");
  display.display();
  //display.setFont();
 // display.setCursor(40,0);display.println("@ 2020 Vlad");display.display();
}
