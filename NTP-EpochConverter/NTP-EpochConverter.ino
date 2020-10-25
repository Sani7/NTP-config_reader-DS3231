#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

// Replace with your network credentials
const char *ssid     = "SSID";
const char *password = "PSWD";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +2 = 7200
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(7200);
}



void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  char currentTime[8];
  sprintf(currentTime, "%d:%d:%d", hour(epochTime), minute(epochTime), second(epochTime));
  Serial.print("Current time: ");
  Serial.println(currentTime);
  char currentDate[9];
  sprintf(currentDate, "%d/%d/%d", day(epochTime), month(epochTime), year(epochTime));
  Serial.print("Current date: ");
  Serial.println(currentDate);
  delay(1000);
}
