#ifndef vertical_estimator_h
#define vertical_estimator_h

#include "mbed.h"
#include "crazyflie.h"

// Classe do Estimador Vertical
class EstimadorVertical
{
  public:
    // Construtor
    EstimadorVertical();
    // Inicializa a classe
    void init();
    // Estima posição e velocidade vertical
    void predict(float f_t);
    // Corrige a posição e velocidade vertical com as medições
    void correct(float phi, float theta);
    // Posição vertical (m) e velocidade (m/s) estimados
    float z, w;
  private:
    // Range Sensor
    VL53L1X range;

};

#endif