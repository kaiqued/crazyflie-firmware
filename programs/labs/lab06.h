#include "mbed.h"
#include "crazyflie.h"

Mixer mixer;

            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{   
    // Armar os motores
    mixer.arm();

    // Fazer o motor atuar com 70% da força peso
    //mixer.atuar(0.7*m*g, 0, 0, 0);
    wait (5) ;

    // Desligar os motores
    mixer.desarm();
    
    // Loop principal
    while(true)
    {
    }
    
}
