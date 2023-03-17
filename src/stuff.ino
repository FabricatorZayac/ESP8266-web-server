#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "wifi_connect.hpp"
#include "html_embed.hpp"

EMBED_FILE
#include "script.js"

EMBED_FILE
#include "index.css"

EMBED_FILE
#include "index.html"

EMBED_FILE
#include "not_found.html"

ESP8266WebServer server(80);

#define LED 2

void setup() {
    Serial.begin(9600);
    wifi_connect(
#include "wifi.conf"
    );

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    server.enableCORS(true);

    server.on("/", HTTP_GET, [](){
        server.send(200, "text/html", index_html);
    });

    server.on("/hi", HTTP_GET, [](){
        server.send(200,
                    "application/json",
                    "{\"message\": \"Hello world!\"}");
    });

    server.on("/index.css", HTTP_GET, [](){
        server.send(200, "text/css", index_css);
    });

    server.on("/script.js", HTTP_GET, [](){
        server.send(200, "text/javascript", script_js);
    });

    server.on("/led", HTTP_POST, [](){
        digitalWrite(LED, !digitalRead(LED));
        String res = String("{\"led_state\":")
                   + String(digitalRead(LED) ? "false" : "true")
                   + "}";
        server.send(200, "application/json", res);
    });

    server.onNotFound([](){
        server.send(404, "text/html", not_found_html);
    });
    server.begin();
}

void loop(){
    server.handleClient();
}
