#include <Servo.h>
#include <ezButton.h>
#include <SoftwareSerial.h>

// Define Joysticks (Attach pins to names)
#define VRX_EM_PIN      A0
#define VRY_EM_PIN      A1
#define VRX_EB_PIN      A2 // Don't need for EB2 as all controlled by this one 
#define VRY_EB_PIN      A3
#define VRX_VO_PIN      A4 // mp3 
#define VRY_VO_PIN      A5 // mp3
#define b_PIN           2

// Define Servos (Attach pins to names)
#define SERVO_X_EYE   3
#define SERVO_Y_EYE   4
#define SERVO_EB      10
#define SERVO_EB2     9

// Give names to flags (Joystick positions) and assign value for readability 
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

// Define debounce time and update interval in milliseconds 
#define DEBOUNCE_TIME    50
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
int xValue_VO = 0;
int yValue_VO = 0;
int xAngle_eye = 90;  // Starting position of servo 90 degrees 
int yAngle_eye = 90;
int ebAngle = 90;
int ebAngle2 = 90;
int command = COMMAND_NO; // Variable to store current command
unsigned long lastUpdateTime = 0; // Variable to store time of last update

// Initialize serial communication for MP3 player
SoftwareSerial mySerial(10, 11);
boolean isPlaying = false;

// Define MP3 player commands
#define Start_Byte 0x7E
#define Version_Byte 0xFF
#define Command_Length 0x06
#define End_Byte 0xEF
#define Acknowledge 0x00 // Returns info with command 0x41 [0x01: info, 0x00: no info]

// MP3 player commands
#define PLAY_PAUSE    1
#define NEXT_SONG     2
#define PREVIOUS_SONG 3
#define PLAY_SONG     4


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Attach Servos to Pins
  xServo.attach(SERVO_X_EYE);
  yServo.attach(SERVO_Y_EYE);
  ebServo.attach(SERVO_EB);
  ebServo2.attach(SERVO_EB2);
  
  button.setDebounceTime(DEBOUNCE_TIME); // Set debounce time for button
  
  delay(1000);
  playFirst();
  isPlaying = true;
}

void loop() {
  button.loop();

  if (millis() - lastUpdateTime > UPDATE_INTERVAL) {
    lastUpdateTime = millis();

    readJoystickInputs(VRX_EM_PIN, VRY_EM_PIN, xValue_EM, yValue_EM, xServo, yServo);
    readJoystickInputs(VRX_EB_PIN, VRY_EB_PIN, lValue_EB, rValue_EB, ebServo, ebServo2);
    readMP3JoystickInputs(VRX_VO_PIN, VRY_VO_PIN, xValue_VO, yValue_VO);
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

void playFirst() {
  // Implement the actions needed to play the first song
  execute_CMD(0x3F, 0, 0); // Command to initialize the MP3 module
  delay(500);
  setVolume(20); // Set volume to a desired level
  delay(500);
  execute_CMD(0x11, 0, 1); // Command to start playing the first song
  delay(500);
}


void readMP3JoystickInputs(int VRX_PIN, int VRY_PIN, int& xValue_mp3, int& yValue_mp3) {
  xValue_mp3 = analogRead(VRX_PIN);
  yValue_mp3 = analogRead(VRY_PIN);

  if (xValue_mp3 < LEFT_THRESHOLD) {
    executeMP3Command(PLAY_PAUSE);
    Serial.println("Left - Pausing Audio");
  } else if (xValue_mp3 > RIGHT_THRESHOLD) {
    executeMP3Command(NEXT_SONG);
    Serial.println("Right - Next Audio");
  }
  
  if (yValue_mp3 < UP_THRESHOLD) {
    executeMP3Command(PREVIOUS_SONG);
    Serial.println("Up - Previous Audio");
  } else if (yValue_mp3 > DOWN_THRESHOLD) {
    executeMP3Command(PLAY_SONG);
    Serial.println("Up - Play Audio");
  }
}

void executeMP3Command(int command) {
  // Implement MP3 control based on the command received
  switch(command) {
    case PLAY_PAUSE:
     execute_CMD(0x0E, 0, 0); // Pause the track
      delay(500);
      break;
    case NEXT_SONG:
      execute_CMD(0x01, 0, 1); // Play the next track
      delay(500);
      break;
    case PREVIOUS_SONG:
      execute_CMD(0x02, 0, 1); // Play the previous track
      delay(500);
      break;
    case PLAY_SONG:
      execute_CMD(0x0D, 0, 1); // Play the track
      delay(500);
      break;
    default:
      break;
  }
}

void setVolume(int volume) {
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}

void execute_CMD(byte CMD, byte Par1, byte Par2) {
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);

  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                            Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte };

  // Send the command line to the module
  for (byte k = 0; k < 10; k++) {
    mySerial.write(Command_line[k]);
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
  Serial.print(ebServo.read());
}
