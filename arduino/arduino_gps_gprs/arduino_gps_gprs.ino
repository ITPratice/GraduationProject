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
  char *latitude;
  char *longitude;
} GpsInformation;

int powerKey = 9;
char response[RESPONSE_MAX_LENGTH];
uint8_t answer;
bool isGpsAvailable;
GpsInformation gpsInfo = {false, "", ""};

void setup() {
  pinMode(powerKey, OUTPUT);
  Serial.begin(9600);
  powerOn();
  // Check if the module is working or not
check_module:
  answer = NO_RESPONSE;
  answer = sendAtCommand("AT", response, "OK", "OK", 200);
  if (answer == NO_RESPONSE)
    goto check_module;
  // Activate gps
  else {
    initGps();
    delay(30000);
  }
}

void loop() {
  //  Do task when gps is available
  if (isGpsAvailable) {
    answer = sendAtCommand("AT+CGNSINF", response, "OK", "OK", 500);
    if (answer == SUCCESS) {
      getGpsInfo(response, &gpsInfo, ',');
      if (gpsInfo.state) {
        activateGPRS();
      }
    }
  }
  delay(10000);
}

void powerOn() {
  uint8_t answer = NO_RESPONSE;
  sendAtCommand("AT", response, "OK", "OK", 2000);
  if (answer == NO_RESPONSE) {
    digitalWrite(powerKey, HIGH);
    delay(1000);
    digitalWrite(powerKey, LOW);
  }
}

int8_t sendAtCommand(char *atCommand, char *response, char* successExpectedResponse,
                     char *failExpectedResponse, unsigned int timeout) {
  uint8_t x = 0, answer = NO_RESPONSE;
  unsigned long previousTime;

  memset(response, '\0', RESPONSE_MAX_LENGTH);  // Initialize the string
  delay (100);

  // Clean the input buffer
  while (Serial.available() > 0)
    Serial.read();

  // Send the at command
  Serial.println(atCommand);

  previousTime = millis();

  // Wait for response
  do {
    if (Serial.available() != 0) {
      response[x] = Serial.read();
      x++;

      // Remove the output that is similar to the at command
      if (strstr(response, atCommand) != NULL) {
        memset(response, '\0', RESPONSE_MAX_LENGTH);
        x = 0;
      }
      // Check if the desired success response is in the response fo the module
      else if (strstr(response, successExpectedResponse) != NULL)
        answer = SUCCESS;
      // Check if the desired fail response is in the response fo the module
      else if (strstr(response, failExpectedResponse) != NULL)
        answer = FAIL;
    }
  } while ((answer == NO_RESPONSE) && ((millis() - previousTime) < timeout));

  Serial.println(response);

  return answer;
}

int8_t sendAtCommandWithoutResponse(char *atCommand, char* successExpectedResponse,
                                    char *failExpectedResponse, unsigned int timeout) {
  uint8_t x = 0, answer = NO_RESPONSE;
  unsigned long previousTime;
  char response[100];

  memset(response, '\0', 100);  // Initialize the string
  delay (100);

  // Clean the input buffer
  while (Serial.available() > 0)
    Serial.read();

  // Send the at command
  Serial.println(atCommand);

  previousTime = millis();

  // Wait for response
  do {
    if (Serial.available() != 0) {
      response[x] = Serial.read();
      x++;

      // Check if the desired success response is in the response fo the module
      if (strstr(response, successExpectedResponse) != NULL)
        answer = SUCCESS;
      // Check if the desired fail response is in the response fo the module
      else if (strstr(response, failExpectedResponse) != NULL)
        answer = FAIL;
    }
  } while ((answer == NO_RESPONSE) && ((millis() - previousTime) < timeout));

  return answer;
}

void initGps() {
init_gps:
  answer = NO_RESPONSE;
  answer = sendAtCommand("AT+CGNSPWR=1", response, "OK", "OK", 200);
  if (answer != SUCCESS)
    goto init_gps;
  else {
    delay(10000);
    // Check if the gps works stably
try_gps:
    answer = sendAtCommand("AT+CGNSINF", response, "OK", "OK", 500);
    if (answer == NO_RESPONSE) {
      delay(30000);
      goto try_gps;
    } else {
      getGpsInfo(response, &gpsInfo, ',');
      if (gpsInfo.state) {
        isGpsAvailable = true;
      }
      else {
        isGpsAvailable = false;
        delay(30000);
        goto try_gps;
      }
    }
  }
}

int split(unsigned char **fields, char *source, unsigned char separateCharacter, int maxField) {
  int count = 0;
  *fields = source;
  fields++;
  count++;
  while (*source != '\0') {
    if (*source == separateCharacter) {
      *source = '\0';
      *fields = source + 1;
      fields++;
      count++;
      if (count >= maxField)
        return count;
    }
    source++;
  }
  return count;
}

void getGpsInfo(char *source, GpsInformation * gpsInfo, char separateCharacter) {
  char *fields[13];

  if (split(fields, source, ',', 13) == 13) {
    if (strcmp(fields[INDEX_GPS_STATE], "1") == 0) {
      gpsInfo->state = true;
      gpsInfo->latitude = fields[INDEX_GPS_LATITUDE];
      gpsInfo->longitude = fields[INDEX_GPS_LONGITUDE];
    } else {
      gpsInfo->state = false;
      gpsInfo->latitude = "0";
      gpsInfo->longitude = "0";
    }
  }
}

void activateGPRS() {
  // Attach GPRS
  if (sendAtCommand("AT+CGATT?", response, "1", "0", 500) != SUCCESS) {
    sendAtCommand("AT+CGATT=1", response, "OK", "", 500);
  }
  sendDataToServer();
}

void sendDataToServer() {
  sendAtCommand("AT+CSTT=\"CMNET\"", response, "OK", "ERROR", 10000);

  // Bring up wireless connection
  if (sendAtCommand("AT+CIICR", response, "OK", "ERROR", 30000) == SUCCESS) {
    // Get local IP address
    if (sendAtCommand("AT+CIFSR", response, ".", "ERROR", 10000) == SUCCESS) {
      // Open a TCP socket
      if (sendAtCommand("AT+CIPSTART=\"TCP\",\"54.179.174.237\",\"3000\"", response, "CONNECT OK", "CONNECT FAIL", 30000) == SUCCESS) {
        // Making data to send
        char *dataToSend = (char*) malloc(1 + strlen(gpsInfo.latitude) + strlen(gpsInfo.longitude) + 1);
        strcpy(dataToSend, gpsInfo.latitude);
        strcat(dataToSend, "#");
        strcat(dataToSend, gpsInfo.longitude);

        // Send data
        char *command;
        sprintf(command, "AT+CIPSEND=%d", strlen(dataToSend));
        if (sendAtCommandWithoutResponse(command, ">", "ERROR", 10000) == SUCCESS) {
          sendAtCommandWithoutResponse(dataToSend, "SEND OK", "ERROR", 10000);
        }

        // Close socket
        sendAtCommandWithoutResponse("AT+CIPCLOSE", "CLOSE OK", "ERROR", 10000);
      }
    }
  }
}
