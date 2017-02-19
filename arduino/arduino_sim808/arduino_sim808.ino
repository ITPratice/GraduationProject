int powerPin = 9;
char data[300];

void setup() {
  Serial.begin(9600);

  pinMode(powerPin, OUTPUT);
  powerUp();

  initGps();
}

void loop() {
  sendData("AT+CGNSINF", 1000);
}

// Turn on the module
void powerUp() {
  digitalWrite(powerPin, LOW);
  delay(1000);
  digitalWrite(powerPin, HIGH);
}

// Check if module Sim808 is ready or not
bool isReady() {
  Serial.write("AT\r");
  delay(1000);
  Serial.println((char)Serial.read());
}

int readSerialData(char* data, unsigned int timeout) {
  unsigned long previousTime, currentTime;
  int i = 0;

  // Init time
  previousTime = currentTime = millis();

  // Read the received data
  while (1) {
    if (currentTime - previousTime >= timeout)
      return i;
    else {
      if (Serial.available() > 0) {
        previousTime = currentTime;
        data[i] = (char)Serial.read();
        i++;
      }
      currentTime = millis();
    }
  }
}

void sendData(String command, const unsigned int timeout) {
  String response = "";

  Serial.println(command);
  unsigned long startTime = millis();
  while ((startTime + timeout) > millis()) {
    while (Serial.available() > 0) {
      char c = Serial.read();
      response += c;
    }
  }

  if (response.length() > 0)
    Serial.print("This is response: " + response);
}

void initGps() {
  sendData("AT+CGNSPWR=1", 1000);
}

bool isStringEmpty(char* data) {
  return data[0] == '\0';
}

