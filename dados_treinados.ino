#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
#include <WiFi.h>

#include "ArduinoJson.h"

const char* ssid = "LIVE TIM_1901_2G";
const char* password = "danivalberlu";
const char* host = "5acf-35-194-216-133.ngrok-free.app"; // Replace with your server's hostname or IP address
const int port = 80;

MPU6050 accelgyro;
int16_t ax_atual, ay_atual, az_atual;
int16_t gx_atual, gy_atual, gz_atual;

double ax[20], ay[20], az[20];
double gx[20], gy[20], gz[20];

int cont = 0;

void setup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    Serial.begin(38400);
    delay(2000);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");

    accelgyro.initialize();
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
 
        for (int i = 0; i < 20; i++) {
            ax[i] = 0.123456;
            ay[i] = -0.789012;
            az[i] = 0.345678;
            gx[i] = -0.901234;
            gy[i] = -0.567890;
            gz[i] = 0.123456;
        }
     
 enviar_dados();
}

void loop() {
    accelgyro.getMotion6(&ax_atual, &ay_atual, &az_atual, &gx_atual, &gy_atual, &gz_atual);
    String data = String(ax_atual) + "," + String(ay_atual) + "," + String(az_atual) + "," +
                  String(gx_atual) + "," + String(gy_atual) + "," + String(gz_atual);

       
       
       /* for (int i = 0; i < 20; i++) {
            ax[i] = 0;
            ay[i] = 0;
            az[i] = 0;
            gx[i] = 0;
            gy[i] = 0;
            gz[i] = 0;
        }*/ 
    delay(5000); // Send data every 0.5 seconds
}
void enviar_dados() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;

        if (client.connect(host, port)) {
            // Create a JSON array
            StaticJsonDocument<1024> jsonDoc;
            JsonArray dataArray = jsonDoc.to<JsonArray>();

            // Add elements to the JSON array
            for (int i = 0; i < 20; i++) {
                JsonObject dataObj = dataArray.createNestedObject();
                dataObj["AccX"] = ax[i];
                dataObj["AccY"] = ay[i];
                dataObj["AccZ"] = az[i];
                dataObj["GyroX"] = gx[i];
                dataObj["GyroY"] = gy[i];
                dataObj["GyroZ"] = gz[i];
            }

            // Serialize the JSON array to a string
            String data;
            serializeJson(dataArray, data);
            Serial.println(data);

            // Send data to the server
            String url = "/get_data"; // Replace with the endpoint path on your server
            String request = "POST " + url + " HTTP/1.0\r\n" +
                 "Host: " + host + "\r\n" +
                 "Content-Type: application/json\r\n" +
                 "Content-Length: " + String(data.length()) + "\r\n" +
                 "\r\n" +
                 data;
            client.print(request);

             // Read and print the server's response
          while (client.connected() || client.available()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
        // The empty line after headers indicates the start of the response body
        break;
    }
}

// Now, read and print the rest of the response (the response body)
while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
}

// Close the connection
client.stop();

            // Rest of the code...
        } else {
            Serial.println("Connection to server failed");
        }
    } else {
        Serial.println("WiFi disconnected");
    }
}
