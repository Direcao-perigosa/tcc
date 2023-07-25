#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
#define LED_PIN 2

// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
double gravity = 9.89;
double ax, ay, az;
double gx, gy, gz;
String n = "\n";
String data_hora = "";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -10800; // UTC-3 (three hours behind UTC)
const int daylightOffset_sec = 3600;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec);


//CARTAO MEMORIA
#include "FS.h"
#include "SD.h"
#include "SPI.h"


void setup() {
  Serial.begin(115200);
  WiFi.begin("LIVE TIM_1901_2G", "danivalberlu");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  inicializar_sdcard();
  setup_mpu();
}

void loop() {
    get_hora();
    //colocar leitura do mpu
    get_mpu();
    delay(500);
}
void inicializar_sdcard(){
  
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    
  
  }
void get_mpu(){
   sensors_event_t a, g, temp;
   mpu.getEvent(&a, &g, &temp);
   ax=a.acceleration.x;
   ay=a.acceleration.y;
   az= a.acceleration.z -gravity;
   gx=g.gyro.x;
   gy=g.gyro.y;
   gz=g.gyro.z;

  
  String value =  "";
  value = data_hora+","+String(ax)+","+String(ay)+","+String(az)+","+String(gx)+","+String(gy)+","+String(gz)+n;
  Serial.println(value);
  appendFile(SD, "/dados_tcc.txt",value);
}

void setup_mpu(){
if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

}

void get_hora(){
  timeClient.update();

  // Get Unix timestamp
  unsigned long epochTime = timeClient.getEpochTime();

  // Convert to time struct
  struct tm *timeinfo;
  time_t rawTime = (time_t)epochTime;
  timeinfo = localtime(&rawTime);

  // Extract date and time components
  int day = timeinfo->tm_mday;
  int month = timeinfo->tm_mon + 1; // Months are 0-based
  int year = timeinfo->tm_year + 1900; // Years since 1900
  String formattedTime = timeClient.getFormattedTime();

  // Print date and time (adjusted to local time)
  data_hora="";
  data_hora=data_hora+year+"-";
  if (month < 10){
    data_hora=data_hora+"0";
  }
  data_hora=data_hora+String(month)+"-";
  if (day < 10){
     data_hora=data_hora+"0";
  } 
   data_hora=data_hora+String(day)+" ";
   data_hora=data_hora+formattedTime;
  

}



void appendFile(fs::FS &fs, String path, String message){
    //Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        digitalWrite(LED_PIN, HIGH);
        return;
    }
    if(file.print(message)){
      digitalWrite(LED_PIN, LOW);
      //  Serial.println("Message appended");
    } else {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Append failed");
    }
    file.close();
}

void listDir(fs::FS &fs, String dirname, uint8_t levels){
    //Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
           // Serial.print("  DIR : ");
            //Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
          //  Serial.print("  FILE: ");
          //  Serial.print(file.name());
          //  Serial.print("  SIZE: ");
          //  Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}




