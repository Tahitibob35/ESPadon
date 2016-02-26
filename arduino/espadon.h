/*
  espadon.h - Library for the ESP8266 module
  Created by David Hautbois.
  Released into the public domain.
 */
#ifndef espadon_h
#define espadon_h

#include "serialcomm.h"


/*
  An ESP8266 channel is activated by creating an instance of the ESPadon class passing
  a Stream object (hard or soft).

  The methods are:
    ESPadon - Class for using the ESP8266 module.
    httpGET( url )  - Send an GET HTTP request the the URL.
    SSID            - Get the current sSID og the ESP8266 module

 */

#include "Arduino.h"

//Local actions
#define A_WIFISTATUS             102
#define A_WIFIDISCONN            103
#define A_WIFIBEGIN              104
#define A_SSID                   105
#define A_BSSID                  106
#define A_MAC                    107
#define A_IP                     108
#define A_SUBNET                 109
#define A_STARTHTTPSERVER        110
#define A_HTTPGET                111

//Remote actions
#define A_HTTPREQUEST            112    //A changer

class ESPadon
{
    public:
        ESPadon( Stream &s );
        int httpGET( char * url );                     // Open the URL
        bool SSID( char * ssid );                      // Get the SSID
        int status( void );                            // Get the status
        bool disconnect( void );                       // Disconnects the ESP8266 module from the current network.
        int begin( char * ssid , char * password );    // Disconnects the ESP8266 module to the network.
        bool BSSID( int * bssid );                     // Get the BSSID
        bool macAddress( int * mac );                  // Get the Mac Address
        bool localIP ( int * ip );                     // Get the IP Address
        bool subnetMask ( int * ip );                  // Get the subnet
        bool startHTTPServer ( int port );             // Start the HTTP server on the specified port
        bool getHTTPRequest ( char * url , int urlsize );
        void check_reception( void );                  // Check for incoming messages
        void (*pHTTPCallBack)(void);                   // Callback for incoming HTTP request
        void attach( void ( *pcallbackfct )( void ) ); // Attach the HTTP callback

        SerialComm sc;


    private:
        Stream *_serial;
};

#endif
