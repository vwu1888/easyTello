int numSyncs = 0;
int inputPins[6];
int outputPins[6]

void setup() {
  Serial.begin(19200);

  pinMode(LED_BUILTIN, OUTPUT);
}

void setupPins() {
  numSyncs = waitDrone().toInt();

  for (int i = 0; i < numSyncs; i++) {
    inputPins[i] = 2 + i;
    pinMode(inputPins[i], INPUT);
    outputPins[i] = 8 + i;
    pinMode(outputPins[i], OUTPUT);
  }
}

void loop() {
  String result = waitDrone();

  if (result == "READY") {
    syncUp();
  } else if (result == "FINISH") {
    ready();
    return;
  } else if (result == "START") {
    setupPins();
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

  while (!waitSync()) {}

  Serial.write("SYNCED\n");
  delay(500);
  notReady();
}

void ready() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 0; i < numSyncs; i++) {
    digitalWrite(outputPins[i], HIGH)
  }
}

void notReady() {
  digitalWrite(LED_BUILTIN, LOW);
  for (int i = 0; i < numSyncs; i++) {
    digitalWrite(outputPins[i], LOW)
  }
}

void bool waitSync() {
  for (int i = 0; i < numSyncs; i++) {
    if (digitalRead(inputPins[i]) == LOW) {
      return false;
    }
  }
  return true;
}

String waitDrone() {
  while (Serial.available() == 0) {}

  String result = Serial.readString();
  result.trim();
  Serial.flush();

  return result;
}