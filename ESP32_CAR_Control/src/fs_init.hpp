#include "env.hpp"

void handleFileList();
bool handleFileRead(String path);
void handleFileCreate();
void handleFileDelete();
void handleFileUpload();

//format bytes
String formatBytes(size_t bytes) {
    if (bytes < 1024) {
      return String(bytes) + "B";
    } else if (bytes < (1024 * 1024)) {
      return String(bytes / 1024.0) + "KB";
    } else if (bytes < (1024 * 1024 * 1024)) {
      return String(bytes / 1024.0 / 1024.0) + "MB";
    } else {
      return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
    }
  }
  
  // Инициализация FFS
  void FS_init(void) {
    FILESYSTEM.begin();
    {
        File root = FILESYSTEM.open("/");
        File file = root.openNextFile();
        while(file){
            String fileName = file.name();
            size_t fileSize = file.size();
            Serial.print("FS File: ");Serial.println(fileName);
            file = root.openNextFile();
        }
    }
  
    //list directory
    HTTP.on("/list", HTTP_GET, handleFileList);
    //load editor
    HTTP.on("/edit", HTTP_GET, []() {
      if (!handleFileRead("/edit.htm")) {
        HTTP.send(404, "text/plain", "FileNotFound");
      }
    });
    
    //create file
    HTTP.on("/edit", HTTP_PUT, handleFileCreate);
    //delete file
    HTTP.on("/editt", HTTP_DELETE, handleFileDelete);
    //first callback is called after the request has ended with all parsed arguments
    //second callback handles file uploads at that location
    HTTP.on("/edit", HTTP_POST, []() {
      HTTP.send(200, "text/plain", "");
    }, handleFileUpload);
    //called when the url is not defined here
    //use it to load content from FILESYSTEM
    HTTP.onNotFound([]() {
      if (!handleFileRead(HTTP.uri())) {
        HTTP.send(404, "text/plain", "NotFound");
      }
    });
  }
  
  // ------------------------------------------------------------------ Здесь функции для работы с файловой системой
  
  String getContentType(String filename) {
    if (HTTP.hasArg("download")) {
      return "application/octet-stream";
    } else if (filename.endsWith(".htm")) {
      return "text/html";
    } else if (filename.endsWith(".html")) {
      return "text/html";
    } else if (filename.endsWith(".css")) {
      return "text/css";
    } else if (filename.endsWith(".js")) {
      return "application/javascript";
    } else if (filename.endsWith(".png")) {
      return "image/png";
    } else if (filename.endsWith(".gif")) {
      return "image/gif";
    } else if (filename.endsWith(".jpg")) {
      return "image/jpeg";
    } else if (filename.endsWith(".ico")) {
      return "image/x-icon";
    } else if (filename.endsWith(".xml")) {
      return "text/xml";
    } else if (filename.endsWith(".pdf")) {
      return "application/x-pdf";
    } else if (filename.endsWith(".zip")) {
      return "application/x-zip";
    } else if (filename.endsWith(".gz")) {
      return "application/x-gzip";
    }
    return "text/plain";
  }
  
  bool exists(String path){
    bool yes = false;
    File file = FILESYSTEM.open(path, "r");
    if(!file.isDirectory()){
      yes = true;
    }
    file.close();
    return yes;
  }
  
  bool handleFileRead(String path) {
    Serial.println("handleFileRead: " + path);
    if (path.endsWith("/")) {
      path += "index.htm";
    }
    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";
    if (exists(pathWithGz) || exists(path)) {
      if (exists(pathWithGz)) {
        path += ".gz";
      }
      File file = FILESYSTEM.open(path, "r");
      HTTP.streamFile(file, contentType);
      file.close();
      return true;
    }
    return false;
  }
  
  void handleFileUpload() {
    if (HTTP.uri() != "/edit") {
      return;
    }
    HTTPUpload& upload = HTTP.upload();
    if (upload.status == UPLOAD_FILE_START) {
      String filename = upload.filename;
      if (!filename.startsWith("/")) {
        filename = "/" + filename;
      }
      Serial.print("handleFileUpload Name: "); Serial.println(filename);
      fsUploadFile = FILESYSTEM.open(filename, "w");
      filename = String();
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      //Serial.print("handleFileUpload Data: "); Serial.println(upload.currentSize);
      if (fsUploadFile) {
        fsUploadFile.write(upload.buf, upload.currentSize);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (fsUploadFile) {
        fsUploadFile.close();
      }
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
    }
  }
  
  void handleFileDelete() {
    if (HTTP.args() == 0) {
      return HTTP.send(500, "text/plain", "BAD ARGS");
    }
    String path = HTTP.arg(0);
    Serial.println("handleFileDelete: " + path);
    if (path == "/") {
      return HTTP.send(500, "text/plain", "BAD PATH");
    }
    if (!exists(path)) {
      return HTTP.send(404, "text/plain", "FileNotFound");
    }
    FILESYSTEM.remove(path);
    HTTP.send(200, "text/plain", "");
    path = String();
  }
  
  void handleFileCreate() {
    if (HTTP.args() == 0) {
      return HTTP.send(500, "text/plain", "BAD ARGS");
    }
    String path = HTTP.arg(0);
    Serial.println("handleFileCreate: " + path);
    if (path == "/") {
      return HTTP.send(500, "text/plain", "BAD PATH");
    }
    if (exists(path)) {
      return HTTP.send(500, "text/plain", "FILE EXISTS");
    }
    File file = FILESYSTEM.open(path, "w");
    if (file) {
      file.close();
    } else {
      return HTTP.send(500, "text/plain", "CREATE FAILED");
    }
    HTTP.send(200, "text/plain", "");
    path = String();
  }
  
  void handleFileList() {
    if (!HTTP.hasArg("dir")) {
      HTTP.send(500, "text/plain", "BAD ARGS");
      return;
    }
  
    String path = HTTP.arg("dir");
    Serial.println("handleFileList: " + path);
  
  
    File root = FILESYSTEM.open(path);
    path = String();
  
    String output = "[";
    if(root.isDirectory()){
        File file = root.openNextFile();
        while(file){
            if (output != "[") {
              output += ',';
            }
            output += "{\"type\":\"";
            output += (file.isDirectory()) ? "dir" : "file";
            output += "\",\"name\":\"";
            output += String(file.name()).substring(1);
            output += "\"}";
            file = root.openNextFile();
        }
    }
    output += "]";
    HTTP.send(200, "text/json", output);
  }