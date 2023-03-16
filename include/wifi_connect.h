#ifndef WIFI_CONNECT_H_
#define WIFI_CONNECT_H_

#include <ESP8266WiFi.h>

void wifi_connect(const char *ssid, const char *pass) {
    Serial.println('\n');
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to ");
    Serial.print(ssid); Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(++i); Serial.print('.');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

#endif // !DEBUG
