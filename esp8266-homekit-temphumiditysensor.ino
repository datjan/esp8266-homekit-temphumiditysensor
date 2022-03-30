
/*  WEMOS D1 Mini
                     ______________________________
                    |   L T L T L T L T L T L T    |
                    |                              |
                 RST|                             1|TX HSer
                  A0|                             3|RX HSer
                  D0|16                           5|D1
                  D5|14                           4|D2
                  D6|12                    10kPUP_0|D3
RX SSer/HSer swap D7|13                LED_10kPUP_2|D4
TX SSer/HSer swap D8|15                            |GND
                 3V3|__                            |5V
                       |                           |
                       |___________________________|
       ________
      |        |
      | DHT11  |
      | DHT22  |
      |________|
      |  |  |  |
    VCC  D  N  GND

      
// connection schema
D1 mini -> DHT11/DHT22
3V3 -> VCC
3V3 -> 10kOhm -> D
D2 -> D
GND -> GND


*/


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#include "DHT.h"                // https://www.arduinolibraries.info/libraries/dht-sensor-library and https://www.arduino.cc/reference/en/libraries/adafruit-unified-sensor/


#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

#define DHTTYPE DHT11   // DHT 11

// PIN mit dem "Data" des DHT22 verbunden ist
uint8_t DHTPin = 4; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                


void setup() {
  Serial.begin(115200);
  wifi_connect(); // in wifi_info.h
  //homekit_storage_reset(); // to remove the previous HomeKit pairing storage when you first run this new HomeKit example

  pinMode(DHTPin, INPUT);
  
  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_temperature;
extern "C" homekit_characteristic_t cha_humidity;


// Called when the value is read by iOS Home APP
homekit_value_t cha_programmable_switch_event_getter() {
  // Should always return "null" for reading, see HAP section 9.75
  return HOMEKIT_NULL_CPP();
}

void my_homekit_setup() {
  arduino_homekit_setup(&config);
}

static uint32_t next_heap_millis = 0;
static uint32_t next_report_millis = 0;

void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_report_millis) {
    // report sensor values every 10 seconds
    next_report_millis = t + 10 * 1000;
    my_homekit_report();
  }
  if (t > next_heap_millis) {
    // Show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
        ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

  }
}

void my_homekit_report() {
  // FIXME, read your real sensors here.
  
  cha_temperature.value.float_value = dht.readTemperature(); // Gets the values of the temperature
  homekit_characteristic_notify(&cha_temperature, cha_temperature.value);

  cha_humidity.value.float_value = dht.readHumidity(); // Gets the values of the humidity 
  homekit_characteristic_notify(&cha_humidity, cha_humidity.value);


  //LOG_D("t %.1f, h %.1f, l %.1f, c %u, m %u, o %u", t, h, l, c, (uint8_t)m, o);
}

int random_value(int min, int max) {
  return min + random(max - min);
}
