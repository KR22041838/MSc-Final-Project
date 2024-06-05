/* 
 This Code has been adapted from a combonation of the following source codes:
 
 Servo Sweep Code:
 * by BARRAGAN <http://barraganstudio.com>
 * This example code is in the public domain.

 * modified 8 Nov 2013
 * by Scott Fitzgerald
 * https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep

 Joystick code:
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick-servo-motor
 */




/* ---------------------------------------Randy the Rabbit--------------------------------------------------
 *  by KiriAnn Rodenburg
 
 This 'Final Expression Code' controls the animatronic eyes of games-master 'Randy the Rabbit' to rotate about 
 the x and y axis, to give fully articulated eye motion and is controlled using a joystick. 
 A second joystick controls the rotation of the eyebrows. 

 This code has issues with feedback connecting to the 4th 'eyebrow' servo, the code will work initially
 to give full control over the facial expression of the animatronic, however after a minuet of so 
 the eyebrow connect to servo 'ebServo2' will start to jitter, rotate on its own or stop rotating at all.

 I have not managed to fix this in time so the code used for the exhibition has been adapted to 
 get round this issue. See code: Expression_Exhibition_Code. 

 ------------------------------------------------------------------------------------------------------------
 */

#include <Servo.h>
#include <ezButton.h>

// Define Joysticks (Attach pins to names)
#define VRX_EM_PIN      A0
#define VRY_EM_PIN      A1
#define VRX_EB_PIN      A2 
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
  button.loop(); // Update the button state

  // Check if the update interval has passed
  if (millis() - lastUpdateTime > UPDATE_INTERVAL) {
    lastUpdateTime = millis(); // Update the last update time

    // Read and process joystick inputs for eye movement
    readJoystickInputs(VRX_EM_PIN, VRY_EM_PIN, xValue_EM, yValue_EM, xServo, yServo);
    
    // Read and process joystick inputs for eyebrow movement
    readJoystickInputs(VRX_EB_PIN, VRY_EB_PIN, lValue_EB, rValue_EB, ebServo, ebServo2); 
  }

  // Check if the button is pressed
  if (button.isPressed()) {
    Serial.println("The button is pressed");
    resetServoAngles(); // Reset all servos to their default angles
  }

  printServoAngles(); // Print the current angles of the servos to the serial monitor
}

void readJoystickInputs(int VRX_PIN, int VRY_PIN, int& xValue_eye, int& yValue_eye, Servo& servo1, Servo& servo2) {
  xValue_eye = analogRead(VRX_PIN); // Read the x-axis value of the joystick
  yValue_eye = analogRead(VRY_PIN); // Read the y-axis value of the joystick

  command = COMMAND_NO; // Reset command

  // Determine the direction of joystick movement and set the corresponding command
  if (xValue_eye < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue_eye > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  if (yValue_eye < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue_eye > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  processJoystickCommand(command, servo1, servo2); // Process the joystick command to move the servos
}

void processJoystickCommand(int command, Servo& servo1, Servo& servo2) {
  // Adjust servo1 angle based on the command
  if (command & COMMAND_LEFT) {
    servo1.write(servo1.read() - 2);
  }

  if (command & COMMAND_RIGHT) {
    servo1.write(servo1.read() + 2);
  }

  // Adjust servo2 angle based on the command
  if (command & COMMAND_UP) {
    servo2.write(servo2.read() + 2);
  }

  if (command & COMMAND_DOWN) {
    servo2.write(servo2.read() - 2);
  }
}

void resetServoAngles() {
  // Reset all servos to their default angles (90 degrees)
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
  // Print the current angles of all servos to the serial monitor
  Serial.print("Servo Motor's Angles: ");
  Serial.print("X: ");
  Serial.print(xServo.read());
  Serial.print("°, Y: ");
  Serial.print(yServo.read());
  Serial.print("°, Z: ");
  Serial.print(ebServo.read());
  Serial.println("°");
}
