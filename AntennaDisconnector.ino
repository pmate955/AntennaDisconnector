
const int LED = 13;
const int M1 = 4;
const int M2 = 5;
const int M3 = 6;
const int M4 = 7;
const int BTN1 = 2;
const int BTN2 = 3;
const int CONNECTED_GATE = A0;
const int DISCONNECTED_GATE = A1;

enum Direction {
  CONNECT,
  DISCONNECT,
  STOP
};

Direction dir = STOP;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BTN1) == 0)
  //  doSteps(true, 5);
    //moveSteps(10, 1);
    dir = CONNECT;
  else if(digitalRead(BTN2) == 0)
    //moveSteps(10, -1);
    dir = DISCONNECT;
  //else 
    //stop();

  bool isConnectedState = analogRead(CONNECTED_GATE) < 100;
  bool isDisconnectedState = analogRead(DISCONNECTED_GATE) < 100;

  if (dir == CONNECT && !isConnectedState)
    moveSteps(10, 1);
  else if (dir == DISCONNECT && !isDisconnectedState)
    moveSteps(10, -1);
  else if (dir != STOP) {
    dir = STOP;
    stop();
  }
}
