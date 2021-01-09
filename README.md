# Tracking-orientation-wih-P5.js
This project allow you to track the orientation of a device and to display it in real time on a web page.

Orientation is captured by a MPU6050 accelerometer with WEMOS D1 R1. Then these data are sent into the web page using http requests and p5.js draw the box that follows the real time orientation of your device.

All web page files such index.htmm, script.js, p5.js are stored into the flash of the WEMOS D1 R1 we access to it using littleFS (same as SPIFFS). The page is served using  ESPAsyncWebServer.h library.
