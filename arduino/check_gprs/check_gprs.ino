String response;
bool isModuleOk;

void setup() {
  Serial.begin(9600);
}

void loop() {
try_on:
  if (!isModuleOk) {
    sendCommand("AT\r");
    clearBuffer();
    readData(&response, 200);
    isModuleOk = response.length() > 0 && response.indexOf("OK") > 0;
    if (!isModuleOk)
      goto try_on;
  }

  sendCommand("AT+CGATT=?\r");
  clearBuffer();
  readData(&response, 200);
  Serial.println(response);

  delay(5000);
}

void clearBuffer() {
  while (Serial.available() > 0)
    Serial.read();
}

void sendCommand(String command) {
  clearBuffer();
  Serial.println(command);
}

void readData(String* response, unsigned timeout) {
  unsigned long currentTime = millis();
  *response = "";
  while (currentTime + timeout > millis()) {
    while (Serial.available() > 0) {
      char tmp = Serial.read();
      *response += tmp;
    }
  }
}

