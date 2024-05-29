#include <Servo.h>
#include <ezButton.h>

// Define Joysticks (Attach pins to names)
#define VRX_EM_PIN      A0
#define VRY_EM_PIN      A1
#define VRX_EB_PIN      A2 // Don't need for EB2 as all controlled by this one 
#define VRY_EB_PIN      A3
#define b_PIN         2

// Define Servos (Attach pins to names)
#define SERVO_X_EYE   3
#define SERVO_Y_EYE   4
#define SERVO_EB   10
#define SERVO_EB2  9

// Give names to flags(Joystick positions) and assign value for readability 
#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

// Define threshold values for Joystick directions
#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

//Define update interval in milliseconds 
#define UPDATE_INTERVAL 100

// Initialize objects/Create objects and name them
ezButton button(b_PIN);
Servo xServo;
Servo yServo;
Servo ebServo;
Servo ebServo2;

// Initialize variables/give starting value
int xValue_EM = 0;
int yValue_EM = 0;
int lValue_EB = 0;
int rValue_EB = 0;
int xAngle_eye = 90;  // Starting postion of servo 90 degrees 
int yAngle_eye = 90;
int ebAngle = 90;
int ebAngle2 = 90;
int command = COMMAND_NO; // Variable to store current command
unsigned long lastUpdateTime = 0; // Variable to store time of last update

void setup() {
  Serial.begin(9600);

  // Attach Servos to Pins
  xServo.attach(SERVO_X_EYE);
  yServo.attach(SERVO_Y_EYE);
  ebServo.attach(SERVO_EB);
  ebServo2.attach(SERVO_EB2);
  
  button.setDebounceTime(50); // Set debounce time for button
}

void loop() {
  button.loop();

  if (millis() - lastUpdateTime > UPDATE_INTERVAL) {
    lastUpdateTime = millis();

    readJoystickInputs(VRX_EM_PIN, VRY_EM_PIN, xValue_EM, yValue_EM, xServo, yServo);
    readJoystickInputs(VRX_EB_PIN, VRY_EB_PIN, lValue_EB, rValue_EB, ebServo, ebServo2 ); 
  }

  if (button.isPressed()) {
    Serial.println("The button is pressed");
    resetServoAngles();
  }

  printServoAngles();
}

void readJoystickInputs(int VRX_PIN, int VRY_PIN, int& xValue_eye, int& yValue_eye, Servo& servo1, Servo& servo2) {
  xValue_eye = analogRead(VRX_PIN);
  yValue_eye = analogRead(VRY_PIN);

  command = COMMAND_NO;

  if (xValue_eye < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue_eye > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  if (yValue_eye < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue_eye > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  processJoystickCommand(command, servo1, servo2);
}

void processJoystickCommand(int command, Servo& servo1, Servo& servo2) {
  if (command & COMMAND_LEFT) {
    servo1.write(servo1.read() - 2);
  }

  if (command & COMMAND_RIGHT) {
    servo1.write(servo1.read() + 2);
  }

  if (command & COMMAND_UP) {
    servo2.write(servo2.read() + 2);
  }

  if (command & COMMAND_DOWN) {
    servo2.write(servo2.read() - 2);
  }
}

void resetServoAngles() {
  xAngle_eye = 90;
  yAngle_eye = 90;
  ebAngle = 90;
  ebAngle2 = 90;

  xServo.write(xAngle_eye);
  yServo.write(yAngle_eye);
  ebServo.write(ebAngle);
  ebServo2.write(ebAngle2);
}

void printServoAngles() {
  Serial.print("Servo Motor's Angles: ");
  Serial.print("X: ");
  Serial.print(xServo.read());
  Serial.print("°, Y: ");
  Serial.print(yServo.read());
  Serial.print("°, Z: ");
  Serial.print(ebServo.read());
  Serial.println("°");
}
