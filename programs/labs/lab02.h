#include "mbed.h"
#include "crazyflie.h"
// Define motor 1 as PWM output object
PwmOut Mot1(MOTOR1);




// Converts desired angular velocity (rad/s) to PWM signal (%)
float control_motor(float omega_r)
{
    return Motor_a2*omega_r*omega_r + Motor_a1*omega_r;
}

int main()
{   
    // Set PWM frequency to 500Hz
    Mot1.period(1.0/500.0);
    
    wait(1);
    Mot1 = 0.6;
    wait(4);
    Mot1 = 0.0;

    while(true)
    {
    }
    
}

