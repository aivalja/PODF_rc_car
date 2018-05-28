
#define LM 9 
#define RM 10
// Direction of movement from bluetooth
#define F  'F'
#define R  'R'
#define L  'L'
#define S  'S'

char incomingByte;
unsigned long currentTime, lastCommandTime, autoOFF;

void setup() {
  Serial.begin(9600);  // Init serial
  pinMode(LM, OUTPUT); // Output to left motor 
  pinMode(RM, OUTPUT); // and right motor
  autoOFF = 500;       // How long the car moves before stopping if no connection
  currentTime = millis();
  lastCommandTime = currentTime;

}

void loop() {
  // These 4 lines are for testing purposes
  controlCar(1, 0); 
  delay(1000);            // wait for a second
  controlCar(0, 1);
  delay(1000);
  
  if (Serial.available() > 0) { // If there is data from bluetooth
    incomingByte = Serial.read();
    controlCar(1, 1);
    delay(10000);
  }
  

  while (Serial.available() > 1) { // clear all but the latest byte
    incomingByte = Serial.read(); // read byte
  }

  if (Serial.available() > 0) { // Read only the latest command
    incomingByte = Serial.read();
  }
  // If no new command, use the last command

  if (millis() - lastCommandTime > autoOFF) { // If too long since last command, stop car
    controlCar(0, 0);
  }
  else if (incomingByte == F) { // Depending on command, set the motor directions
    controlCar(1, 1);
  }
  else if (incomingByte == R) {
    controlCar(1, 0);
  }
  else if (incomingByte == L) {
    controlCar(0, 1);
  }
  else if (incomingByte == S) {
    controlCar(0, 0);
  }

}

// Car/motor control function, arguments are booleans (0 or 1)
void controlCar(int left, int right) {
  digitalWrite(LM, left);
  digitalWrite(RM, right);
}


