#include <stdio.h>

#define GPS_STATE_INDEX       1
#define GPS_LAT_INDEX         3
#define GPS_LONG_INDEX        4
#define GPS_SPEED_INDEX       6
#define GPS_ORIENTATION_INDEX 7

typedef struct {
  bool state;        // Trang thai cua GPS
  String latitude;    // Vi do
  String longitude;   // Kinh do
  float gpsSpeed;    // Toc do GPS
  float orientation; // Huong GPS
} GpsInformation;

bool isModuleOk = false;
bool isGpsAvailable = false;
String response;
GpsInformation gpsInformation = {false, "", "", 0, 0};

void setup() {
  Serial.begin(9600);
}

void loop() {
try_on:
  if (!isModuleOk) {
    // Check if module is ready
    sendCommand("AT\r");
    readData(&response, 200);
    isModuleOk = response.length() > 0 && response.indexOf("OK") > 0;

    // If module is not ok, start over
    if (!isModuleOk)
      goto try_on;
  }

  if (!isGpsAvailable) {
    initGps();

    delay(30000); // Delay 30 seconds to boot gps
  }

try_get_gps:
  // Read gps if it's available
  sendCommand("AT+CGNSINF\r");
  readData(&response, 200);
  if (response.length() > 0)
    Serial.println(response);

  // Split Gps Info
  clearBuffer();
  // Get number of words after splitting the response string
  int numberOfWords = 1;
  for (int i = 0; i < response.length(); i++) {
    if (response[i] == ',')
      numberOfWords++;
  }

  // If there are more than two words, then execute
  if (numberOfWords > 1) {
    String result[numberOfWords];
    split(response, result, ',');
    for (int i = 0; i < numberOfWords; i++) {
      Serial.println(result[i]);
      clearBuffer();
    }

    // Check if gps state is ok (1). If it's not ok, start over from try_get_gps
    if (result[GPS_STATE_INDEX] == "0") {
      delay(5000);
      goto try_get_gps;
    }

    gpsInformation.state = (result[GPS_STATE_INDEX] == "1");
    gpsInformation.latitude = result[GPS_LAT_INDEX];
    gpsInformation.longitude = result[GPS_LONG_INDEX];
    gpsInformation.gpsSpeed = result[GPS_SPEED_INDEX].toFloat();
    gpsInformation.orientation = result[GPS_ORIENTATION_INDEX].toFloat();
    Serial.println(gpsInformation.latitude);
    clearBuffer();
    Serial.println(gpsInformation.longitude);
    clearBuffer();
    Serial.println(gpsInformation.gpsSpeed);
    clearBuffer();
    Serial.println(gpsInformation.orientation);
  }

  // Wait for 5 seconds
  delay(5000);
}

void initGps() {
try_gps:
  sendCommand("AT+CGNSPWR=1\r");
  readData(&response, 200);
  isGpsAvailable = response.length() > 0 && response.indexOf("OK") > 0;

  // If gps is not available, start over
  if (!isGpsAvailable)
    goto try_gps;
}

void sendCommand(String command) {
  clearBuffer();
  Serial.println(command);
}

void readData(String* response, const unsigned int timeout) {
  unsigned long currentTime = millis();
  bool isFirst = true;
  *response = "";

  while ((currentTime + timeout) > millis()) {
    while (Serial.available() > 0) {
      char c = Serial.read();

      if (c == '\r' && isFirst) {
        isFirst = false;
        *response = "";
      } else {
        *response += c;
      }
    }
  }
}

// Clear serial buffer to eliminate old data
void clearBuffer() {
  while (Serial.available() > 0) {
    Serial.read();
  }
}

void split(String data, String result[], char separators) {
  String tmp = "";
  unsigned short i = 0;
  for (unsigned short j = 0; j < data.length(); j++) {
    if (data[j] == separators) {
      result[i] = tmp;
      tmp = ""; // Reset found word
      i++;
    } else {
      tmp += data[j];
    }
  }
}

