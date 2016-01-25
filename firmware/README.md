# ESPadon firmware

You can flash the ESP8266 module with the prebuilt firmware :

```shell
./esptool.py --port /dev/ttyUSB1 write_flash 0x00000 ESP8266.ino.generic.bin
```

[esptool](https://github.com/themadinventor/esptool)
