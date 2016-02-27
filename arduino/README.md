# ESPadon

# Setup
```C
#include "espadon.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial( 11 , 10 );   # The ESP8266 is connected to the SoftwareSerial port
ESPadon esp( mySerial );


void setup() {
  Serial.begin( 9600 );
  mySerial.begin( 9600 );             # The firmware is configured the 9600 speed
}
```

# Main fonctions

```C
char my_ssid[] = "MyNetWorkSSID";                # Connection
char my_passphrase[] = "My_Passphrase";
int result = 0;
result  = esp.begin( my_ssid , my_passphrase );  # https://www.arduino.cc/en/Reference/WiFiBegin
delay(5000);

char url[] = "http://192.168.0.10:8000/";        # Outgoing HTTP request
int wstatus = esp.urlOpen( url );
Serial.print( "HTTP Status : " );
Serial.println( wstatus );

char ssid[50] = "";                              # Get the current SSID
esp.SSID( ssid );                                # https://www.arduino.cc/en/Reference/WiFiSSID
Serial.print( "SSID : " );
Serial.println( ssid );

int status = 0;                                  # Get the status of the ESP8266 module 
status = esp.status( );                          # https://www.arduino.cc/en/Reference/WiFiStatus
Serial.print( "ESP8266 status : " );
Serial.println( status );

int mac[6];                                      # Get the MAC address of the ESP8266 module
esp.macAddress( mac );                           # https://www.arduino.cc/en/Reference/WiFiMACAddress
Serial.print( "MAC : " );
for (int i=0 ; i<6 ; i++ ) {
    Serial.print( mac[i] , HEX );
}

int ip[4];                                       # Get the IP address of  the ESP8266 module
esp.localIP( ip );                               # https://www.arduino.cc/en/Reference/WiFiLocalIP
Serial.print( "IP : " );
for (int i=0 ; i<4 ; i++ ) {
    Serial.print( ip[i] , DEC );
}

int mask[4];                                     # Get the subnetmask of  the ESP8266 module
esp.subnetMask( mask );                          # https://www.arduino.cc/en/Reference/WiFiSubnetMask
Serial.print( "Subnet mask : " );
for (int i=0 ; i<4 ; i++ ) {
    Serial.print( mask[i] , DEC );
}

Serial.println( "Disconnect" );                  # Disconnect from the current Wifi network
esp.disconnect( );                               # https://www.arduino.cc/en/Reference/WiFiDisconnect
}

esp.attach( incoming );                          # Attach a callback function for incoming HTTP requests
```

# Embedded Web server

* A basic web interface
```
http://192.168.0.10/ESPadon
```

* digitalWrite request
```
http://192.168.0.10/digitalwrite/13/1
```

* analogWrite request
```
http://192.168.0.10/analogwrite/13/1
```

* digitalRead request
```
http://192.168.0.10/digitalread/6
```

* analogWrite request
```
http://192.168.0.10/analogread/14
```