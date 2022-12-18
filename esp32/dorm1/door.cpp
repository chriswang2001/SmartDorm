#include "door.h"

#include <Arduino.h>

bool door_open = false;
bool door_open_voice = false;

void doorSetup() {
    ledcSetup(door_channel, door_freq, door_resolution);
    ledcAttachPin(door_pin, door_channel);

    pinMode(door_state_pin, INPUT_PULLDOWN);
    pinMode(door_open_pin, INPUT_PULLDOWN);
}

void doorOpen() {
    if (digitalRead(door_state_pin) == 0 || digitalRead(door_open_pin) == 0) {
        return;
    }

    ledcWrite(door_channel, door_on_duty);

    // 多次连续判定，避免奇异值
    int count = 0;
    do {
        if (digitalRead(door_open_pin) == 0) {
            count++;
        } else {
            count = 0;
        }
        delay(5);
    } while (count > 10);

    ledcWrite(door_channel, 0);
}

void doorClose() {
    // 多次连续判定，避免奇异值
    int count = 0;
    do {
        if (digitalRead(door_state_pin) == 1) {
            count++;
        } else {
            count = 0;
        }
        delay(5);
    } while (count > 100);

    ledcWrite(door_channel, door_off_duty);
    delay(door_close_time);
    ledcWrite(door_channel, 0);
}
