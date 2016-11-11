/*
Copyright (c) 2016 Ubidots.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Made by Mateo Velez - Metavix for Ubidots Inc

*/

#include "UbidotsESPMQTT.h"

Ubidots::Ubidots(char* token) {
    _token = token;
    currentValue = 0;
    val = (Value *)malloc(MAX_VALUES*sizeof(Value));
}

void Ubidots::begin(void (*callback)(char*,uint8_t*,unsigned int)) {
    this->callback = callback;
    _client.setServer(SERVER, MQTT_PORT);
    _client.setCallback(callback);
}

bool Ubidots::add(char* variableLabel, float value) {
    return add(variableLabel, value, "NULL", "NULL");
}

<<<<<<< HEAD
bool Ubidots::add(char* variableLabel, float value) {
    return add(variableLabel, value, "NULL", "NULL");
}


bool Ubidots::add(char* variableLabel, float value, char *context) {
    return add(variableLabel, value, context, "NULL");
}


=======
bool Ubidots::add(char* variableLabel, float value, char *context) {
    return add(variableLabel, value, context, "NULL");    
}

>>>>>>> origin/master
bool Ubidots::add(char* variableLabel, float value, char *context, char *timestamp) {
    (val+currentValue)->_variableLabel = variableLabel;
    (val+currentValue)->_value = value;
    (val+currentValue)->_context = context;
    (val+currentValue)->_timestamp = timestamp;
    currentValue++;
    if (currentValue > MAX_VALUES) {
        Serial.println(F("You are sending more than the maximum of consecutive variables"));
        currentValue = MAX_VALUES;
    }
    return true;
}

bool Ubidots::ubidotsSubscribe(char* deviceLabel, char* variableLabel) {
    char topic[150];
    sprintf(topic, "%s%s/%s/lv", FIRST_PART_TOPIC, deviceLabel, variableLabel);
    if (!_client.connected()) {
        reconnect();
    }
    return _client.subscribe(topic);
}

<<<<<<< HEAD

bool Ubidots::ubidotsPublish(char *sourceLabel) {
    char topic[150];
    char payload[500];
    String str;
    sprintf(topic, "%s%s", FIRST_PART_TOPIC, sourceLabel);
    sprintf(payload, "{");
    for (int i = 0; i <= currentValue; ) {
        str = String((val+i)->_value, 2);
        Serial.println(str);
=======
bool Ubidots::ubidotsPublish() {
    char topic[150];
    char payload[500];
    String str;
    sprintf(topic, "%sESP8266", FIRST_PART_TOPIC);
    sprintf(payload, "{");
    for (int i = 0; i <= currentValue; ) {
        str = String((val+i)->_value, 2);
>>>>>>> origin/master
        sprintf(payload, "%s\"%s\": [{\"value\": %s", payload, (val+i)->_variableLabel, str.c_str());
        if ((val+i)->_timestamp != "NULL") {
            sprintf(payload, "%s, \"timestamp\": %s", payload, (val+i)->_timestamp);
        }
        if ((val+i)->_context != "NULL") {
            sprintf(payload, "%s, \"context\": {%s}", payload, (val+i)->_context);
        }
        i++;
        if (i >= currentValue) {
            sprintf(payload, "%s}]}", payload);
            break;
        } else {
            sprintf(payload, "%s}], ", payload);
        }
    }
    currentValue = 0;
    return _client.publish(topic, payload);
}

void Ubidots::reconnect() {
    while (!_client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (_client.connect("ESP8266", _token, NULL)) {
            Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client.state());
      Serial.println(" try again in 3 seconds");
      delay(3000);
    }
  }
}
bool Ubidots::loop() {
    if (!_client.connected()) {
        reconnect();
    }
    return _client.loop();
}
bool Ubidots::wifiConnection(char* ssid, char* pass) {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(F("WiFi connected"));
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
}
