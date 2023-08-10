#include <WiFi.h>
#include <ArduinoJson.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float gravity = 9.89;
float ax, ay, az;
float gx, gy, gz;

float fix_ax,fix_ay,fix_az, fix_gx,fix_gy=0;
float fix_gz = gravity;


const char* ssid = "LIVE TIM_1901_2G";
const char* password = "danivalberlu";
const char* serverAddress = "5e29-35-225-43-53.ngrok-free.app";
const int serverPort = 80;
const String endpoint = "/get_data"; // Change this to the appropriate endpoint on your server

const int numSamples = 20;
float samples[6]; // 6 values per sample (x, y, z for acceleration and inclination)
int sampleCount = 0;
float accelerationX =0;
  float accelerationY = 0;
  float accelerationZ =0;
  
  float inclinationX =0;
  float inclinationY = 0;
  float inclinationZ =0;

const int PINO_LED = 12;
const int PINO_LED_GND = 14;
void setup() {
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_LED_GND, OUTPUT);

  Serial.begin(9600);
  delay(100);
  setup_mpu();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  get_mpu();
  // Initialize samples array
  for (int i = 0; i < 6; i++) {
      samples[i] = 0.0;

  }
  for(int i =0;i<20;i++){
      get_mpu();
      fix_ax = (ax+(i*fix_ax))/(i+1);
      fix_ay = (ay+(i*fix_ay))/(i+1);
      fix_az = (az+(i*fix_az))/(i+1);
      fix_gx = (gx+(i*fix_gx))/(i+1);
      fix_gy = (gy+(i*fix_gy))/(i+1);
      fix_gz=(gz+(i*fix_gz))/(i+1);
  }
  if(fix_ax == -0.00){
    fix_ax =0;
  }
  if(fix_ay == -0.00){
    fix_ay=0;
  }
  if(fix_az == -0.00){
    fix_az=0;
  }
  if(fix_gx == -0.00){
    fix_gx=0;
  }
  if(fix_gy == -0.00){
    fix_gy=0;
  }
  if(fix_gz == -0.00){
    fix_gz=0;
  }
Serial.println("Fix"+String(fix_ax)+","+String(fix_ay)+","+String(fix_az)+","+String(fix_gx)+","+String(fix_gy)+","+String(fix_gz));
delay(3000);

get_mpu();
   accelerationX =ax;
   accelerationY = ay;
   accelerationZ = az;
  
   inclinationX = gx;
   inclinationY = gy;
   inclinationZ = gz;
  const int threshold = 0.5; // Adjust this threshold value as needed

  while((abs(accelerationX) >= threshold) && abs((accelerationY) >= threshold)  && (abs(accelerationZ) >= threshold)  && (abs(inclinationX) >= threshold) && (abs(inclinationY) >= threshold) && (abs(inclinationZ)>= threshold) ){
      get_mpu();
      accelerationX =ax;
      accelerationY = ay;
      accelerationZ = az;
      inclinationX = gx;
      inclinationY = gy;
      inclinationZ = gz;

  }
  Serial.println("Carro começou a se movimentar");
  

}

int cont =0;
void loop() {
  // Simulate collecting data (replace with your actual data collection code)
  get_mpu();
  
  // Store data in samples array

  samples[0] = ax;
  samples[1] = ay;
  samples[2] = az;
  samples[3] = gx;
  samples[4] = gy;
  samples[5] = gz;
  String resultado = sendDataToServer();
  Serial.println("."+resultado+".");
  if(resultado == "NORMAL"){
      digitalWrite(PINO_LED_GND, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(PINO_LED, LOW);   // turn the LED on (HIGH is the voltage level)

  }else{
    if(resultado=="AGGRESSIVE"){
      digitalWrite(PINO_LED_GND, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(PINO_LED, HIGH);   // turn the LED on (HIGH is the voltage level)

    }
  }
  delay(500); // Wait for 0.5 seconds before collecting next sample
}
String sendDataToServer() {
  WiFiClient client;
  String result;
  if (client.connect(serverAddress, serverPort)) {
    DynamicJsonDocument jsonDoc(4096);

    JsonObject sampleObj = jsonDoc.createNestedObject();
    sampleObj["AccX"] = samples[0];
    sampleObj["AccY"] = samples[1];
    sampleObj["AccZ"] = samples[2];
    sampleObj["GyroX"] = samples[3];
    sampleObj["GyroY"] = samples[4];
    sampleObj["GyroZ"] = samples[5];

    String payload;
    serializeJson(jsonDoc, payload);

    client.println("POST " + endpoint + " HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(payload.length()));
    client.println();
    client.println(payload);


    unsigned long timeout = millis(); // Get the current time

    // Read and print the response from the server



      while (client.connected() && millis() - timeout < 1000) { // Read for up to 5 seconds
    if (client.available()) {
      char c = client.read();
      //Serial.write(c);

      // Collect the characters until a closing curly brace is encountered
      if (c == '}') {
        result += c; // Include the closing curly brace in the result
        break; // Exit the loop
      }
      result += c; // Append characters to the result
    }
  }
  // Serial.println("..."+result+"...");
  String result_corrected =result.substring(218, result.length()-3);
  // Parse the JSON response
  
  return result_corrected;
}




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
  get_mpu();
  delay(2000);
}


void get_mpu(){
   sensors_event_t a, g, temp;
   mpu.getEvent(&a, &g, &temp);
   ax=a.acceleration.x-fix_ax;
   ay=a.acceleration.y-fix_ay;
   az= a.acceleration.z -gravity-fix_az;
   gx=g.gyro.x-fix_gx;
   gy=g.gyro.y-fix_gy;
   gz=g.gyro.z-fix_gz;

  
  String value =  "";
  value = String(ax)+","+String(ay)+","+String(az)+","+String(gx)+","+String(gy)+","+String(gz);
}
