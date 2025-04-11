#include <Servo.h>
#include <NewPing.h>

// ==== Ultrasonic Sensor (HC-SR04) ====
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
float initialDistance = 0;
float finalDistance = 0;

// ==== TCS3200 Color Sensor ====
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define SENSOR_OUT 8

int redFrequency, greenFrequency, blueFrequency;

// ==== Servo Motor ====
Servo titrationServo;
int servoPin = 3;

// ==== Setup ====
void setup() {
  Serial.begin(9600);

  // Setup pins for TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Attach the servo
  titrationServo.attach(servoPin);
  titrationServo.write(0);  // Start with valve closed

  delay(2000); // wait for sensor to settle

  initialDistance = sonar.ping_cm();
  Serial.print("Initial Distance: ");
  Serial.println(initialDistance);
}

// ==== Main Loop ====
void loop() {
  // Open valve
  titrationServo.write(90); // Open knob
  delay(1000);              // Allow some flow

  // Measure current volume level
  finalDistance = sonar.ping_cm();
  float volumeUsed = initialDistance - finalDistance;
  Serial.print("Volume Used (cm): ");
  Serial.println(volumeUsed);

  // Read color frequencies
  redFrequency = readColor('R');
  greenFrequency = readColor('G');
  blueFrequency = readColor('B');

  Serial.print("Red: "); Serial.print(redFrequency);
  Serial.print(" Green: "); Serial.print(greenFrequency);
  Serial.print(" Blue: "); Serial.println(blueFrequency);

  // Check if color has changed (endpoint reached)
  if (blueFrequency > redFrequency && blueFrequency > greenFrequency) {
    Serial.println("Color Change Detected: Endpoint Reached!");
    titrationServo.write(0); // Close knob
    while (true); // Halt further actions
  }

  delay(1000); // Small delay before next loop
}

// ==== Read Color Function ====
int readColor(char color) {
  switch (color) {
    case 'R':
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      break;
    case 'G':
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      break;
    case 'B':
      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      break;
  }

  int frequency = pulseIn(SENSOR_OUT, LOW);
  return frequency;
}
