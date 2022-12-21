#pragma once

const int light1_pin = 25;  // 左灯引脚
const int light2_pin = 13;  // 右灯引脚

// 控制灯的电机占用的PWM通道
const int light1_channel = 8;
const int light2_channel = 9;

// 关灯时对应的占空比
const int light1_off_duty = 82;
const int light2_off_duty = 86;

// 开灯时对应的占空比
const int light1_on_duty = 101;
const int light2_on_duty = 67;

const int light_freq = 50;        // 频率
const int light_resolution = 10;  // 分辨率

const int hour_on = 15;  // 最早开灯时间 h

const int brightness_pin = 34;  // 光敏电阻输入端口（读到数据越大，亮度越低）
const int brightness_on = 2000;  // 光敏电阻阈值

void lightSetup();
void lightOn();
void lightOff();
void lightNeu();

extern bool light_on;
extern bool light_off;
extern bool light_state;
