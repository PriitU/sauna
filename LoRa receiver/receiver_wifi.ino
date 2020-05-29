/*
 *  LoRa receiver and WiFi connector
 *
 *  v2020.1 (21.05.2020)
 */
#include "WiFi.h"
#include <HTTPClient.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h"
#include <ArduinoJson.h>
//#include "images.h"

// Pin definetion of WIFI LoRa 32
// HelTec AutoMation 2017 support@heltec.cn
#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define SS      18   // GPIO18 -- SX127x's CS
#define RST     14   // GPIO14 -- SX127x's RESET
#define DI0     26   // GPIO26 -- SX127x's IRQ(Interrupt Request)

#define BAND    868E6
#define PABOOST true

SSD1306 display(0x3c, 21, 22);
String rssi = "RSSI --";
String packSize = "--";
String packet ;

const char* ssid = SSID;
const char* password = PWD;
const char* host = URI;

long randNum;
float sauna;
float water;
float air;
float pressure;
float humidity;
float UV;
float BAT_voltage;
int resetCount = 0;

String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void logo(){
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(15,25,"SAUNA IoT");
  display.display();
  display.setFont(ArialMT_Plain_10);
}

void connectWifi(){
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high、

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  logo();
  delay(2500);
  display.clear();

  Serial.begin(9600);

  connectWifi();

  Serial.println("Setup done");

  Serial.println();
  Serial.println("LoRa Receiver Callback");

  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    display.drawString(0, 0, "Starting LoRa failed!");
    display.display();
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  display.drawString(0, 0, "LoRa Initial success!");
  display.drawString(0, 10, "Waiting for incomm data...");
  display.display();
  delay(1500);
  //LoRa.onReceive(cbk);
  LoRa.receive();

  Serial.println("init ok");

  Serial.println("Setup done");
  delay(1500);
}


void loop()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String received = "";

    while (LoRa.available()) {
      received += (char) LoRa.read();
    }

    //Serial.println(received);
    String url = host;
    //url += "/";
    //url += packet;
    String sauna = getValue(received, '/', 0);
    String water = getValue(received, '/', 1);
    String air = getValue(received, '/', 2);
    String pressure = getValue(received, '/', 3);
    String humidity = getValue(received, '/', 4);
    String UVaverage = getValue(received, '/', 5);
    String battery = getValue(received, '/', 6);

    String msg = "";
    msg += "{\"sauna\":" + sauna;
    msg += ",\"water\":" + water;
    msg += ",\"air\":" + air;
    msg += ",\"airPressure\":" + pressure;
    msg += ",\"humidity\":" + humidity;
    msg += ",\"uv\":" + UVaverage;
    msg += ",\"battery\":" + battery;
    msg += "}";

    Serial.println(msg);
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(url);
      http.addHeader("Content-Type", "application/json");

      Serial.print("Requesting URL: ");
      Serial.println(url);
      int httpCode = http.POST(msg);
      if (httpCode > 0) { //Check for the returning code
            DynamicJsonDocument doc(500);
            deserializeJson(doc, http.getString());
            const char* code = doc["message"];
            Serial.print("Code return element = ");
            Serial.println(code);

            //String payload = http.getString();
            //Serial.println(httpCode);
            //Serial.println(payload);
      } else {
          Serial.println("Error on HTTP request");
          String payload = http.getString();
          Serial.println(httpCode);
          Serial.println(payload);
      }

      display.clear();
      display.drawString(0, 0, "SAUN: ");
      display.drawString(70, 0, sauna);
      display.drawString(0, 12, "VESI: ");
      display.drawString(70, 12, water);
      display.drawString(0, 24, "ÕHK: ");
      display.drawString(70, 24, air);
      display.drawString(0, 36, "UV: ");
      display.drawString(70, 36, UVaverage);
      display.drawString(0, 48, "POST: ");
      display.drawString(70, 48, String(httpCode)+" / "+ String(resetCount));
      display.display();

      http.end();
      //Serial.println("Loop End");
      delay(60000);
    } else {
      resetCount++;
      connectWifi();
    }
  }
  //Serial.println("New Loop");
}
