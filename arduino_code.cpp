// ========== PIN DEFINITIONS ==========
int ENA = 5;
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int ENB = 6;
int RELAY = 7;
int sensorFL = 2;
int sensorFR = 3;
int sensorBL = 4;
int sensorBR = 12;

// ========== SPEED SETTINGS ==========
int motorSpeed = 150;
int turnSpeed  = 255;

// ========== CALIBRATION ==========
int startupMoveTime = 1500;
int reverseTime     = 800;
int turn180TimeCW   = 3350;  
int turn180TimeCCW  = 3400; 
int rowShiftTime    = 600;

// ========== STATE MACHINE ==========
#define STARTUP        0
#define MOVE_FORWARD   1
#define REVERSING      2
#define TURN_CW        3
#define TURN_CCW       4
#define ROW_SHIFT      5
#define DONE           6

int state     = STARTUP;
int turnCount = 0;

// ========== SETUP ==========
void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(sensorFL, INPUT);
  pinMode(sensorFR, INPUT);
  pinMode(sensorBL, INPUT);
  pinMode(sensorBR, INPUT);

  Serial.begin(9600);
  Serial.println("==================");
  Serial.println("  Robot Starting  ");
  Serial.println("==================");

  digitalWrite(RELAY, LOW);
  Serial.println("Brush ON");

  delay(1000);
}

// ========== MOVEMENT FUNCTIONS ==========
void moveForward() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Left FORWARD + Right BACKWARD = Clockwise sharp turn
void spinCW() {
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Left BACKWARD + Right FORWARD = Anticlockwise sharp turn
void spinCCW() {
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ========== MAIN LOOP ==========
void loop() {

  int FL = digitalRead(sensorFL);
  int FR = digitalRead(sensorFR);
  int BL = digitalRead(sensorBL);
  int BR = digitalRead(sensorBR);

  Serial.print("State:"); Serial.print(state);
  Serial.print(" | Turn#:"); Serial.print(turnCount);
  Serial.print(" | FL:"); Serial.print(FL);
  Serial.print(" FR:"); Serial.print(FR);
  Serial.print(" BL:"); Serial.print(BL);
  Serial.print(" BR:"); Serial.println(BR);

  switch (state) {

    // ===== STATE 0: STARTUP =====
    case STARTUP:
      Serial.println(">> STARTUP: Moving forward blindly...");
      moveForward();
      delay(startupMoveTime);
      stopMotors();
      delay(500);
      Serial.println(">> STARTUP done. Sensors enabled.");
      state = MOVE_FORWARD;
      break;

    // ===== STATE 1: MOVE FORWARD =====
    case MOVE_FORWARD:

      if (FL == 1 && FR == 1) {
        stopMotors();
        delay(300);
        Serial.println(">> EDGE detected! Reversing...");
        state = REVERSING;
      }
      else if (BL == 1 || BR == 1) {
        stopMotors();
        delay(100);
        moveForward();
        delay(400);
        stopMotors();
      }
      else {
        moveForward();
      }
      break;

    // ===== STATE 2: REVERSING =====
    case REVERSING:
      Serial.println(">> REVERSING away from edge...");
      moveBackward();
      delay(reverseTime);
      stopMotors();
      delay(400);

      if (turnCount % 2 == 0) {
        Serial.println(">> Next: CLOCKWISE turn");
        state = TURN_CW;
      } else {
        Serial.println(">> Next: ANTICLOCKWISE turn");
        state = TURN_CCW;
      }
      turnCount++;
      break;

    // ===== STATE 3: CLOCKWISE 180 =====
    case TURN_CW:
      Serial.println(">> SPINNING Clockwise 180...");
      spinCW();
      delay(turn180TimeCW);  // 3700ms
      stopMotors();
      delay(400);
      Serial.println(">> CW turn done.");
      state = ROW_SHIFT;
      break;

    // ===== STATE 4: ANTICLOCKWISE 180 =====
    case TURN_CCW:
      Serial.println(">> SPINNING Anticlockwise 180...");
      spinCCW();
      delay(turn180TimeCCW);  // 3450ms
      stopMotors();
      delay(400);
      Serial.println(">> CCW turn done.");
      state = ROW_SHIFT;
      break;

    // ===== STATE 5: ROW SHIFT =====
    case ROW_SHIFT:
      Serial.println(">> ROW SHIFT: Moving to next row...");
      moveForward();
      delay(rowShiftTime);
      stopMotors();
      delay(400);

      if (digitalRead(sensorBL) == 1 || digitalRead(sensorBR) == 1) {
        Serial.println(">> No more rows.");
        state = DONE;
      } else {
        Serial.println(">> New row. Resuming.");
        state = MOVE_FORWARD;
      }
      break;

    // ===== STATE 6: DONE =====
    case DONE:
      stopMotors();
      digitalWrite(RELAY, HIGH);
      Serial.println("==============================");
      Serial.println("   Cleaning Complete!");
      Serial.println("   Robot Stopped.");
      Serial.println("==============================");
      delay(5000);
      break;
  }

  delay(100);
}
