#include <Servo.h>  //kushal poudel nepro

const int trigPin = 6;    // Ultrasonic sensor trig pin
const int echoPin = 7;    // Ultrasonic sensor echo pin
const int servoPin = 8;   // Servo motor control pin

Servo lidServo;            // Create a servo object to control the lid
int lidClosedAngle = 0;    // Angle to close the lid
int lidOpenAngle = 90;     // Angle to open the lid
bool isLidOpen = false;    // Flag to track if the lid is currently open

void setup() {
  Serial.begin(9600);      // Initialize serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lidServo.attach(servoPin);  // Attach the servo to its pin
  lidServo.write(lidClosedAngle); // Start with the lid closed
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the time it takes for the ultrasonic pulse to return
  duration = pulseIn(echoPin, HIGH);
  
  // Convert the time to distance (in centimeters)
  distance = duration * 0.034 / 2;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check if an object is detected within range (adjust as needed)
  if (distance < 20 && !isLidOpen) { // Open the lid if it's not already open
    openLid(); // Open the lid
    isLidOpen = true; // Set the flag to indicate that the lid is open
  } else if (distance >= 20 && isLidOpen) { // Close the lid if it's open and no object is detected
    closeLid(); // Close the lid
    isLidOpen = false; // Set the flag to indicate that the lid is closed
  }
  
  delay(1000); // Wait for a second before taking another reading
}

void openLid() {
  Serial.println("Opening lid...");
  lidServo.write(lidOpenAngle); // Open the lid
}

void closeLid() {
  Serial.println("Closing lid...");
  lidServo.write(lidClosedAngle); // Close the lid
}
