int led = 2;
int button = 11;
int time1 = 0;

bool isMoving;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(button) == HIGH) {
    if ((unsigned long)(millis() - time1) >= 1000) {
      if (isMoving) {
        isMoving = false;
        digitalWrite(led, LOW);
      } else {
        isMoving = true;
        digitalWrite(led, HIGH);
      }
      time1 = millis();
      Serial.println(isMoving);
    }
  }
}

