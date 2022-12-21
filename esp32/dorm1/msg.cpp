#include "msg.h"

#include <Arduino.h>
#include <HTTPClient.h>

int wechatmsg(String msg) {
    HTTPClient http;

    String url =
        "http://wxpusher.zjiecode.com/api/send/message/"
        "?appToken=AT_GSU4EDjT5Ut8zyhBNl8uUArFgFn1iai8&topicId=3238&content=";

    msg.replace(" ", "%20");
    Serial.printf("[HTTP] BEGIN... msg:%s\n", msg);
    http.begin(url + msg);

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n",
                      http.errorToString(httpCode).c_str());
    }

    http.end();

    return httpCode;
}
