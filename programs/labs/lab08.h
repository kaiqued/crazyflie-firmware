#include "mbed.h"
#include "crazyflie.h"

Mixer mixer;
EstimadorAtitude Est_Ati;
AttitudeController Con_Ati;

Ticker tic;

bool flag;

void callback() { flag = true; }

            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{  
    // Set references
    float f_t = 0.9*m*g;
    float phi_r = 0.0;
    float theta_r = 0.0;
    float psi_r = 0.0;

    Est_Ati.init();

    tic.attach( &callback, EstAti_dt);

    mixer.arm();

    // Loop principal
    while(abs ( Est_Ati.phi ) <= pi /4.0 && abs ( Est_Ati . theta ) <= pi /4.0 && abs(Est_Ati .p) <= 4.0* pi && abs ( Est_Ati .q) <= 4.0* pi && abs( Est_Ati .r) <= 4.0*pi)
    {
        if(flag)
        {
            flag = false;
            Est_Ati.estimate();
            Con_Ati.control(phi_r, theta_r, psi_r, Est_Ati.phi, Est_Ati.theta, Est_Ati.psi, Est_Ati.p, Est_Ati.q, Est_Ati.r);
            mixer.atuar(f_t, Con_Ati.tau_phi, Con_Ati.tau_theta , Con_Ati.tau_psi);
        }
    }
    
    mixer.desarm();
    while(true);
}
