#pragma once

#include <IPAddress.h>

void blinkerSetup();
void blinkerLoop();

// blinker(点灯)APP的Secret Key
const char auth[] = "91dc6624d031";

// 添加室友手机的IP（使用路由器固定IP）
const IPAddress remote_ip1(192, 168, 1, 100);
const IPAddress remote_ip2(192, 168, 1, 109);
const IPAddress remote_ip3(192, 168, 1, 106);
const IPAddress remote_ip4(192, 168, 1, 112);