#include "horizontal_estimator.h"
#include <cmath>

// Construtor
EstimadorHorizontal::EstimadorHorizontal() : flow (PA_7 ,PA_6 ,PA_5 , PB_4 )
{
    x = 0.0;
    y = 0.0;
    u = 0.0;
    v = 0.0;
}

// Inicializa a classe
void EstimadorHorizontal::init()
{
    flow.init();
}

// Estima 
void EstimadorHorizontal::predict(float phi, float theta)
{

}

void EstimadorHorizontal::correct(float phi, float theta, float p, float q, float z)
{
    float den = cos(phi) * cos(theta) ;
    if ( den > 0.5)
    {
        float d = z/ den;
        float u_m = (Sigma*flow.px + q)*d;
        float v_m = (Sigma*flow.py - p)*d;
        u = u_m;
        v = v_m;
    }
}