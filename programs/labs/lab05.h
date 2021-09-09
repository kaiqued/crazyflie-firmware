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

// Define velocidades angulares (rad/s)
float omega_1 ;
float omega_2 ;
float omega_3 ;
float omega_4 ;

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
float Rad2PWM( float OMEGA_R );

// Converte força total de sustentação (N) e torques (N.m) para velocidades angulares (rad/s)
void Mixer ( float F_T , float TAU_PHI , float TAU_THETA , float TAU_PSI );

// Atua em todos os motores alterando a velocidade angular com base na força total de sustentação (N) e torques (N.m)
void Atuador ( float F_T , float TAU_PHI , float TAU_THETA , float TAU_PSI );


            /******************\
            |**** INT MAIN ****|
            \******************/

int main()
{
    INIT_DRONE();



    // Fazer o motor atuar com 70% da força peso
    Atuador (0 ,0 ,0 ,0.005) ;
    wait (5) ;
    // Desligar os motores
    Atuador (0 ,0 ,0 ,0) ;

    // Turn off red LEDs indicating motors are armed
    Led_R_L = 1;
    Led_R_R = 1;

    // Turn off the motors
    Mot1 = 0;
    Mot2 = 0;
    Mot3 = 0;
    Mot4 = 0;
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
    wait(1);
}

float Rad2PWM(float OMEGA)
{
    return Motor_a2 * OMEGA * OMEGA + Motor_a1 * OMEGA;
}

void Mixer ( float F_T , float TAU_PHI , float TAU_THETA , float TAU_PSI )
{
    omega_1 = ( F_T/(4*Motor_kl)) - ( TAU_PHI/(4*Motor_kl*l)) - ( TAU_THETA/(4*Motor_kl*l)) - ( TAU_PSI/(4*Motor_kd));
    omega_2 = ( F_T/(4*Motor_kl)) - ( TAU_PHI/(4*Motor_kl*l)) + ( TAU_THETA/(4*Motor_kl*l)) + ( TAU_PSI/(4*Motor_kd));
    omega_3 = ( F_T/(4*Motor_kl)) + ( TAU_PHI/(4*Motor_kl*l)) + ( TAU_THETA/(4*Motor_kl*l)) - ( TAU_PSI/(4*Motor_kd));
    omega_4 = ( F_T/(4*Motor_kl)) + ( TAU_PHI/(4*Motor_kl*l)) - ( TAU_THETA/(4*Motor_kl*l)) + ( TAU_PSI/(4*Motor_kd));

    if (omega_1 < 0) omega_1 = 0;
    if (omega_2 < 0) omega_2 = 0;
    if (omega_3 < 0) omega_3 = 0;
    if (omega_4 < 0) omega_4 = 0;

    omega_1 = sqrt(omega_1);
    omega_2 = sqrt(omega_2);
    omega_3 = sqrt(omega_3);
    omega_4 = sqrt(omega_4);
}

void Atuador ( float F_T , float TAU_PHI , float TAU_THETA , float TAU_PSI )
{
    Mixer (F_T , TAU_PHI , TAU_THETA , TAU_PSI );
    Mot1 = Rad2PWM( omega_1 ) ;
    Mot2 = Rad2PWM( omega_2 ) ;
    Mot3 = Rad2PWM( omega_3 ) ;
    Mot4 = Rad2PWM( omega_4 ) ;
}