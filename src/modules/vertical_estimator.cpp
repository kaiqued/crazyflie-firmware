#include "vertical_estimator.h"
#include <cmath>

// Construtor
EstimadorVertical::EstimadorVertical() : range(E_SDA, E_SCL)
{
    z = 0;
    w = 0;
}

// Inicializa a classe
void EstimadorVertical::init()
{
    range.init();
}

// Estima 
void EstimadorVertical::predict(float f_t)
{
    z = z + w * EstAti_dt;
    //if( z > 0.05)
    //{
    //    w = w + ((f_t/m) - g) * EstAti_dt;
    //}
}

void EstimadorVertical::correct(float phi, float theta)
{
    range.read();
    if( range.d < 2.0)
    {
        float z_m = range.d * cos(phi) * cos(theta);
        w = w + Est_Ver_dt * Est_Ver_l1 * (z_m - z);
        z = z + Est_Ver_dt * Est_Ver_l2 * (z_m - z);
    }
}