#ifndef ENV
#define ENV

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#define FILESYSTEM SPIFFS

#if FILESYSTEM == FFat
#include <FFat.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif

IPAddress apIP(192, 168, 2, 3);

String _ssidAP = "KalHozMobile";   // SSID AP точки доступа
String _passwordAP = "12345678";  // пароль точки доступа


// Web интерфейс для устройства
WebServer HTTP(80);
// Для файловой системы
File fsUploadFile;

int speed_left = 0;
int speed_right = 0;

bool dir_left = true;
bool dir_right = true;

#endif