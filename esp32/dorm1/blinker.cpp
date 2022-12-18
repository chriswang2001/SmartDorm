#define BLINKER_WIFI        // 使用wifi方式接入blinker
#define BLINKER_MIOT_LIGHT  // 以灯的形式接入小爱同学音箱

#include "blinker.h"

#include <Blinker.h>
#include <ESP32Ping.h>
#include <Ticker.h>

#include "door.h"
#include "dorm1.h"
#include "light.h"
#include "msg.h"

Ticker autoTicker;

BlinkerButton DOOR("door");
BlinkerButton LIGHT("light");

BlinkerNumber BRIGHTNESS("brightness");

BlinkerButton FRESH_IP("fresh_ip");
BlinkerText IP1("ip1");
BlinkerText IP2("ip2");
BlinkerText IP3("ip3");
BlinkerText IP4("ip4");

bool fresh_ip = false;

void autoCallback() {
    if (Blinker.hour() == 0 && Blinker.minute() <= (auto_time / 60)) {
        light_off = true;
    } else if (light_state == false && Blinker.hour() > hour_on &&
               analogRead(brightness_pin) > brightness_on &&
               true == pingCheck()) {
        light_on = true;
    }
}

void freshIPCallback(const String &state) {
    BLINKER_LOG("get button state: ", state);

    fresh_ip = true;
}

// 通过手机是否连上wifi，判断房间是否有人（不够准确）
bool pingCheck() {
    if (Ping.ping(remote_ip1, 10)) {
        return true;
    } else if (Ping.ping(remote_ip2, 10)) {
        return true;
    } else if (Ping.ping(remote_ip3, 10)) {
        return true;
    } else if (Ping.ping(remote_ip4, 10)) {
        return true;
    } else {
        return false;
    }
}

int pingState() {
    int count = 0;

    if (Ping.ping(remote_ip1, 3)) {
        IP1.print("在线");
        count++;
    } else {
        IP1.print("离线");
    }

    if (Ping.ping(remote_ip2, 3)) {
        IP2.print("在线");
        count++;
    } else {
        IP2.print("离线");
    }

    if (Ping.ping(remote_ip3, 3)) {
        IP3.print("在线");
        count++;
    } else {
        IP3.print("离线");
    }

    if (Ping.ping(remote_ip4, 3)) {
        IP4.print("在线");
        count++;
    } else {
        IP4.print("离线");
    }

    return count;
}

void doorReport() {
    if (digitalRead(door_state_pin)) {
        DOOR.icon("fad fa-door-closed");
        DOOR.color("#076EEF");
        DOOR.text("门：关");
        DOOR.print();
    } else {
        DOOR.icon("fad fa-door-open");
        DOOR.color("#E90909");
        DOOR.text("门：开");
        DOOR.print();
    }
}

void doorCallback(const String &state) {
    BLINKER_LOG("get button state: ", state);

    if (state == BLINKER_CMD_BUTTON_TAP) {
        door_open = true;
    }
}

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
        light_on = true;
    } else if (state == BLINKER_CMD_OFF) {
        light_off = true;
    }
}

void heartbeat() {
    BLINKER_LOG("heartbeat");

    doorReport();
    lightReport();
    BRIGHTNESS.print(analogRead(brightness_pin));
}

void dataRead(const String &data) {
    BLINKER_LOG("Blinker readString: ", data);
}

void miotPowerState(const String &state) {
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        light_on = true;
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    } else if (state == BLINKER_CMD_OFF) {
        light_off = true;
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}

void miotBright(const String &bright) {
    int colorW = bright.toInt();
    BLINKER_LOG("now set brightness: ", colorW);

    BlinkerMIOT.brightness(colorW);
    BlinkerMIOT.print();

    // 通过小爱同学自定义口令，将开门口令转化为设置灯的亮度
    door_open_voice = true;
}

void miotQuery(int32_t queryCode) {
    BLINKER_LOG("MIOT Query codes: ", queryCode);

    switch (queryCode) {
        case BLINKER_CMD_QUERY_ALL_NUMBER:
            BLINKER_LOG("MIOT Query All");
            BlinkerMIOT.powerState(light_state ? "on" : "off");
            BlinkerMIOT.color(0);
            BlinkerMIOT.mode(0);
            BlinkerMIOT.colorTemp(1000);
            BlinkerMIOT.brightness(1);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER:
            BLINKER_LOG("MIOT Query Power State");
            BlinkerMIOT.powerState(light_state ? "on" : "off");
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_COLOR_NUMBER:
            BLINKER_LOG("MIOT Query Color");
            BlinkerMIOT.color(0);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_MODE_NUMBER:
            BLINKER_LOG("MIOT Query Mode");
            BlinkerMIOT.mode(0);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_COLORTEMP_NUMBER:
            BLINKER_LOG("MIOT Query ColorTemperature");
            BlinkerMIOT.colorTemp(1000);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER:
            BLINKER_LOG("MIOT Query Brightness");
            BlinkerMIOT.brightness(1);
            BlinkerMIOT.print();
            break;
        default:
            BlinkerMIOT.powerState(light_state ? "on" : "off");
            BlinkerMIOT.color(0);
            BlinkerMIOT.mode(0);
            BlinkerMIOT.colorTemp(1000);
            BlinkerMIOT.brightness(1);
            BlinkerMIOT.print();
            break;
    }
}

void blinkerSetup() {
    // 初始化blinker
    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    Blinker.begin(auth, ssid, pswd);

    // 设置时区 保证blinker.hour能够获取到正确时间
    Blinker.setTimezone(8.0);

    // 注册回调函数
    Blinker.attachData(dataRead);
    Blinker.attachHeartbeat(heartbeat);

    autoTicker.attach(auto_time, autoCallback);
    DOOR.attach(doorCallback);
    LIGHT.attach(lightCallback);
    FRESH_IP.attach(freshIPCallback);

    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachBrightness(miotBright);
    BlinkerMIOT.attachPowerState(miotPowerState);
}

void blinkerLoop() {
    Blinker.run();

    if (true == door_open || true == door_open_voice) {
        if (true == door_open_voice) {
            if (false == pingCheck())
                goto next;
        }

        doorOpen();

        // 开门后自动判断是否开灯
        int8_t hour = Blinker.hour();
        if (hour > hour_on && analogRead(brightness_pin) > brightness_on) {
            lightOn();
            Blinker.delay(1000);
        } else {
            Blinker.delay(2000);
        }

        doorClose();

        door_open = false;
    }

next:
    if (true == light_on || true == light_off) {
        if (true == light_on) {
            lightOn();
        } else if (true == light_off) {
            lightOff();
        }

        lightReport();

        Blinker.delay(500);
        lightNeu();

        light_on = light_off = false;
    }

    if (true == fresh_ip) {
        pingState();

        fresh_ip = false;
    }
}
