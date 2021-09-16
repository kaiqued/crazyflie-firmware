#ifndef mixer_h
#define mixer_h

#include "mbed.h"
#include "/utils/pin_names.h"
#include "/utils/parameters.h"

class Mixer
{
    public:
        // Construtor
        Mixer();
        // Atua em todos os motores alterando a velocidade angular com base na força total de sustentação (N) e torques (N.m)
        void atuar( float F_T , float TAU_PHI , float TAU_THETA , float TAU_PSI );
        // Arma/Prepara para os motores ligarem
        void arm();
        // Desarma/Desliga os motores
        void desarm();
    private:
        // Define os motores como PWMOut
        PwmOut Mot_1, Mot_2, Mot_3, Mot_4;
        DigitalOut Led_R_L, Led_R_R, Led_G_R, Led_G_L;
        // Define velocidades angulares (rad/s)
        float omega_r_1, omega_r_2, omega_r_3, omega_r_4;
        // Define o estado dos motores
        bool armed;
        // Converte força total de sustentação (N) e torques (N.m) para velocidades angulares (rad/s)
        void mixer ( float F_T , float TAU_PHI , float TAU_THETA , float TAU_PSI );
        // Converte Velocidade angular (rad/s) para sinal PWM (%)
        float Rad2PWM( float OMEGA_R );
        

};
#endif 