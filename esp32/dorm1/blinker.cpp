// 使用wifi方式接入blinker
#define BLINKER_WIFI

#include "blinker.h"

#include <Blinker.h>

#include "dorm1.h"
#include "light.h"

BlinkerButton LIGHT("light");

void lightReport() {
    if (true == light_state) {
        LIGHT.icon("fad fa-lightbulb-on");
        LIGHT.color("#FBA713");
        LIGHT.text("灯：开");
        LIGHT.print("on");
    } else {
        LIGHT.icon("fad fa-lightbulb");
        LIGHT.color("#595959");
        LIGHT.text("灯：关");
        LIGHT.print("off");
    }
}

void lightCallback(const String &state) {
    BLINKER_LOG("get button state: ", state);

    if (state == BLINKER_CMD_ON) {
        lightOn();
    } else if (state == BLINKER_CMD_OFF) {
        lightOff();
    }

    lightReport();

    Blinker.delay(500);
    lightNeu();
}

void blinkerSetup() {
    // 初始化blinker
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    Blinker.begin(auth, ssid, pswd);

    LIGHT.attach(lightCallback);
}

void blinkerLoop() {
    Blinker.run();
}
