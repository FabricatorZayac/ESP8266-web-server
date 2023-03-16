#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "wifi_connect.h"

// clang-format off
// HTML stuffs
#include "html_begin.pp"
#include "index.html"

#include "html_begin.pp"
#include "index.css"

#include "html_begin.pp"
#include "script.js"

#include "html_begin.pp"
#include "404.html"

#include "html_end.pp"
//clang-format

ESP8266WebServer server(80);

void setup() {
    Serial.begin(9600);
    wifi_connect(
#include "wifi.conf"
            );

    html_page.replace("$(STYLE)", css);
    not_found_page.replace("$(STYLE)", css);
    html_page.replace("$(MAIN_SCRIPT)", main_js);
    html_page.replace("$(LOCAL_IP)", WiFi.localIP().toString());

    server.enableCORS(true);

    server.on("/", HTTP_GET, [](){
        server.send(200, "text/html", html_page);
    });

    server.on("/hi", HTTP_GET, [](){
        server.send(200,
                    "application/json",
                    "{\"message\": \"Hello world!\"}");
    });

    server.onNotFound([](){
        server.send(404, "text/html", not_found_page);
    });
    server.begin();
}

void loop(){
    server.handleClient();
}
