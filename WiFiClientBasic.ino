/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "DHT.h"

#ifndef STASSID
#define STASSID "WE_AFD587"
#define STAPSK  "25205081716"
#define DHTPIN D5
#define DHTTYPE DHT11 
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.8.172";
const uint16_t port = 7654;

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }

  // This will send the request to the server
  client.println("hello from ESP8266");

  //read back one line from server
  Serial.println("receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);

  //Serial.println("closing connection");
 // client.stop();

  //Serial.println("wait 5 sec...");
  delay(5000);


// pinMode(DHTPIN,INPUT)

  
  dht.begin();
  pinMode(DHTPIN,INPUT);
}


void loop() 
{
  //Serial.print("yazeed");
  //client.write("hello from zozz");


  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

// Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;}

float hif = dht.computeHeatIndex(f, h);
float hic = dht.computeHeatIndex(t, h, false);

Serial.print("Humidity: ");
//client.print("Humidity: ");

Serial.print(h);
client.print(h);

Serial.print("% Temperature: ");
//client.print("% Temperature: ");

Serial.print(t);
client.print(t);

Serial.print("°C");
client.print("°C  ");

//Serial.print(f);
//client.print(f);

//Serial.print("°F  Heat index: ");
//client.println("°F  Heat index: ");

//Serial.print(hic);
//client.print(hic);
//client.write(" Humidity: " + "°F" + h + "%Temperature");

//Serial.print(F("°C "));
//client.print(F("°C "));

//Serial.print(hif);
//client.print(hif);

//Serial.println("°F");
//client.println("°F");



delay(10000);

 
  
}
