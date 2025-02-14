# include "mbed.h"
# include "crazyflie.h"

// Crazyflie controller objects
Mixer mixer ;
EstimadorAtitude att_est ;
AttitudeController att_cont ;
EstimadorVertical ver_est ;
VerticalController ver_cont ;

 // Ticker objects
 Ticker tic , tic_range, tic_subida;

 // Interrupt flag and counter variables
 bool flag , flag_range, flag_subida;

float Delta_z = 0;
float z_final = 1.0;
float z_r     = 0.1;

 // Callback functions
 void callback () { flag = true ; }
 void callback_range () { flag_range = true ; }
 void callback_subida () { if(z_r != z_final){ z_r+=0.1; } }

 // Main program
 int main ()
 {
    // Set references
    
    float phi_r   = 0.0;
    float theta_r = 0.0;
    float psi_r   = 0.0;

    // Initialize estimators objects
    att_est.init () ;
    ver_est.init () ;

    // Initialize interrupts
    tic.attach( &callback, EstAti_dt);
    tic_range.attach( &callback_range, Est_Ver_dt);

    tic_subida.attach( &callback_subida, 4);

    // Arm motors and run controller while stable
    mixer.arm () ;
    while ( abs ( att_est.phi ) <= pi /4.0 && abs ( att_est.theta ) <= pi /4.0 && abs(att_est.p) <= 4.0* pi && abs ( att_est .q) <= 4.0* pi && abs( att_est .r) <= 4.0*pi)
    {
        if ( flag )
        {
            flag = false ;
            att_est.estimate () ;
            ver_est.predict ( ver_cont.f_t );
            if ( flag_range )
            {
                flag_range = false ;
                ver_est . correct ( att_est.phi , att_est.theta );
            }
            ver_cont . control (z_r , ver_est .z, ver_est .w);
            att_cont . control (phi_r , theta_r ,psi_r , att_est .phi , att_est .theta , att_est .
            psi , att_est .p, att_est .q, att_est .r);
            mixer . atuar ( ver_cont . f_t /( cos ( att_est .phi) *cos ( att_est . theta )) ,
            att_cont . tau_phi , att_cont . tau_theta , att_cont . tau_psi );
        }
    }
    // Disarm motors and end program
    mixer.desarm () ;
    while(true) ;
 }