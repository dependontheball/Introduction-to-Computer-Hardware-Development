#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"


#define RED_GPIO       42
#define YELLOW_GPIO    41
#define GREEN_GPIO     40
#define LDR_GPIO       4
#define TOPIC_LIGHT    TOPIC_PREFIX "/light"
#define TOPIC_LED_RED  TOPIC_PREFIX "/led/red"


WiFiClient wifiClient;
PubSubClient mqtt(MQTT_BROKER, 1883, wifiClient);
uint32_t last_publish;


void connect_wifi() {
  printf("WiFi MAC address is %s\n", WiFi.macAddress().c_str());
  printf("Connecting to WiFi %s.\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    printf(".");
    fflush(stdout);
    delay(500);
  }
  printf("\nWiFi connected.\n");
}


void connect_mqtt() {
  printf("Connecting to MQTT broker at %s.\n", MQTT_BROKER);
  if (!mqtt.connect("", MQTT_USER, MQTT_PASS)) {
    printf("Failed to connect to MQTT broker.\n");
    for (;;) {} // wait here forever
  }
  mqtt.setCallback(mqtt_callback);
  mqtt.subscribe(TOPIC_LED_RED);
  printf("MQTT broker connected.\n");
}


void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, TOPIC_LED_RED) == 0) {
    payload[length] = 0; // null-terminate the payload to treat it as a string
    int value = atoi((char*)payload); 
    if (value == 0) {
      digitalWrite(RED_GPIO, LOW);
    }
    else if (value == 1) {
      digitalWrite(RED_GPIO, HIGH);
    }
    else {
      printf("Invalid payload received.\n");
    }
  }
}


void setup() {
  pinMode(RED_GPIO, OUTPUT);
  digitalWrite(RED_GPIO, 0);
  connect_wifi();
  connect_mqtt();
  last_publish = 0;
}


void loop() {
  // check for incoming subscribed topics
  mqtt.loop();


  // publish light value periodically (without using delay)
  uint32_t now = millis();
  if (now - last_publish >= 2000) {
    int level = 100 - (analogRead(LDR_GPIO)*100/4095);
    String payload(level);
    printf("Publishing light value: %d\n", level);
    mqtt.publish(TOPIC_LIGHT, payload.c_str());
    last_publish = now;
  }
}
