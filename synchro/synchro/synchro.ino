const int synchroOne = 2;
const int synchroTwo = 3;
const int outputOne = 10;
const int outputTwo = 11;

bool isReady = false;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(synchroOne, INPUT);
  pinMode(synchroTwo, INPUT);
  pinMode(outputOne, OUTPUT);
  pinMode(outputTwo, OUTPUT);
}

void loop() {
  if (isReady) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(outputOne, HIGH);  
    digitalWrite(outputTwo, HIGH);  
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(outputOne, LOW);  
    digitalWrite(outputTwo, LOW);  
    isReady = waitDrone();
  }

  if (isReady, digitalRead(synchroOne), digitalRead(synchroTwo)) {
    Serial.write("SYNCED");
    isReady = false;
  }
}

bool waitDrone() {
  while(Serial.available() == 0) {}

  String result = Serial.readString();
  result.trim();
  Serial.flush();

  return result == "READY";
}
