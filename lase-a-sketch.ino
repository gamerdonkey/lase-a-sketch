#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define X_ENCODER_A_PIN     2
#define X_ENCODER_B_PIN     3

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Y_ENCODER_A_PIN    18
#define Y_ENCODER_B_PIN    19

#define FORWARD          HIGH
#define REVERSE           LOW
#define STEP_DELAY       1000
#define STEPS_PER_MOVE     2

int desiredPosition[] = { 0, 0 };
int currentPosition[] = { 0, 0 };

void setup() {
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(X_ENCODER_A_PIN, INPUT);
  pinMode(X_ENCODER_B_PIN, INPUT);
  pinMode(Y_ENCODER_A_PIN, INPUT);
  pinMode(Y_ENCODER_B_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(X_ENCODER_A_PIN), xEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(X_ENCODER_B_PIN), xEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Y_ENCODER_A_PIN), yEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Y_ENCODER_B_PIN), yEncoderB, CHANGE);
  
  delay(3000);
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
}

void loop() {
  if(currentPosition[0] < desiredPosition[0]) {
    stepMotor(X_STEP_PIN, STEPS_PER_MOVE, X_DIR_PIN, FORWARD);
    currentPosition[0] = currentPosition[0] + 1;
  }
  else if(currentPosition[0] > desiredPosition[0]) {
    stepMotor(X_STEP_PIN, STEPS_PER_MOVE, X_DIR_PIN, REVERSE);
    currentPosition[0] = currentPosition[0] - 1;
  }
  else if(currentPosition[1] < desiredPosition[1]) {
    stepMotor(Y_STEP_PIN, STEPS_PER_MOVE, Y_DIR_PIN, FORWARD);
    currentPosition[1] = currentPosition[1] + 1;
  }
  else if(currentPosition[1] > desiredPosition[1]) {
    stepMotor(Y_STEP_PIN, STEPS_PER_MOVE, Y_DIR_PIN, REVERSE);
    currentPosition[1] = currentPosition[1] - 1;
  }
  
}

void stepMotor(int stepPin, int steps, int dirPin, int dir) {
  digitalWrite(dirPin, dir);
  
  digitalWrite(LED_BUILTIN, HIGH);
  
  for(int i = 0; i < steps; i++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(STEP_DELAY);
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void doEncoder(int aPin, int bPin, int& pos) {
  if(digitalRead(aPin) == HIGH) {
    if(digitalRead(bPin) == LOW) {
      pos = constrain(pos + 1, 0, 100);
    }
    else {
      pos = constrain(pos - 1, 0, 100);
    }
  }
  else {
    if(digitalRead(bPin) == HIGH) {
      pos = constrain(pos + 1, 0, 100);
    }
    else {
      pos = constrain(pos - 1, 0, 100);
    }
  }
}

void xEncoderA() {
  doEncoder(X_ENCODER_A_PIN, X_ENCODER_B_PIN, desiredPosition[0]);
}

void xEncoderB() {
  doEncoder(X_ENCODER_B_PIN, X_ENCODER_A_PIN, desiredPosition[0]);
}

void yEncoderA() {
  doEncoder(Y_ENCODER_A_PIN, Y_ENCODER_B_PIN, desiredPosition[1]);
}

void yEncoderB() {
  doEncoder(Y_ENCODER_B_PIN, Y_ENCODER_A_PIN, desiredPosition[1]);
}


