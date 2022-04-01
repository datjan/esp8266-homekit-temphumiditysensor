# esp8266-homekit-temphumiditysensor
This is a native HomeKit temperature and humidity sensor with D1 mini ESP8266 and DHT11/22 sensor in celsius.

## Hardware
The following hardware is required:
```
- D1 mini (ESP8266)
- Resistor 10kOhm
- Temperature and humidty sensor (DHT11 or DHT22)
```

Connection:
D1 mini -> DHT11/DHT22
```
3V3 -> VCC
3V3 -> 10kOhm -> D
D2 -> D
GND -> GND
```
![alt text](https://github.com/datjan/esp8266-homekit-temphumiditysensor/blob/main/connection-schema.png?raw=true)

## Development
This sketch is for following development environment
```
Arduino
```

Following libraries are required
```
https://github.com/datjan/Arduino-HomeKit-ESP8266 (fork from Mixiaoxiao/Arduino-HomeKit-ESP8266:master)
https://www.arduino.cc/reference/en/libraries/adafruit-unified-sensor/
https://www.arduinolibraries.info/libraries/dht-sensor-library
```

## Setup
Setup esp8266-homekit-temphumiditysensor.ino:
```
#define DHTTYPE DHT11   // DHT11 or DHT22
```

Setup my_accessory.c:
```
.password = "555-11-123". // Homekit Code
```

Setup wifi_info.h
```
const char *ssid = "xxx"; // SETUP Wlan ssid
const char *password = "xxx"; // SETUP Wlan password
```

## Upload to device
Following files needs to be uploaded to the ESP8266 (D1 mini)
```
esp8266-homekit-temphumiditysensor.ino
my_accessory.c
wifi_info.h
```

## Add device to Homekit
The device can be added to homekit like every other homekit device.
