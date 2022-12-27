#include "light.h"

#include <Arduino.h>

bool light_on = false;
bool light_off = false;
bool light_state = false;

void lightWrite(int light1_duty, int light2_duty) {
    Serial.printf("%s:%d-%d\n", __func__, light1_duty, light2_duty);
    ledcWrite(light1_channel, light1_duty);
    delay(100);
    ledcWrite(light2_channel, light2_duty);
}

void lightOff() {
    Serial.printf("%s %d\n", __func__, __LINE__);
    lightWrite(light1_off_duty, light2_off_duty);
    light_state = false;
}

void lightOn() {
    Serial.printf("%s %d\n", __func__, __LINE__);
    lightWrite(light1_on_duty, light2_on_duty);
    light_state = true;
}

// 停止电机控制，方便手动开关灯
void lightNeu() {
    Serial.printf("%s %d\n", __func__, __LINE__);
    lightWrite(0, 0);
}

void lightSetup() {
    Serial.printf("%s %d\n", __func__, __LINE__);
    ledcSetup(light1_channel, light_freq, light_resolution);
    ledcSetup(light2_channel, light_freq, light_resolution);

    ledcAttachPin(light1_pin, light1_channel);
    ledcAttachPin(light2_pin, light2_channel);

    pinMode(brightness_pin, INPUT);
}
