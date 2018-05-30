
#define LM 9
#define RM 10
// Direction of movement from bluetooth, forward, right, left, stop
#define F  'F'
#define R  'R'
#define L  'L'
#define S  'S'

char incomingByte;
unsigned long currentTime, lastCommandTime, autoOFF;

void controlCar(int left, int right);

void setup() {
  Serial.begin(9600);  // Init serial
  pinMode(LM, OUTPUT); // Output to left motor
  pinMode(RM, OUTPUT); // and right motor
  autoOFF = 500;       // How long the car moves in ms before stopping if connection fails
  currentTime = millis();
  lastCommandTime = currentTime;
}

void loop() {
  // clear all but the latest byte/command to prevent "backlog"
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    lastCommandTime = millis();
  }

  // If too long since last command, stop car
  if (millis() - lastCommandTime > autoOFF) {
    controlCar(0, 0);
  }
  else {
    // Depending on command, set the motor directions
    switch (incomingByte) {
      case F:
        controlCar(1, 1);
        lastCommandTime = millis();
        break;
      case R:
        controlCar(1, 0);
        lastCommandTime = millis();
        break;
      case L:
        controlCar(0, 1);
        lastCommandTime = millis();
        break;
      case S:
        controlCar(0, 0);
        lastCommandTime = millis();
    }
  }
}

// Car/motor control function, arguments are booleans (0 or 1)
void controlCar(int left, int right) {
  digitalWrite(LM, left);
  digitalWrite(RM, right);
}


