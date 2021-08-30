#include "mbed.h"
#include "crazyflie.h"

            /*****************************\
            |**** DEFINIÇÕES DE PINOS ****|
            \*****************************/

// Define os motores como PWMOut
PwmOut Mot1(MOTOR1);
PwmOut Mot2(MOTOR2);
PwmOut Mot3(MOTOR3);
PwmOut Mot4(MOTOR4);

// Define os Led's como DigitalOut
DigitalOut Led_G_L(LED_GREEN_L,!false);
DigitalOut Led_G_R(LED_GREEN_R,!false);
DigitalOut Led_R_L(LED_RED_L,!false);
DigitalOut Led_R_R(LED_RED_R,!false);


            /**********************************\
            |**** INICIALIZAÇÃO DE FUNÇÕES ****|
            \**********************************/

// Inicializa o Drone
void INIT_DRONE();

// Converte Velocidade angular (rad/s) para sinal PWM (%)
float Rad2PWM(float OMEGA_R);


            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{
    INIT_DRONE();

    float PWMCalculado = Rad2PWM(1000);




    // Turn off red LEDs indicating motors are armed
    Led_R_L = 1;
    Led_R_R = 1;
    while(true)
    {
    }
    
}


            /********************************\
            |**** DEFINIÇÕES DAS FUNÇÕES ****|
            \********************************/

void INIT_DRONE()
{
    // Set PWM frequency to 500Hz
    Mot1.period(1.0/500.0);
    Mot2.period(1.0/500.0);
    Mot3.period(1.0/500.0);
    Mot4.period(1.0/500.0);

    // Turn on red LEDs indicating motors are armed
    Led_R_L = 0;
    Led_R_R = 0;
}

float Rad2PWM(float OMEGA)
{
    return Motor_a2 * OMEGA * OMEGA + Motor_a1 * OMEGA;
}