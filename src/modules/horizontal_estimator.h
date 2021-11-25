#ifndef horizontal_estimator_h
#define horizontal_estimator_h

#include "mbed.h"
#include "crazyflie.h"

// Classe do Estimador Horizontal
class EstimadorHorizontal
{
  public:
    // Construtor
    EstimadorHorizontal();
    // Inicializa a classe
    void init();
    // Estima posição e velocidade Horizontal
    void predict(float phi, float theta);
    // Corrige a posição e velocidade Horizontal com as medições
    void correct(float phi, float theta, float p, float q, float z);
    // Posição Horizontal (m) e velocidade (m/s) estimados
    float x, y, u, v;
  private:
    // Range Sensor
    PMW3901 flow;

};

#endif