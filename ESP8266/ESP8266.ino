#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "wastiya-616c8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Ivo191MW9aGqPfgH4MSkTFVSkkhKUmQ1GvwDZ8po"
#define WIFI_SSID "Wifi_Name" 
#define WIFI_PASSWORD "Wifi_Password" 

#define TRIG_PIN D1
#define ECHO_PIN D2
#define BATTERY_PIN A0 // Analog pin to read battery voltage

#define BATTERY_THRESHOLD 100 // Set the threshold below which battery level is considered 0%

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Set default battery level to 100%
  Firebase.setInt("/devices/-NrQ7hiYs4Px79qkXGfQ/battery", 100);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    long duration, distance;
    
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = (duration * 0.0343) / 2; // Calculate distance in cm

    int garbageLevel = map(distance, 0, 100, 100, 0); // Map distance to garbage level percentage

    // Limit garbage level to a minimum of 0
    garbageLevel = max(garbageLevel, 0);

    int batteryValue = analogRead(BATTERY_PIN); // Read battery voltage

    // Assuming a 3.3V reference voltage, calculate the actual voltage
    float voltage = batteryValue * (3.3 / 1023.0);

    // Map the voltage to a percentage (assuming a 4.2V maximum voltage for a fully charged battery)
    int batteryLevel;
    if (voltage > BATTERY_THRESHOLD) {
      batteryLevel = map(voltage * 100, 0, 420, 0, 100);
    } else {
      batteryLevel = 100; // Set battery level to 100% if voltage is below threshold
    }

    Firebase.setInt("/devices/-NrQ7hiYs4Px79qkXGfQ/garbage", garbageLevel); // Update Firebase with garbage level

    Firebase.setInt("/devices/-NrQ7hiYs4Px79qkXGfQ/battery", batteryLevel); // Update Firebase with battery level

    Serial.print("Garbage Level: ");
    Serial.println(garbageLevel);

    Serial.print("Battery Level: ");
    Serial.print(batteryLevel);
    Serial.println("%");
  } else {
    Serial.println("WiFi Disconnected");
    delay(1000);
  }

  delay(1000); // Wait for 1 second
}
