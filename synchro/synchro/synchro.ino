const int synchroOne = 2;
const int synchroTwo = 3;
const int outputOne = 10;
const int outputTwo = 11;

bool isReady = false;
bool hasResponse = false;

void setup() {
  Serial.begin(19200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(synchroOne, INPUT);
  pinMode(synchroTwo, INPUT);
  pinMode(outputOne, OUTPUT);
  pinMode(outputTwo, OUTPUT);
  
}

void loop() {
  String result = waitDrone();

  if (result == "READY") {
    syncUp();
  } else if (result == "FINISH") {
    ready();
  } else if (result == "START") {
    notReady();
  } else if (result == "UNSYNC") {
    ready();
  } else if (result == "RESYNC") {
    notReady();
  } else {
    notReady();
  }
}

bool syncUp() {
  ready();

  while (digitalRead(synchroOne) == LOW || digitalRead(synchroTwo) == LOW) {}

  Serial.write("SYNCED\n");
  delay(500);
  notReady();
}

void ready() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(outputOne, HIGH);
  digitalWrite(outputTwo, HIGH);
}

void notReady() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(outputOne, LOW);
  digitalWrite(outputTwo, LOW);
}

String waitDrone() {
  while (Serial.available() == 0) {}

  String result = Serial.readString();
  result.trim();
  Serial.flush();

  return result;
}