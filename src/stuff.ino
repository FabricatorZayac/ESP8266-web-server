#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

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
        server.send(404, "text/html", not_found_html);
    });
    server.begin();
}

void loop(){
    MDNS.update();
    server.handleClient();
}
