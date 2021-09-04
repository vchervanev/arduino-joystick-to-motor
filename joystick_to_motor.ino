//const int SW = ; // Joystick's digital switch - unused
const int DX = 0; // Joystick's analog DX
//const int DY = 1; // Joystick's analog DY - unused

const int SPEED = 5;
const int DIRECTION_A = 3;
const int DIRECTION_B = 4;

const bool CLOCKWISE = true;
bool currentDirection = !CLOCKWISE;

void setDirection(bool target) {
  if (target != currentDirection) {
    currentDirection = target;
    if (currentDirection) {
      digitalWrite(DIRECTION_A, HIGH);
      digitalWrite(DIRECTION_B, LOW);
    } else {
      digitalWrite(DIRECTION_A, LOW);
      digitalWrite(DIRECTION_B, HIGH);
    }
  }
}

void stopMotor() {
  analogWrite(SPEED, 0);
}

void setup() {
  pinMode(DX, INPUT);
  pinMode(SPEED,OUTPUT);
  pinMode(DIRECTION_A,OUTPUT);
  pinMode(DIRECTION_B,OUTPUT);

  setDirection(CLOCKWISE);
}

void setSpeed(int speed) {
  analogWrite(SPEED, min(255, speed));
}

void loop() {
  int dx = analogRead(DX);  
  int speed = abs(dx - 512)/2; // ~ 0..256
  bool clockwise = dx > 512;

  if (speed < 10) {
    stopMotor();
  } else {
    setDirection(clockwise);
    setSpeed(speed);
  }
}
