#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

#define PORT 8000
#define SSID "wifi_name"
#define PASSWORD "wifi_password"
#define FILE "files/index.html"

typedef enum {
    LOCKED,
    UNLOCKED
} DOOR_STATE;

DOOR_STATE status = LOCKED;

WebServer server(PORT);

void __UNLOCK_DOOR() {
    if (status == UNLOCKED) {
        Serial.printf("[?] Door's already unlocked!\n");
        return;
    }
    Serial.printf("[$] Unlocked the door\n");
    status = UNLOCKED;
    // gpio set pin 5 HIGH
    server.send(200, "application/json", "{\"status\": \"unlocked\"}");
}

void __LOCK_DOOR() {
    if (status == LOCKED) {
        Serial.printf("[?] Door's already locked!\n");
        return;
    }
    Serial.printf("[$] Locking the door!\n");
    status = LOCKED;
    // gpio set pin 5 LOW
    server.send(200, "application/json", "{\"status\": \"locked\"}");
}

void __ROOT() {
    File file = SPIFFS.open(FILE, "r");
    if (!file) {
        server.send(404, "application/json", "File Not Found");
        return;
    }

    server.streamFile(file, "text/html");
    file.close();
}

void setup() {
    Serial.begin(9600);

    WiFi.begin(SSID, PASSWORD);
    Serial.printf("[$] Connecting to wifi ");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); Serial.printf(".");
    }

    Serial.printf("\n[$] Connected to wifi\n");

    if (!SPIFFS.begin()) {
        Serial.printf("[!] Err%d: Mount failed!\n", __LINE__);
        return;
    }

    server.on("/", HTTP_GET, __ROOT);
    server.on("/api/unlock", HTTP_POST, __UNLOCK_DOOR);
    server.on("/api/lock", HTTP_POST, __LOCK_DOOR);

    server.begin();
    Serial.printf("[#] Server started \n");
}

void loop() {
    server.handleClient();
}
