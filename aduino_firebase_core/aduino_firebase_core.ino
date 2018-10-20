#define period 1000

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "https://dld-v3.firebaseio.com"
#define FIREBASE_AUTH "z85j1z58AL6Xqbl9HofAU4SYSYDYCF6v6ipXUR4P"
#define WIFI_SSID "TP-LINK_C6173C"
#define WIFI_PASSWORD "0312240888"

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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // get value
  Serial.print("Slider: ");
  Serial.println(Firebase.getInt("Slider"));
  delay(period);

  if (Firebase.failed()) {
    Serial.print("Reading_failed - ");
    Serial.println(Firebase.error());
    return;
  }
  delay(period);
}
