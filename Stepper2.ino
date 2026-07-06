// Egy lépés végrehajtása
const int steps[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int stepIndex = 0;
int stepDelay = 2;

void stepMotor(int direction) {
  stepIndex += direction;

  if (stepIndex > 7) stepIndex = 0;
  if (stepIndex < 0) stepIndex = 7;

  digitalWrite(M1, steps[stepIndex][0]);
  digitalWrite(M2, steps[stepIndex][1]);
  digitalWrite(M3, steps[stepIndex][2]);
  digitalWrite(M4, steps[stepIndex][3]);

  delayMicroseconds(1500);
}

// Több lépés végrehajtása
void moveSteps(int numberOfSteps, int direction) {
  for (int i = 0; i < numberOfSteps; i++) {
    stepMotor(direction);
  }
}

void stop() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
}