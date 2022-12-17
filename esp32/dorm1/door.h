#pragma once

const int door_pin = 32;        // 开门电机引脚
const int door_open_pin = 33;   // 辅助开门引脚 0开门成功 1未开门
const int door_state_pin = 27;  // 监测门开关状态引脚 0门开 1门关

const int door_channel = 10;  // 通道

// 开关门时对应的占空比
const int door_on_duty = 21;
const int door_off_duty = 131;

const int door_close_time = 1300;  // 以上述占空比关门的时间

const int door_freq = 50;        // 频率
const int door_resolution = 10;  // 分辨率

void doorSetup();
void doorOpen();
void doorClose();

extern bool door_open;