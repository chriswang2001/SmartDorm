#pragma once

const int light1 = 25;  // 左灯引脚
const int light2 = 13;  // 右灯引脚

// 控制灯的电机占用的PWM通道
const int light1_channel = 8;
const int light2_channel = 9;

// 关灯时对应的占空比
const int light1_off_duty = 82;
const int light2_off_duty = 86;

// 开灯时对应的占空比
const int light1_on_duty = 101;
const int light2_on_duty = 67;

const int freq = 50;        // 频率
const int resolution = 10;  // 分辨率

void lightSetup();
void lightOn();
void lightOff();
void lightNeu();

extern bool light_state;
