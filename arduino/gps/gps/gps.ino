/* SIM808
    D9     < - >     PWK
 */
 
// RMC
#define GPS_RSTS                0
#define GPS_FSTS                1
#define GPS_TIME                2
#define GPS_LAT                 3
#define GPS_LON                 4
#define GPS_MSL                 5
#define GPS_SPEED               6
#define GPS_ORG                 7
 
/*!< cau truc du lieu thoi gian */
typedef union
{
struct
{
unsigned int year;
unsigned char month;
unsigned char date;
unsigned char hour;
unsigned char minute;
unsigned char sec;
}time;
}SysTime;
 
/*!< cau truc du lieu GPS */
typedef struct{       
bool State_gps;      /*!< trang thai gps 1 = co tin hieu, 0 = mat tin hieu */
SysTime time_gps;    /*!< time gps  */
float Lat;           /*!< vi do */
float Lng;           /*!< kinh do */
float SpeedGPS;      /*!< Toc do GPS */
float OrGPS;         /*!< Huong GPS 360 do */
}GPS_T;                  
 
/*!< So dien thoai can nhan tin               */
int phone_number_to_send = "01696698882"; 
/*!< Chan dieu khien Bat/Tat Module Sim808    */
int PWK_PIN  =  9;     
/*!< Chan canh bao tin hieu dau vao           */
int BUTTON_PIN = 8;
 
GPS_T g_gps_data = {false, 0, 0, 0, 0};
 
 
void setup() {
  Serial.begin(9600);
  pinMode(PWK_PIN, OUTPUT);
  digitalWrite(PWK_PIN, HIGH);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
}
 
char respond[300];
  
void loop() {
  static unsigned long previousMillis; 
  unsigned long currentMillis;
   
  ModemInit();
   
  // Update GPS data
  Serial.write("AT+CGNSINF\r");
  delay(1000);
  if(readSerialFrame(respond) > 0)
  {
    if(strncmp(respond, "\r\n+CGNSINF: ", 12) == 0)
    {
      NMEA_GPRMC_Decoder(&g_gps_data, respond + 12);
    }
  }
  // Kiem tra co tin hieu canh cao hay khong
  int sensorVal = digitalRead(BUTTON_PIN);
  if(sensorVal == LOW)
  {
    char data_to_send_sms[160];
    char tmp_str1[20], tmp_str2[20];
     
    // Gui tin nhan bao cao toa do
    dtostrf(g_gps_data.Lat, 10, 6, tmp_str1);
    dtostrf(g_gps_data.Lng, 10, 6, tmp_str2);
    sprintf(data_to_send_sms, "https://maps.google.com/maps?q=%s,%s", tmp_str1, tmp_str2);
    SendSMS(phone_number_to_send, data_to_send_sms);
           
    // Gui tin nhan bao cao thoi gian
    //      sprintf(data_to_send_sms, "TIME %04d/%02d/%02d  %02d:%02d:%02d"  , g_gps_data.time_gps.time.year  \
    //                        , g_gps_data.time_gps.time.month  \
    //                        , g_gps_data.time_gps.time.date \
    //                        , g_gps_data.time_gps.time.hour   \
    //                        , g_gps_data.time_gps.time.minute   \
    //                        , g_gps_data.time_gps.time.sec);
    //      SendSMS(phone_number_to_send, data_to_send_sms);
     
    // Gui tin nhan bao cao van toc
    //      dtostrf(g_gps_data.SpeedGPS, 5, 2, tmp_str1);
    //      dtostrf(g_gps_data.OrGPS, 5, 2, tmp_str2);    
    //      sprintf(data_to_send_sms, "SPEED = %s (km/h)   ORG = %s",tmp_str1, tmp_str2);
    //      SendSMS(phone_number_to_send, data_to_send_sms);
  }
}
 
/*
  Read input serial
 */
int readSerial(char result[], int time_out) {
  int i = 0;
  unsigned long currentMillis, previousMillis;
  previousMillis = millis();
  currentMillis = previousMillis;
  while (1) {
    if (currentMillis - previousMillis >= time_out) 
    {
      return 0;
    }
    else
    {
      while (Serial.available() > 0) {
        char inChar = Serial.read();
        if (inChar == '\r') {
          result[i] = '\0';
          Serial.flush();
          return i;
        }
        if (inChar != '*') {
          result[i] = inChar;
          i++;
        }
      }
    }
    currentMillis = millis();
  }
}
 
bool SendSMS(char *phone_num, char *data)
{
  unsigned long currentMillis, previousMillis;
  char sms_cmd[50];
  char respond[30];
  char command_en[2] = {0x1A, 0};
       
  sprintf(sms_cmd,"AT+CMGS=\"%s\"\r",phone_num);
  Serial.write(sms_cmd);
  if(readSerialFrame(respond) > 0)
  {
    if(strcmp(respond, "\r\n>") != 0)
    {
      Serial.write(data);
    }
  }
  Serial.write(command_en);
  previousMillis = millis();
  currentMillis = previousMillis;
  while(currentMillis - previousMillis < 5000)      // timeout 5s
  {
    currentMillis = millis();
    if(readSerialFrame(respond) > 0)
    {
      if(strcmp(respond, "\r\nOK\r\n") != 0)
      {
    return true;
    }
    }
  }
  return false;
}
 
void ModemInit(void)
{
  static bool is_modem_init_ok = false;
 // Turn on modem:
  if(is_modem_init_ok == false)
  {
    try_on:
    digitalWrite(PWK_PIN, HIGH); // 
    delay(2000);
    digitalWrite(PWK_PIN, LOW);
    delay(2000);
    digitalWrite(PWK_PIN, HIGH); 
    delay(5000);
  
    Serial.write("ATE0\r"); // turn off the echo mode
    delay(1000);
    if(readSerialFrame(respond) > 0)
    {
      if(strstr(respond,"\r\nOK\r\n") == NULL)
      {
        goto try_on;
      }
    }
    else
    {
      goto try_on;
    }
 
    Serial.write("AT+CMGF=1\r"); // turn on text mode of sms
    delay(1000);
    if(readSerialFrame(respond) > 0)
    {
      if(strstr(respond,"\r\nOK\r\n") == NULL)
      {
        goto try_on;
      }
    }
    else
    {
      goto try_on;
    }
 
    Serial.write("AT+CGNSPWR=1\r"); // Turn GPS on
    delay(1000);
    if(readSerialFrame(respond) > 0)
    {
      if(strstr(respond,"\r\nOK\r\n") == NULL)
      {
        goto try_on;
      }
    }
    else
    {
      goto try_on;
    }
 
    Serial.write("AT+CGNSSEQ=\"RMC\"\r");
    delay(1000);
    if(readSerialFrame(respond) > 0)
    {
      if(strstr(respond,"\r\nOK\r\n") == NULL)
      {
        goto try_on;
      }
    }
    else
    {
      goto try_on;
    }
    
    Serial.write("AT+CMGF=1\r"); 
    delay(1000);
    if(readSerialFrame(respond) > 0)
    {
      if(strstr(respond,"\r\nOK\r\n") == NULL)
      {
        goto try_on;
      }
    }
    else
    {
      goto try_on;
    }
    
    Serial.write("AT+CNMI=2,2,0,0,0\r");
    delay(1000);
    if(readSerialFrame(respond) > 0)
    {
      if(strstr(respond,"\r\nOK\r\n") == NULL)
      {
        goto try_on;
      }
    }
    else
    {
      goto try_on;
    }
    is_modem_init_ok = true;
    delay(2000);
  }
}
 
int readSerialFrame(char result[]) {
  int i = 0;
  unsigned long currentMillis, previousMillis;
  previousMillis = millis();
  currentMillis = previousMillis;
  while (1) {
    if (currentMillis - previousMillis >= 200) 
    {
      return i;
    }
    else
    {
      if (Serial.available() > 0) {
        previousMillis = currentMillis;
        char inChar = Serial.read();
        result[i] = inChar;
        modemSerial.write(result[i]);
        i++;
        result[i] = 0;  
      }
    }
    currentMillis = millis();
  }
}
 
 
static int GetMessageFeilds(unsigned char **message_feildls, unsigned char *msg, unsigned char separate_char, int max_feild_get)
{
  int count_feild = 0;
  *message_feildls = msg;
  message_feildls++;
  count_feild++;
  while(*msg !='\0')
  {
    if(*msg == separate_char)
    {
      *msg = '\0';
      *message_feildls = msg + 1;
      message_feildls++;
      count_feild++;
      if(count_feild >= max_feild_get)
        return count_feild;
    }
    msg++;
  }
  return count_feild;
}
 
 
 
static void NMEA_GPRMC_Decoder(GPS_T *gps_data, char *data_bytes)
{
  //Get data
  char *message_field[13];
  if(GetMessageFeilds(message_field, data_bytes, ',', 13) == 13)
  {    
      if(strcmp(message_field[GPS_FSTS], "1") == 0)
      {
        gps_data->State_gps = true;
        gps_data->State_gps = true;
        
        gps_data->SpeedGPS = atof(message_field[GPS_SPEED]);
        gps_data->OrGPS = atof(message_field[GPS_ORG]);
        gps_data->Lat = atof(message_field[GPS_LAT]);
        gps_data->Lng = atof(message_field[GPS_LON]); 
      }
      else
      {
        gps_data->State_gps = false;
        
        gps_data->Lat = 0;
        gps_data->Lng = 0;
        gps_data->SpeedGPS = 0;
      }
    
      gps_data->time_gps.time.sec = message_field[GPS_TIME][13] - '0'  + 10*(message_field[GPS_TIME][12] - '0');
      gps_data->time_gps.time.minute = message_field[GPS_TIME][11] - '0'  + 10*(message_field[GPS_TIME][10] - '0');
      gps_data->time_gps.time.hour = message_field[GPS_TIME][9] - '0'  + 10*(message_field[GPS_TIME][8] - '0');
    
      gps_data->time_gps.time.date = message_field[GPS_TIME][7] - '0'  + 10*(message_field[GPS_TIME][6] - '0');
      gps_data->time_gps.time.month = message_field[GPS_TIME][5] - '0'  + 10*(message_field[GPS_TIME][4] - '0');
      gps_data->time_gps.time.year = message_field[GPS_TIME][3] - '0'  + 10*(message_field[GPS_TIME][2] - '0') + 100*(message_field[GPS_TIME][1] - '0') + 1000*(message_field[GPS_TIME][0] - '0');
    
  }
}
