#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

USBSerial serial;


EstimadorAtitude Est_Ati;
EstimadorVertical Est_Ver;

Ticker tic, tic_range;

bool flag, flag_range;

void callback(){ flag = true; }
void callback_range(){ flag_range = true; }


            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{  
    Est_Ati.init();
    Est_Ver.init();

    tic.attach( &callback, EstAti_dt);
    tic_range.attach( &callback_range, Est_Ver_dt);

    // Loop principal
    while(true)
    {
        if(flag)
        {
            flag = false;
            Est_Ati.estimate();
            Est_Ver.predict(0.0);
            if( flag_range )
            {
                flag_range = false;
                Est_Ver.correct(  Est_Ati.phi, Est_Ati.theta );
                serial.printf("z [m ]:%6.2f | w [m/s ]:%6.2f \n", Est_Ver.z, Est_Ver.w);
            }
        }

    }
    
}
