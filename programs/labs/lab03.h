#include "mbed.h"
#include "crazyflie.h"

            /*****************************\
            |**** DEFINIÇÕES DE PINOS ****|
            \*****************************/

// Define all motors as PWM output objects
PwmOut Mot1(MOTOR1);
PwmOut Mot2(MOTOR2);
PwmOut Mot3(MOTOR3);
PwmOut Mot4(MOTOR4);


            /*******************************\
            |**** DEFINIÇÕES DE FUNÇÕES ****|
            \*******************************/

// Converts desired angular velocity (rad/s) to PWM signal (%)
float control_motor(float OMEGA_R)
{
    return Motor_a2 * OMEGA_R * OMEGA_R + Motor_a1 * OMEGA_R;
}


            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{   
    // Set PWM frequency to 500Hz
    Mot1.period(1.0/500.0);
    Mot2.period(1.0/500.0);
    Mot3.period(1.0/500.0);
    Mot4.period(1.0/500.0);

    // Calcula o valor de PWM para tal rotação
    float PWMCalculado = control_motor(1000);



    while(true)
    {
    }
    
}

