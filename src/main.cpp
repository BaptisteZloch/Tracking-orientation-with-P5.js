//Baptiste ZLOCH 09/01/2021
//This project is use a WEMOS D1 R1 with ESP8266 core and an accelerometer MPU6050 using I2C bus

#include <Arduino.h>
#include <Wire.h> //I2C bus
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <math.h>
//#include <FS.h> //old version of LittleFS called SPIFFS but deprecated
#include <LittleFS.h>
#include "myWifi.h" //our own wifi ssid and password header, add your own wifi

Adafruit_MPU6050 mpu;      //accelerometer declaration
AsyncWebServer server(80); //Server declaration on port 80

char *ssid = ssid_devolo;
char *password = password_devolo;

void setup()
{
  //-------------------Serial + I2C--------------------------
  Serial.begin(115200);
  Wire.begin();
  //-------------------Accelerometer--------------------------
  if (!mpu.begin(0x69))
  {
    Serial.println("Error with MPU6050");
    while (1)
    {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("\nMPU6050 successfully initialized !");

  //-------------------Wifi--------------------------
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nIP address = ");
  Serial.println(WiFi.localIP());

  //-------------------Filesystem--------------------------
  if (LittleFS.begin())
  {
    Serial.println(F("LittleFS system mounted with success"));
  }
  else
  {
    Serial.println(F("An Error has occurred while mounting LittleFS"));
  }
  Serial.println("List files :");
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) //print all file name inside the flash
  {
    Serial.println(dir.fileName());
  }
  //-------------------SERVER--------------------------
  //file request
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.on("/p5.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/p5.min.js", "text/javascript");
  });
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(LittleFS, "/script.js", "text/javascript");
  });
  //data request
  server.on("/get_x", HTTP_GET, [](AsyncWebServerRequest *request) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float x = atan(a.acceleration.y / sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.z, 2)));
    String str_x = String(x);
    Serial.print("Sending x :");
    Serial.print(x);
    request->send(200, "text/plain", str_x);
  });
  server.on("/get_y", HTTP_GET, [](AsyncWebServerRequest *request) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float y = atan(-1 * a.acceleration.x / sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2)));
    String str_y = String(y);
    Serial.print("   Sending y :");
    Serial.print(y);
    request->send(200, "text/plain", str_y);
  });
  server.on("/get_z", HTTP_GET, [](AsyncWebServerRequest *request) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float z = atan(a.acceleration.z / sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.z, 2)));
    String str_z = String(z);
    Serial.print("   Sending z :");
    Serial.println(z);
    request->send(200, "text/plain", str_z);
  });
  server.begin();
  Serial.println("Server started !");
}

void loop()
{
}