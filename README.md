# ESPadon

## Description
ESPadon simlifies the use of the ESP8266 module from your Arduino board.
The project provides an Arduino library and a dedicated ESP8266 firmware.

## Example

```C
SoftwareSerial mySerial( 11 , 10 );
ESPadon esp( mySerial );
mySerial.begin( 9600 );
esp.begin( "MySSID" , "MyPassPhrase" );

int ip[4];
esp.localIP( ip );

esp.httpGET( "http://google.fr" );
```

## Requirements for firmware building and the Arduino library

The [SerialComm](https://github.com/Tahitibob35/SerialComm) library.

## Documentation

[Library documentation and source code](https://github.com/Tahitibob35/ESPadon/tree/master/arduino)

[The pre-built firmware](https://github.com/Tahitibob35/ESPadon/tree/master/firmware)
