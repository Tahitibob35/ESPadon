/************************************************************
 * Sample code with SoftwareSerial library.
 *
 ***********************************************************/

#include <SoftwareSerial.h>
#include "serialcomm.h"

SoftwareSerial mySerial( 11 , 10 );

SerialComm s(mySerial);

unsigned long previousMillis = 0;
const long interval = 2000;

int i = 0;
int j = 0;

char myname[] = "nano1";

void setup() {
  Serial.begin( 9600 );
  mySerial.begin( 9600 );

  // Attach the action #2 to the actionB function
  Serial.println( "Ready to play...." );
}


void loop( ) {

  if ( mySerial.available( ) ) {
    s.check_reception( );
  }

  i++;

  unsigned long currentMillis = millis();
    Serial.println( "Send msg" );
    char url[] = "http://192.168.0.10:8000/";
    if ( s.sendMessage( 11 , true , "s", "http://192.168.0.10:8000/") ) {
      int wstatus = 0;
      s.getData( "i" , &wstatus );
      Serial.print( "Status : " );
      Serial.println( wstatus );
      if (wstatus == 200 ) {
        j++;
      }
      Serial.print("Attempts : ");
      Serial.print( j );
      Serial.print(" , ");
      Serial.println( i );
      
    }
  delay(5000);
}


void actionB ( void ) {

  // Extract the data of the incoming message
  char a_string[20] = "";
  s.getData( "s" , &a_string , sizeof( a_string ) );

  Serial.print( "I'm " );
  Serial.print( myname );
  Serial.print( " and I received a message from " );
  Serial.println( a_string );

  s.sendAck(  "s" , myname );

}

