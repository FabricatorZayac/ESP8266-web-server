#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>

#include "wifi_connect.hpp"

struct MyServer : public ESP8266WebServer {
    MyServer(int port) : ESP8266WebServer(port) {};
    void sendFile(String content_type, String path) {
        File file = LittleFS.open(path, "r");
        this->streamFile(file, content_type);
        file.close();
    }
};

String getContentType(String filename){
    if(filename.endsWith(".htm")) return "text/html";
    else if(filename.endsWith(".html")) return "text/html";
    else if(filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "text/javascript";
    else if(filename.endsWith(".png")) return "image/png";
    else if(filename.endsWith(".gif")) return "image/gif";
    else if(filename.endsWith(".jpg")) return "image/jpeg";
    else if(filename.endsWith(".ico")) return "image/x-icon";
    else if(filename.endsWith(".xml")) return "text/xml";
    else if(filename.endsWith(".pdf")) return "application/x-pdf";
    else if(filename.endsWith(".zip")) return "application/x-zip";
    else if(filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}

MyServer server(80);

#define LED 2

void setup() {
    Serial.begin(115200);
    wifi_connect(
#include "wifi.conf"
    );

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    if (!MDNS.begin("esp8266")) {
        Serial.println("Error setting up MDNS responder!");
    }
    Serial.println("mDNS responder started");
    MDNS.addService("http", "tcp", 80);

    server.enableCORS(true);
    LittleFS.begin();

    server.on("/hi", HTTP_GET, [](){
        server.send(200,
                    "application/json",
                    "{\"message\": \"Hello world!\"}");
    });

    server.on("/led", HTTP_GET, [](){
        String res = String("{\"led_state\":")
                   + String(digitalRead(LED) ? "false" : "true")
                   + "}";
        server.send(200, "application/json", res);
    });

    server.on("/led", HTTP_POST, [](){
        String body = server.arg("plain");
        Serial.println(body);
        if (body == "on") digitalWrite(LED, LOW);
        if (body == "off") digitalWrite(LED, HIGH);
        server.send(200);
    });

    server.onNotFound([](){
        String path = server.uri();
        if (path == "/") path += "index.html";
        if (LittleFS.exists(path)) {
            server.sendFile(getContentType(path), path);
        }
        server.sendFile("text/html", "/not_found.html");
    });
    server.begin();
}

void loop(){
    MDNS.update();
    server.handleClient();
}
