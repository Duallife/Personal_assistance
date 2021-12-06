#include "setting.h"
//#include "scr.h"

/*wifi and ntp setup*/

/*screen setup*/


void setup()
{
    Serial.begin( 115200 );

    wifiInit();
    displayInit();

    //load_scr1();

    Serial.println( "Setup done" );
}