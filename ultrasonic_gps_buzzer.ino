#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define trigPin 2
#define echoPin 3
#define buzzerPin 4

SoftwareSerial gpsSerial(8, 9); // RX, TX
TinyGPSPlus gps;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  // Ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  // GPS
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
        Serial.print("Latitude: ");
        Serial.println(latitude, 6);
        Serial.print("Longitude: ");
        Serial.println(longitude, 6);
      }
    }
  }

  // Buzzer control based on obstacle detection
  if (distance < 50) { // Adjust this threshold as needed
    // Obstacle detected, activate buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(1000); // Buzzer on for 1 second
    digitalWrite(buzzerPin, LOW);
  }

  delay(1000); // Adjust delay as needed
}
