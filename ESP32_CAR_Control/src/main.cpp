#include "start_ap.hpp"
#include "fs_init.hpp"
#include "http.hpp"

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  delay(3000);

  Serial.println("Start FS");
  FS_init();
  Serial.println("Start WIFI");
  //Запускаем WIFI
  StartAPMode();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start WebServer");
  HTTP_init();

}

void loop()
{
  HTTP.handleClient();
}