#include <stdio.h>

#define NO_RESPONSE 0
#define SUCCESS     1
#define FAIL        2
#define RESPONSE_MAX_LENGTH 300
#define GPS_SEPARATE_CHAR ','

#define INDEX_GPS_STATE 1
#define INDEX_GPS_LATITUDE 3
#define INDEX_GPS_LONGITUDE 4

#define LICENSE_PLATE "29F1-11023"

#define DEBUG false

typedef struct {
  bool state;
  String latitude;
  String longitude;
} GpsInformation;

typedef struct {
  String currentDate;
  String currentTime;
} DateTime;

int powerKey = 9;

unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;

String response = "";
String baseUrl = "http://52.221.199.175:3000/api/";
String hardwareId = "1";
String startTime = "";
bool isGpsAvailable;
bool isArduinoOn;
bool isGprsOpened;
bool isMoving;
GpsInformation gpsInfo = {false, "", ""};
DateTime dateTime = {"", ""};

void setup() {
  pinMode(powerKey, OUTPUT);

  Serial.begin(9600);
  powerOn();
  delay(1000);

  setupModule();
  delay(1000);

  initGps();

  delay(5000);
}

void loop() {
  if (isGpsAvailable) {
    // Get gps information
    if (sendATCommandWithResponse("AT+CGNSINF", &response, "OK", "OK", 5000) != SUCCESS) {
      return;
    }
    getGpsInfo(&gpsInfo, response);

    isGpsAvailable = gpsInfo.state;

    // If gps is not available then return
    if (!isGpsAvailable) {
      delay(10000);
      return;
    }

    while (!isGprsAvailable()) {
      openGprs();
    }

    sendData();

    delay(2000);
  } else {
    if (sendATCommandWithResponse("AT+CGNSINF", &response, "OK", "OK", 5000) != SUCCESS) {
      delay(10000);
      return;
    }

    getGpsInfo(&gpsInfo, response);
    isGpsAvailable = gpsInfo.state;
    if (!isGpsAvailable) {
      delay(10000);
      return;
    }
  }
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

void initGps() {
  // open gps
try_gps:
  while (sendATCommandWithoutResponse("AT+CGNSPWR=1", "OK", "OK", 2000) != SUCCESS);
  delay(2000);
  if (sendATCommandWithResponse("AT+CGNSINF", &response, "OK", "OK", 2000) != SUCCESS) {
    delay(20000);
    goto try_gps;
  }
  getGpsInfo(&gpsInfo, response);
  isGpsAvailable = gpsInfo.state;
  if (!isGpsAvailable) {
    delay(20000);
    goto try_gps;
  }
}

void openGprs() {
  // Attach Gprs
  if (sendATCommandWithoutResponse("AT+CGATT?", "1", "0", 1000) != SUCCESS) {
    sendATCommandWithoutResponse("AT+CGATT=1", "OK", "", 1000);
  }

  while (sendATCommandWithoutResponse("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", "OK", "ERROR", 1000) != SUCCESS) {
    delay(1000);
  }
  delay(1000);

  // Set APN
  while (sendATCommandWithoutResponse("AT+SAPBR=3,1,\"APN\",\"v-internet\"", "OK", "ERROR", 10000) != SUCCESS);
  delay(2000);

  while (sendATCommandWithoutResponse("AT+SAPBR=1,1", "OK", "ERROR", 30000) != SUCCESS);
  delay(1000);
}

bool isGprsAvailable() {
  sendATCommandWithResponse("AT+SAPBR=2,1", &response, "OK", "ERROR", 5000);
  return !(response.indexOf("0.0.0.0") >= 0);
}

void sendData() {
  getCurrentDateTime(&dateTime);
  delay(2000);

  while (!isGprsAvailable()) {
    openGprs();
  }

  if (isMoving) {
    if (startTime == "")
      startTime = dateTime.currentTime;
  } else {
    startTime = "";
  }

  sendATCommandWithoutResponse("AT+HTTPINIT", "OK", "ERROR", 10000);

  String command = "AT+HTTPPARA=\"URL\",\"" + baseUrl + "arduino/location?";

  command += "lat=" + gpsInfo.latitude + "&lon=" + gpsInfo.longitude + "&plate=" + LICENSE_PLATE;

  if (dateTime.currentDate.length() == 0) {
    command += "&date=\"\"";
  } else {
    command += "&date=" + dateTime.currentDate;
  }

  if (startTime == "")
    command += "&start=\"";
  else
    command += "&start=" + startTime + "\"";

  sendATCommandWithoutResponse(command, "OK", "ERROR", 10000);

  // Set http action. Type: 0=GET, 1=POST, 2=HEAD
  sendATCommandWithoutResponse("AT+HTTPACTION=0", "OK", "ERROR", 1000);

  delay(2000);

  // Read data
  sendATCommandWithoutResponse("AT+HTTPREAD", "SUCCESS", "ERROR", 2000);

  // Terminate http
  sendATCommandWithoutResponse("AT+HTTPTERM", "OK", "ERROR", 1000);
  //  while (sendATCommandWithoutResponse("AT+SAPBR=0,1", "OK", "ERROR", 1000) != SUCCESS);
}

void split(String source, String dest[], char seperateCharacter) {
  int j = 0;
  for (int i = 0; i < source.length(); i++) {
    char tmp = source.charAt(i);
    if (tmp != seperateCharacter) {
      if (tmp != '\r')
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

void getCurrentDateTime(DateTime *dateTime) {
  if (sendATCommandWithoutResponse("AT+HTTPINIT", "OK", "ERROR", 1000) == SUCCESS) {

    String command;

    command = "AT+HTTPPARA=\"URL\",\"" + baseUrl + "time?plate=" + LICENSE_PLATE + "\"";
    sendATCommandWithoutResponse(command, "OK", "ERROR", 5000);

    command = "AT+HTTPACTION=0";
    sendATCommandWithoutResponse(command, "OK", "ERROR", 1000);

    delay(5000);

    sendATCommandWithResponse("AT+HTTPREAD", &response, "OK", "OK", 10000);

    String tmp = "";
    int count = 0;

    for (int i = 0; i < response.length(); i++) {
      if (response[i] == '\r') {
        if (count == 2)
          break;
        count++;
        tmp = "";
      } else {
        if (response[i] != '\n')
          tmp += response[i];
      }
    }

    count = 0;
    for (int i = 0; i < tmp.length(); i++) {
      if (tmp.charAt(i) == ' ')
        count++;
    }

    if (count != 0) {
      String info[count + 1];
      split(tmp, info, ' ');
      dateTime->currentDate = info[0];
      dateTime->currentTime = info[1];
      isMoving = info[2] == "1";
    }

    sendATCommandWithoutResponse("AT+HTTPTERM", "OK", "ERROR", 5000);
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

  if (DEBUG)
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

  if (DEBUG)
    Serial.println(*response);
  return answer;
}

