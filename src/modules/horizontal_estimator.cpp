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
    x = x + u * EstAti_dt;
    y = y + v * EstAti_dt;
    u = u + g * theta * EstAti_dt;
    v = v - g * phi * EstAti_dt;
}

void EstimadorHorizontal::correct(float phi, float theta, float p, float q, float z)
{
    float den = cos(phi) * cos(theta) ;
    flow.read();
    if ( den > 0.5)
    {
        float d = z/ den;
        float u_m = (Sigma*flow.px + q)*d;
        float v_m = (Sigma*flow.py - p)*d;
        u = u + EstHor_l * EstAti_dt * (u_m - u);
        v = v + EstHor_l * EstAti_dt * (v_m - v);
    }
}