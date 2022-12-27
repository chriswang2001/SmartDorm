#include <WiFi.h>

#include "blinker.h"
#include "door.h"
#include "dorm.h"
#include "finger.h"
#include "light.h"
#include "ota.h"

/*
 * setup function
 */
void setup(void) {
    Serial.begin(115200);

    // Connect to WiFi network
    WiFi.begin(ssid, pswd);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    otaSetup();

    lightSetup();
    doorSetup();
    fingerSetup();

    blinkerSetup();
}

void loop(void) {
    otaLoop();
    blinkerLoop();
    fingerLoop();
}
