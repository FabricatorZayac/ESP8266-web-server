#ifndef WIFI_CONNECT_H_
#define WIFI_CONNECT_H_

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void wifi_connect(const char *ssid, const char *pass) {
    Serial.println('\n');
    wifiMulti.addAP(ssid, pass);

    Serial.print("Connecting to ");
    Serial.print(ssid); Serial.println(" ...");

    int i = 0;
    while (wifiMulti.run() != WL_CONNECTED) {
        delay(1000);
        Serial.print(++i); Serial.print('.');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

#endif // !DEBUG
