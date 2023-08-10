#include <WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "LIVE TIM_1901_2G";
const char* password = "danivalberlu";

const char* serverAddress = "2fcb-104-196-19-194.ngrok-free.app";
const int serverPort = 80;
const String endpoint = "/teste"; // Change this to the appropriate endpoint on your server

const int numSamples = 20;
float samples[numSamples][6]; // 6 values per sample (x, y, z for acceleration and inclination)
int sampleCount = 0;

void setup() {
  Serial.begin(9600);
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize samples array
  for (int i = 0; i < numSamples; i++) {
    for (int j = 0; j < 6; j++) {
      samples[i][j] = 0.0;
    }
  }
}

void loop() {
  // Simulate collecting data (replace with your actual data collection code)
  float accelerationX = random(0, 10);
  float accelerationY = random(0, 10);
  float accelerationZ = random(0, 10);
  
  float inclinationX = random(-45, 45);
  float inclinationY = random(-45, 45);
  float inclinationZ = random(-45, 45);
  
  // Store data in samples array
  samples[sampleCount][0] = accelerationX;
  samples[sampleCount][1] = accelerationY;
  samples[sampleCount][2] = accelerationZ;
  samples[sampleCount][3] = inclinationX;
  samples[sampleCount][4] = inclinationY;
  samples[sampleCount][5] = inclinationZ;
  
  sampleCount++;

  if (sampleCount >= numSamples) {
    for(int i =0;i<numSamples;i++){
      Serial.println(samples[i][0]);
      Serial.println(samples[i][1]);
      Serial.println(samples[i][2]);
      Serial.println(samples[i][3]);
      Serial.println(samples[i][4]);
      Serial.println(samples[i][5]);
    }
    // tudo ok aqui
    sendDataToServer();
    sampleCount = 0;
  }

  delay(500); // Wait for 0.5 seconds before collecting next sample
}
void sendDataToServer() {
  WiFiClient client;

  if (client.connect(serverAddress, serverPort)) {
    DynamicJsonDocument jsonDoc(4096); // Adjust the size as needed

    for (int i = 0; i < numSamples; i++) {
      Serial.println("oi");
      JsonObject sampleObj = jsonDoc.createNestedObject();
      sampleObj["AccX"] = samples[i][0];
      sampleObj["AccY"] = samples[i][1];
      sampleObj["AccZ"] = samples[i][2];
      sampleObj["GyroX"] = samples[i][3];
      sampleObj["GyroY"] = samples[i][4];
      sampleObj["GyroZ"] = samples[i][5];
    }

   
    Serial.println("Serialized JSON document:");
    serializeJsonPretty(jsonDoc, Serial);

     String payload;
    serializeJson(jsonDoc, payload);

    client.println("POST " + endpoint + " HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(payload.length()));
    client.println();
    client.println(payload);

    Serial.println("Data sent to server");

    // Read and print the response from the server
    while (client.connected()) {
      if (client.available()) {
        Serial.write(client.read());
      }
    }

    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }

  delay(5000000);
}
