#ifndef attitude_estimator_h
#define attitude_estimator_h

#include "mbed.h"
#include "crazyflie.h"

// Classe do Estimador de Atitude
class EstimadorAtitude
{
  public:
    // Construtor
    EstimadorAtitude();
    // Inicializa a classe
    void init();
    // Estima os angulos de Euler (rad) e velocidades angulares (rad/s)
    void estimate();
    // Angulos de Euler
    float phi, theta, psi;
    // Velocidades Angulares
    float p, q, r;
    // Bias
    float p_bias, q_bias, r_bias;
  private:
    // IMI sensor
    BMI088 imu;

};

#endif