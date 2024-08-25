# Smart-Walking-Stick

This project demonstrates how to use an Arduino to integrate an ultrasonic sensor for distance measurement, a GPS module for location tracking, and a buzzer for obstacle detection alerts.

## Components Used

- **Arduino Uno**: Microcontroller board.
- **Ultrasonic Sensor (HC-SR04)**: Measures distance to obstacles.
- **GPS Module (e.g., Neo-6M)**: Provides location data.
- **Buzzer**: Emits sound when an obstacle is detected.

## Circuit Diagram

- **Ultrasonic Sensor**
  - `Trig` Pin to Arduino Pin 2
  - `Echo` Pin to Arduino Pin 3

- **GPS Module**
  - `TX` Pin to Arduino Pin 8
  - `RX` Pin to Arduino Pin 9

- **Buzzer**
  - `Positive` Pin to Arduino Pin 4
  - `Negative` Pin to Arduino GND

## Code Files

### `ultrasonic_gps_buzzer.ino`

This is the main Arduino sketch that handles ultrasonic distance measurement, GPS data retrieval, and buzzer control.

```cpp
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
```
## How to Use

1. **Upload Code**: Open the `ultrasonic_gps_buzzer.ino` file in the Arduino IDE and upload it to your Arduino board.
2. **Connect Components**: Follow the circuit diagram to connect the ultrasonic sensor, GPS module, and buzzer to the Arduino.
3. **Monitor Output**: Open the Serial Monitor in the Arduino IDE to view the GPS coordinates and distance readings. The buzzer will sound if an obstacle is detected within the defined threshold distance.

## Installation

### Arduino IDE

- Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
- Open the provided `.ino` file and upload it to the Arduino board.

### Libraries

- Install the following Arduino libraries through the Library Manager:
  - **TinyGPS++**: For GPS data parsing.
  - **SoftwareSerial**: For serial communication with the GPS module.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! Please fork this repository and submit a pull request with your improvements.

## Notes

- Ensure you have the necessary libraries (`TinyGPS++` and `SoftwareSerial`) installed in the Arduino IDE.
- Adjust the distance threshold and buzzer activation time based on your specific requirements.

