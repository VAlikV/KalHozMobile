#include "env.hpp"
#include "motors.hpp"

void handle_Restart();
void handle_settings();
void handle_speeding();

void HTTP_init(void) {
    HTTP.on("/restart", handle_Restart); // Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
    HTTP.on("/settings", handle_settings);
    HTTP.on("/speed", handle_speeding);
    // Запускаем HTTP сервер
    HTTP.begin();
  
  }

// Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
void handle_Restart() {
  String restart = HTTP.arg("device");
  if (restart == "ok") ESP.restart();
  HTTP.send(200, "text/plain", "OK");
}

void handle_settings(){
  String st = HTTP.arg("status");
  if (st == "1") {
    digitalWrite(LED_BUILTIN, HIGH);
    HTTP.send(200, "text/plain", "______________On");
  }
  if (st == "0") {
    digitalWrite(LED_BUILTIN, LOW);
    HTTP.send(200, "text/plain", "________________Off");
  }
}

void handle_speeding(){
  String st = HTTP.arg("vel");
  speed_left = st.substring(0, st.indexOf("=")).toInt();
  dir_left = (speed_left >= 0);

  speed_right = st.substring(st.indexOf("=")+1, st.length()).toInt();
  dir_right = (speed_right >= 0);

  motors();

  Serial.print(dir_left);Serial.print(" ");Serial.println(speed_left);
  Serial.print(dir_right);Serial.print(" ");Serial.println(speed_right);
  Serial.println(" ");

  HTTP.send(200, "text/plain", "OK");
}