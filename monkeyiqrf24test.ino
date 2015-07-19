#include <Streaming.h>
#include <SPI.h>
#include "printf.h"
#include "Switch.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "monkeyiqrf24.h"

monkeyiqrf24 radio;

enum { RMSG_JOYXY = 1, RMSG_JOYBUTTON_DOWN = 10, RMSG_JOYBUTTON_UP = 11 } RADIOMSGTYPES;
struct radiomsg {
  int type;
  union {
    struct {
      int h;  // 0 (left) to 1023 (r ) with 512 at idle
      int v;  // 0 (down) to 1023 (up) with 512 at idle
    } joyxy;
    struct {
      int b;
    } joyb;
    int dummy;
  };
};

void setup()
{
    Serial.begin(57600);
    printf_begin();
  Serial << "starting radio..." << endl;
  radio.setup();
  Serial << "starting loop..." << endl;

}

void loop() 
{
   if( struct radiomsg* msg = tryGetMessage()) 
   {
            switch( msg->type )
            {
               case RMSG_JOYXY:
                  Serial << "h: << " << msg->joyxy.h << "  v: " << msg->joyxy.v << "\n\r";
                  break;
               case RMSG_JOYBUTTON_DOWN:
                  pc.printf("button down " << msg->joyb.b << "\n\r";
                  break;
               case RMSG_JOYBUTTON_UP:
                  pc.printf("button up " << msg->joyb.b << "\n\r";
                  break;
                  
            }
   }
 
   radio.maybeSleep();
}

