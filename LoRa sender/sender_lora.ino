/*
 * 23.06.2018
 * Added UV indeks average / 10 = UV
 *
*/

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  868E6

#define ONE_WIRE_BUS_PIN 4
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);
String appkey = APPKEY;
float saun = 0;
float vesi = 0;
float ohk = 0;
float rohk = 0;
float niiskus = 0;
float aku = 0;
int IDnum;

//UV analog input settings
const int UVnumReadings = 10;
float UVreadings[UVnumReadings];      // the readings from the analog input
int UVreadIndex = 0;              // the index of the current reading
float UVtotal = 0;                  // the running total
float UVaverage = 0;                // the average

int UVinputPin = 2;

DeviceAddress Probe01 = { 0x28, 0xFF, 0xC2, 0x23, 0x30, 0x18, 0x02, 0xE9 };
DeviceAddress Probe02 = { 0x28, 0xFF, 0x8C, 0x5E, 0x30, 0x18, 0x01, 0x75 };
DeviceAddress Probe03 = { 0x28, 0xFF, 0x19, 0x6B, 0x30, 0x18, 0x01, 0xD9 };

unsigned int counter = 0;

SSD1306 display(0x3c, 21, 22);
String rssi = "RSSI --";
String packSize = "--";
String packet ;



void setup() {
  pinMode(16,OUTPUT);
  pinMode(2,OUTPUT);

  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  Serial.begin(9600);
  while (!Serial);
  // del Serial.println();
  //del Serial.println("LoRa saatja");

  //reading UV value and averiging
  for (int UVthisReading = 0; UVthisReading < UVnumReadings; UVthisReading++) {
    UVreadings[UVthisReading] = 0;
  }

  randomSeed(analogRead(0));

  sensors.begin();
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);

  SPI.begin(SCK,MISO,MOSI,SS);

  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  //LoRa.onReceive(cbk);
  //LoRa.receive();
  //Serial.println("init ok");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  delay(1500);
}

void loop() {

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  IDnum = random(111, 999);

  sensors.requestTemperatures();
  float saun = sensors.getTempC(Probe01);
  float vesi = sensors.getTempC(Probe02);
  float ohk = sensors.getTempC(Probe03);

  // subtract the last reading:
  UVtotal = UVtotal - UVreadings[UVreadIndex];
  // read from the sensor:
  UVreadings[UVreadIndex] = analogRead(UVinputPin);
  // add the reading to the total:
  UVtotal = UVtotal + UVreadings[UVreadIndex];
  // advance to the next position in the array:
  UVreadIndex = UVreadIndex + 1;

  // if we're at the end of the array...
  if (UVreadIndex >= UVnumReadings) {
    // ...wrap around to the beginning:
    UVreadIndex = 0;
  }

  // calculate the average:
  UVaverage = UVtotal / UVnumReadings;

  // send it to the computer as ASCII digits
  Serial.println(UVaverage);
  delay(500);        // delay in between reads for stability


  display.drawString(0, 0, "Send ID: ");
  display.drawString(90, 0, String(IDnum));

  display.drawString(0, 12, "SAUN: ");
  display.drawString(90, 12, String(saun));
  display.drawString(0, 24, "VESI: ");
  display.drawString(90, 24, String(vesi));
  display.drawString(0, 36, "ÕHK: ");
  display.drawString(90, 36, String(ohk));
  display.drawString(0, 48, "UV index: ");
  display.drawString(90, 48, String(UVaverage));

  display.display();

//  Serial.print("Probe 01 temperature is:   ");
  Serial.println();

    String packet;
    packet += saun;
    packet += "/";
    packet += vesi;
    packet += "/";
    packet += ohk;
    packet += "/";
    packet += rohk;
    packet += "/";
    packet += niiskus;
    packet += "/";
    packet += UVaverage;
    packet += "/";
    packet += aku;
    packet += "/";
    packet += appkey;
    //del packet += "/";
    //del packet += IDnum;

  Serial.println(packet);


  // send packet
  LoRa.beginPacket();
  LoRa.print(packet);
  //LoRa.print(counter);
  LoRa.endPacket();

  //counter++;
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  delay(3000);
}
