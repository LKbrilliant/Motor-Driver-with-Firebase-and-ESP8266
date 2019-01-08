// Code by   : LKBrilliant
// Date      : 21.10.2018
// Project   : Motor-Driver-with-Firebase-and-ESP8266

#define period 500

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "Your_Project_URL" // "xxxxxx.firebaseio.com" (without the 'https://')
#define FIREBASE_AUTH "Secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

void setup() {
  Serial.begin(115200);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void loop() {
  // get value
  Serial.print("Slider: ");
  Serial.print(Firebase.getInt("Slider"));
  delay(period);

  if (Firebase.failed()) {
    Serial.print("Reading_failed - ");
    Serial.println(Firebase.error());
    return;
  }
}
