#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>

WebSocketsClient webSocket;
const char *id = "the7ag";
const char *pass = "12345678";
#define SERVER "192.168.245.138"
#define PORT 3000
#define URL "/"
#define ledPin D1

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: Serial.printf("Connected\n"); break;
    case WStype_TEXT:
      {
        int value = 0;   //{'1','2',3'}
        for (int i = 0; i < length; i++) {
          value = (value * 10) + (payload[i] - '0');
        }
        Serial.print(value);
        analogWrite(LED_BUILTIN, value); 
        analogWrite(ledPin, value); 
      }
      break;
  }
}

void setup() {
  pinMode(D1, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(id, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.SSID());
  Serial.println(WiFi.localIP());
  webSocket.begin(SERVER, PORT, URL);
}

void loop() {
  webSocket.loop();
}
