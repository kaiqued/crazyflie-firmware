#include "mixer.h"
#include "Music.h"

Mixer::Mixer() : Mot_1(MOTOR1), Mot_2(MOTOR2), Mot_3(MOTOR3), Mot_4(MOTOR4), Led_R_L(LED_RED_L,!false), Led_R_R(LED_RED_R,!false), Led_G_R(LED_GREEN_R,!false), Led_G_L(LED_GREEN_L,!false)
{

    // Turn off the motors
    Mot_1 = 0;
    Mot_2 = 0;
    Mot_3 = 0;
    Mot_4 = 0;

    // Desarm the motors
    armed = false;
    
    // Desligar os LED's indicando que os motores desligaram
    Led_R_L = 1;
    Led_R_R = 1;
    Led_G_L = 1;
    Led_G_R = 1;
    
    // NOTE_GS5, 4, NOTE_DS5, 4 , NOTE_GS4, 4, NOTE_AS4,8,
    for(int i = 0; i<31 ; i++){
        Play(melody[i], int(750/tempos[i]));
    }

    // Turn off the motors
    Mot_1 = 0;
    Mot_2 = 0;
    Mot_3 = 0;
    Mot_4 = 0;

    // Set PWM frequency to 500Hz
    Mot_1.period(1.0/500.0);
    Mot_2.period(1.0/500.0);
    Mot_3.period(1.0/500.0);
    Mot_4.period(1.0/500.0);

    // Turn off the motors
    Mot_1 = 0;
    Mot_2 = 0;
    Mot_3 = 0;
    Mot_4 = 0;
}

void Mixer::atuar(float F_T, float TAU_PHI, float TAU_THETA, float TAU_PSI)
{
    if (armed)
    {
        mixer(F_T, TAU_PHI, TAU_THETA, TAU_PSI);
        Mot_1 = Rad2PWM(omega_r_1);
        Mot_2 = Rad2PWM(omega_r_2);
        Mot_3 = Rad2PWM(omega_r_3);
        Mot_4 = Rad2PWM(omega_r_4);
    }
    else 
    {
        while(1)
        {
            Led_R_L = 0; // Liga
            Led_R_R = 0; // Liga
            wait(1);
            Led_R_L = 1; // Desliga
            Led_R_R = 1; // Desliga
            wait(1);
        }
    }
}

void Mixer::mixer(float F_T, float TAU_PHI, float TAU_THETA, float TAU_PSI)
{
    omega_r_2 = ( F_T/(4*Motor_kl)) - ( TAU_PHI/(4*Motor_kl*l)) + ( TAU_THETA/(4*Motor_kl*l)) + ( TAU_PSI/(4*Motor_kd));
    omega_r_1 = ( F_T/(4*Motor_kl)) - ( TAU_PHI/(4*Motor_kl*l)) - ( TAU_THETA/(4*Motor_kl*l)) - ( TAU_PSI/(4*Motor_kd));
    omega_r_3 = ( F_T/(4*Motor_kl)) + ( TAU_PHI/(4*Motor_kl*l)) + ( TAU_THETA/(4*Motor_kl*l)) - ( TAU_PSI/(4*Motor_kd));
    omega_r_4 = ( F_T/(4*Motor_kl)) + ( TAU_PHI/(4*Motor_kl*l)) - ( TAU_THETA/(4*Motor_kl*l)) + ( TAU_PSI/(4*Motor_kd));

    if (omega_r_1 < 0) omega_r_1 = 0;
    if (omega_r_2 < 0) omega_r_2 = 0;
    if (omega_r_3 < 0) omega_r_3 = 0;
    if (omega_r_4 < 0) omega_r_4 = 0;

    omega_r_1 = sqrt(omega_r_1);
    omega_r_2 = sqrt(omega_r_2);
    omega_r_3 = sqrt(omega_r_3);
    omega_r_4 = sqrt(omega_r_4);

}

float Mixer::Rad2PWM(float OMEGA_R)
{
    return Motor_a2 * OMEGA_R * OMEGA_R + Motor_a1 * OMEGA_R;
}

void Mixer::arm()
{
    armed = 1;

    // Turn on red LEDs indicating motors are armed
    Led_G_L = 1; // Desliga
    Led_G_R = 1; // Desliga
    Led_R_L = 0; // Liga
    Led_R_R = 0; // Liga
    wait(2);
}

void Mixer::desarm()
{
    armed = 0;
    // Desligar os motores
    Mot_1 = 0;
    Mot_2 = 0;
    Mot_3 = 0;
    Mot_4 = 0;
    // Desligar os LED's vermelhos indicando que os motores desligaram
    Led_R_L = 1;
    Led_R_R = 1;
    wait(2);
    Led_G_L = 0;
    Led_G_R = 0;
    wait(4);
    Led_G_L = 1; // Desliga
    Led_G_R = 1; // Desliga
}

void Mixer::Play(float PERIODO, float TEMPO)
{   
    if(Toca_Agora == 0){Toca_Agora = 1;}
    if(PERIODO == 0)
    {
        Toca_Agora = 0;
        wait_ms(TEMPO);
    }
    if (Toca_Agora == 1)
    {
        Mot_1.period(1.0/PERIODO);
        Mot_1 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 2;
        Mot_1 = 0;
    }

    else if (Toca_Agora == 2) 
    {
        Mot_2.period(1.0/PERIODO);
        Mot_2 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 3;
        Mot_2 = 0;
    }

    else if (Toca_Agora == 3) 
    {
        Mot_3.period(1.0/PERIODO);
        Mot_3 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 4;
        Mot_3 = 0;
    }
    
    else if (Toca_Agora == 4) 
    {
        Mot_4.period(1.0/PERIODO);
        Mot_4 = 0.1;
        wait_ms(TEMPO);
        Toca_Agora = 1;
        Mot_4 = 0;
    }
}