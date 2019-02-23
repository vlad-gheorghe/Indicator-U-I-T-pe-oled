/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers
  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98
This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!
Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Adafruit_ADS1015.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;
float curent = 0.0;
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int temp;

//#define VT_PIN A0 
//#define AT_PIN A1
//unsigned long tpmasurare;  // variabila pentru memorare timp masurare (in ms)
//float sumatensiune = 0.;   // valoare insumare tensiune pentru calcul medie
//float sumacurent = 0.;
//int trcurent = 0;
//int trtensiune = 0;

//float current = 0.;   // valoare curent
//float tensiune = 0.; // valoare tensiune

//#if (SSD1306_LCDHEIGHT != 32)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

void setup()   {                
  Serial.begin(9600);
//analogReference(INTERNAL); // punem referinta interna de 1,1V;
  //\
  sensors.begin();
  ads.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
 //display.setRotation(2); 
  display.display();
  delay(50);
 pinMode(13, OUTPUT); 
digitalWrite(13, LOW);

  // Clear the buffer.
  display.clearDisplay();

 

}


void loop() {
///sumatensiune = 0;

 // sumacurent = 0;
 //   for (int i=1; i <= 20; i++)
 // {
 //trtensiune = analogRead(VT_PIN);
 
// sumatensiune = sumatensiune + trtensiune;
 // trcurent = analogRead(AT_PIN);

//  sumacurent = sumacurent + trcurent;
//delay (20);  // pauza de 20ms intre masuratori
//    }
//sumacurent = sumacurent/20.;
//sumatensiune = sumatensiune/20.;
//tensiune=(float)(97.5+.974)/.974*1.08*sumatensiune/1023;
//current=(float)1.08/0.1*sumacurent/1023;  
 int16_t adc0;  // we read from the ADC, we have a sixteen bit integer as a result
int16_t adc1;
  adc0 = ads.readADC_SingleEnded(0);
  Voltage = (adc0 * 0.1875)/1000;
  adc1 = ads.readADC_SingleEnded(1);
  curent = (adc1 * 0.1875)/1000;
   sensors.requestTemperatures();  
 float temp = sensors.getTempCByIndex(0);
 
display.setFont(&FreeSans9pt7b);
//display.setTextSize(1.999);
  display.setTextColor(WHITE);
  display.setCursor(0,30);
  display.println("U:");display.setTextColor(WHITE,BLACK);
  display.fillRect(26, 18, 75, 18, BLACK);display.display();
  //delay(3000);
   display.setCursor(28,30);display.setTextColor(WHITE);
   display.println(Voltage,5);display.display();
    display.setCursor(110,30); display.println(" V");
  //display.setFont();
  
  display.setCursor(0,50);
  
   
  display.println("I :");
  display.setCursor(26,50);display.setTextColor(WHITE);
  display.fillRect(26, 35, 75, 18, BLACK);display.display();
   display.println(curent,5);display.display();
   display.setCursor(110,50); display.println("A");
  display.display();
   if ((temp) < 35)
  digitalWrite(13,LOW);
  if ((temp) > 40)
  digitalWrite(13, HIGH);
  
  display.setFont(&FreeSans9pt7b);
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,12);
  
  display.println("T:");display.drawCircle(82,2,2,WHITE);
   display.setCursor(90,12);display.println("C");
   display.fillRect(16, 0, 60, 16,BLACK);
    display.setCursor(26,12);display.println(temp,2);
  display.setCursor(30,60);
   display.setFont();
  display.println("Home made test");
}

