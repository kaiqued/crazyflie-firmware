#include "attitude_estimator.h"
#include <cmath>

// Construtor
EstimadorAtitude::EstimadorAtitude() : imu(IMU_SDA, IMU_SCL)
{
    phi   = 0;
    theta = 0;
    psi   = 0;
    p     = 0;
    q     = 0;
    r     = 0;
    p_bias = 0;
    q_bias = 0;
    r_bias = 0;
}

// Inicializa a classe
void EstimadorAtitude::init()
{
    imu.init();
    for ( int i =0; i <500; i ++)
    {
    imu.read();
    p_bias += imu.gx;
    q_bias += imu.gy;
    r_bias += imu.gz;
    wait(EstAti_dt);
    }
    p_bias = p_bias/500;
    q_bias = q_bias/500;
    r_bias = r_bias/500;
}

// Estima os angulos de Euler (rad) e velocidades angulares (rad/s)
void EstimadorAtitude::estimate()
{
    imu.read();
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;
    float phi_g = phi + p * EstAti_dt;
    float phi_a = atan2(-imu.ay, -imu.az);
    phi = phi_g * (1-EstAti_alpha) +  phi_a * EstAti_alpha;

    float theta_g = theta + q * EstAti_dt;
    float theta_a = atan2(imu.ax, -imu.az);
    theta = theta_g * (1-EstAti_alpha) +  theta_a * EstAti_alpha;
}
    