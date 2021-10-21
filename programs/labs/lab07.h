#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

USBSerial serial;

char command;

EstimadorAtitude Est_Ati;

Ticker tic;

bool flag;

void callback()
{
    flag = true;
}

            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{  
    Est_Ati.init();
    
    tic.attach( &callback, EstAti_dt);

    // Loop principal
    while(true)
    {
        if(flag)
        {
            flag = false;
            Est_Ati.estimate();
        }

        if (serial.readable())
        {
            command = serial.getc();
            if (command == 'p') serial.printf("%f, %f, %f\n", Est_Ati.phi, Est_Ati.theta, Est_Ati.psi);
        }
    }
    
}
