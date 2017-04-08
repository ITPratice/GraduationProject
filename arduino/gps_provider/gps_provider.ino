#include <stdio.h>

#define NO_RESPONSE 0
#define SUCCESS     1
#define FAIL        2
#define RESPONSE_MAX_LENGTH 300
#define GPS_SEPARATE_CHAR ','

#define INDEX_GPS_STATE 1
#define INDEX_GPS_LATITUDE 3
#define INDEX_GPS_LONGITUDE 4

typedef struct {
  bool state;
  String latitude;
  String longitude;
} GpsInformation;

int powerKey = 9;
String response = "";
bool isGpsAvailable;
bool isArduinoOn;
bool isGprsOpened;
GpsInformation gpsInfo = {false, "", ""};

void setup() {
  pinMode(powerKey, OUTPUT);
  Serial.begin(9600);
  powerOn();
  delay(1000);

  setupModule();
  delay(1000);

  //  openGprs();
  initGps();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void powerOn() {
  isArduinoOn = !isArduinoOn;
  if (sendATCommandWithoutResponse("AT", "OK", "OK", 2000) == NO_RESPONSE) {
    digitalWrite(powerKey, HIGH);
    delay(1000);
    digitalWrite(powerKey, LOW);
  }
}

void setupModule() {
check_module:
  if (sendATCommandWithoutResponse("AT", "OK", "OK", 500) != SUCCESS)
    goto check_module;

  // Turn off echo mode to prevent module send back the at command
  while (sendATCommandWithoutResponse("ATE0", "OK", "ERROR", 500) != SUCCESS) {
    delay(500);
  }
}

void openGprs() {
  // Attach Gprs
  if (sendATCommandWithoutResponse("AT+CGATT?", "1", "0", 500) != SUCCESS) {
    sendATCommandWithoutResponse("AT+CGATT=1", "OK", "", 500);
  }

  // Select single connection mode
  if (sendATCommandWithoutResponse("AT+CIPMUX=0", "OK", "ERROR", 1000) != SUCCESS)
    return;
  // Set APN
  while (sendATCommandWithoutResponse("AT+CSTT=\"v-internet\"", "OK", "ERROR", 10000) != SUCCESS);
  // Bring up wireless connection
  if (sendATCommandWithoutResponse("AT+CIICR", "OK", "ERROR", 30000) == SUCCESS) {
    // Get local IP address
    if (sendATCommandWithoutResponse("AT+CIFSR", ".", "ERROR", 10000) == SUCCESS) {
      isGprsOpened = true;
    }
  }
}

void initGps() {
  // open gps
  while (sendATCommandWithoutResponse("AT+CGNSPWR=1", "OK", "OK", 200) != SUCCESS);
  delay(5000);
try_gps:
  if (sendATCommandWithResponse("AT+CGNSINF", &response, "OK", "OK", 500) != SUCCESS) {
    delay(20000);
    goto try_gps;
  }
  getGpsInfo(&gpsInfo, response);
  if (!gpsInfo.state) {
    delay(20000);
    goto try_gps;
  }
  Serial.println(gpsInfo.latitude);
  Serial.println(gpsInfo.longitude);
}

void split(String source, String dest[], char seperateCharacter) {
  int j = 0;
  for (int i = 0; i < source.length(); i++) {
    char tmp = source.charAt(i);
    if (tmp != seperateCharacter) {
      dest[j] += tmp;
    } else {
      j++;
    }
  }
}

void getGpsInfo(GpsInformation *gpsInfo, String data) {
  int count = 0;
  for (int i = 0; i < data.length(); i++) {
    if (data.charAt(i) == ',')
      count++;
  }

  if (count == 0) {
    gpsInfo->state = false;
    gpsInfo->latitude = "";
    gpsInfo->longitude = "";
  }
  else {
    String info[count + 1] ;
    split(data, info, ',');
    gpsInfo->state = info[INDEX_GPS_STATE].compareTo("1") == 0;
    gpsInfo->latitude = info[INDEX_GPS_LATITUDE];
    gpsInfo->longitude = info[INDEX_GPS_LONGITUDE];
  }
}

int8_t sendATCommandWithoutResponse(String atCommand, String successExpectedResponse,
                                    String failExpectedResponse, unsigned int timeout) {
  uint8_t answer = NO_RESPONSE;
  unsigned long previousTime;
  String response = "";

  // Clean the input buffer
  while (Serial.available() > 0)
    Serial.read();

  // Send the at command;
  Serial.println(atCommand);

  // Read the response
  previousTime = millis();
  do {
    if (Serial.available() > 0) {
      response += (char)Serial.read();

      if (response.indexOf(successExpectedResponse) >= 0) {
        answer = SUCCESS;
      } else if (response.indexOf(failExpectedResponse) >= 0) {
        answer = FAIL;
      }
    }
  } while ((answer == NO_RESPONSE) && ((millis() - previousTime) < timeout));

  Serial.println(response);
  return answer;
}

int8_t sendATCommandWithResponse(String atCommand, String *response, String successExpectedResponse,
                                 String failExpectedResponse, unsigned int timeout) {
  uint8_t answer = NO_RESPONSE;
  unsigned long previousTime;
  *response = "";

  // Clean the input buffer
  while (Serial.available() > 0)
    Serial.read();

  // Send the at command;
  Serial.println(atCommand);

  // Read the response
  previousTime = millis();
  do {
    if (Serial.available() > 0) {
      (*response) += (char)Serial.read();

      if ((*response).indexOf(successExpectedResponse) >= 0) {
        answer = SUCCESS;
      } else if ((*response).indexOf(failExpectedResponse) >= 0) {
        answer = FAIL;
      }
    }
  } while ((answer == NO_RESPONSE) && ((millis() - previousTime) < timeout));

  Serial.println(*response);
  return answer;
}

