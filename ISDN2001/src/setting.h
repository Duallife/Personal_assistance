#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <WifiUdp.h>
#include <NTPClient.h>

/*Screen resolution and function*/
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 320;

/*Wifi connection (Wi-Fi5 required) in setup.cpp */
extern const char* ssid;
extern const char* password;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;




