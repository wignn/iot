#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 0          // pin D3 (GPIO0) pada NodeMCU ESP8266
#define ss 15             // pin D8 (GPIO15) pada NodeMCU ESP8266
#define rst 16            // pin D0 (GPIO16) pada NodeMCU ESP8266
#define dio0 4            // pin D2 (GPIO4) pada NodeMCU ESP8266
int counter = 0;

DHT dht(DHTPIN, DHT22);
void setup()
{
  Serial.begin(115200);
  dht.begin();

  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" degrees Celcius, Humidity: ");
  Serial.println(h);
  Serial.println();
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print(F("Pkt No:"));
  LoRa.println(counter);

  LoRa.print("Temp: ");
  LoRa.print(t);
  LoRa.println("°C");

  LoRa.print("Hum:  ");
  LoRa.print(h);
  LoRa.print("%");
  LoRa.println("");

  LoRa.endPacket();

  counter++;

  delay(3000);
}