#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
#include <WiFi.h>

#include "ArduinoJson.h"

const char* ssid = "LIVE TIM_1901_2G";
const char* password = "danivalberlu";
const char* host = "http://1a95-34-86-31-23.ngrok-free.app"; // Replace with your server's hostname or IP address
const int port = 80;

MPU6050 accelgyro;
int16_t ax_atual, ay_atual, az_atual;
int16_t gx_atual, gy_atual, gz_atual;

int16_t ax[20], ay[20], az[20];
int16_t gx[20], gy[20], gz[20];

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

    enviar_dados();
}

void loop() {
    accelgyro.getMotion6(&ax_atual, &ay_atual, &az_atual, &gx_atual, &gy_atual, &gz_atual);
    String data = String(ax_atual) + "," + String(ay_atual) + "," + String(az_atual) + "," +
                  String(gx_atual) + "," + String(gy_atual) + "," + String(gz_atual);

    if (cont == 20) {
        enviar_dados();
        for (int i = 0; i < 20; i++) {
            ax[i] = 0;
            ay[i] = 0;
            az[i] = 0;
            gx[i] = 0;
            gy[i] = 0;
            gz[i] = 0;
        }
        cont = 0;
    } else {
        ax[cont] = ax_atual;
        ay[cont] = ay_atual;
        az[cont] = az_atual;
        gx[cont] = gx_atual;
        gy[cont] = gy_atual;
        gz[cont] = gz_atual;
    }
    cont = cont + 1;
    delay(500); // Send data every 0.5 seconds
}

void enviar_dados() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;

        if (client.connect(host, port)) {
            Serial.println("Connected to server");

            // Create a JSON object
            StaticJsonDocument<128> jsonDoc;
            jsonDoc["Teste"] = "Oi";

            // Serialize the JSON object to a string
            String data;
            serializeJson(jsonDoc, data);

            // Send data to the server
            String url = "/teste"; // Replace with the endpoint path on your server
            String request = "POST " + url + " HTTP/1.1\r\n" +
                             "Host: " + host + "\r\n" +
                             "Content-Type: application/json\r\n" +
                             "Content-Length: " + String(data.length()) + "\r\n" +
                             "Connection: close\r\n\r\n" +
                             data;
            Serial.println(request);
            client.print(request);

            // Resto do código...
        } else {
            Serial.println("Connection to server failed");
        }
    } else {
        Serial.println("WiFi disconnected");
    }
}
