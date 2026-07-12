const int LED = 13;
const int M1 = 4;
const int M2 = 5;
const int M3 = 6;
const int M4 = 7;
const int BTN1 = 3;
const int BTN2 = 2;
const int CONNECTED_GATE = A0;
const int DISCONNECTED_GATE = A1;

enum Direction {
  CONNECT,
  DISCONNECT,
  STOP
};

Direction dir = STOP;

long totalSteps = 0;
unsigned long lastStepReport = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);

  pinMode(CONNECTED_GATE, INPUT);
  pinMode(DISCONNECTED_GATE, INPUT);

  Serial.begin(9600);

  Serial.println("Send \"C\" to connect, \"D\" to disconnect, or \"S\" to stop!");
}

void loop() {

  // ---- Soros port parancsok ----
  if (Serial.available()) {
    char cmd = toupper(Serial.read());

    switch (cmd) {
      case 'C':
        dir = CONNECT;
        Serial.println("CONNECT command received.");
        break;

      case 'D':
        dir = DISCONNECT;
        Serial.println("DISCONNECT command received.");
        break;

      case 'S':
        dir = STOP;
        stop();
        Serial.println("STOP command received.");
        break;
    }
  }

  // ---- Gombok ----
  if (digitalRead(BTN1) == LOW) {
    if (dir != CONNECT)
      dir = CONNECT;
    else {
      dir = STOP;
      stop();
      Serial.println("Manual stop!");
    }

    delay(200); // egyszerű debounce
  }
  else if (digitalRead(BTN2) == LOW) {
    if (dir != DISCONNECT)
      dir = DISCONNECT;
    else {
      dir = STOP;
      stop();
      Serial.println("Manual stop!");
    }

    delay(200); // egyszerű debounce
  }

  bool isConnectedState = analogRead(CONNECTED_GATE) < 100;
  bool isDisconnectedState = analogRead(DISCONNECTED_GATE) < 100;

  // ---- Mozgatás ----
  if (dir == CONNECT && !isConnectedState) {
    moveSteps(10, -1);
    totalSteps += 10;
    reportSteps();
  }
  else if (dir == DISCONNECT && !isDisconnectedState) {
    moveSteps(10, 1);
    totalSteps -= 10;
    reportSteps();
  }
  else if (dir != STOP) {
    dir = STOP;
    stop();
    Serial.println("Target position reached.");
  }
}

void reportSteps() {
  // kb. másodpercenként írjuk ki
  if (millis() - lastStepReport > 5000) {
    Serial.print("Steps moved: ");
    Serial.println(totalSteps);
    lastStepReport = millis();
  }
}