#include "horizontal_controller.h"

// Class constructor
HorizontalController::HorizontalController()
{
    phi_r   = 0.0;
    theta_r = 0.0;
}

// Control thrust force (N) given vertical position (m) and velocity (m/s)
void HorizontalController::control(float x_r, float y_r, float x, float y, float u, float v)
{
    theta_r = (1.0/g) * control_siso(x_r,x,u,kp_z,kd_z);
    phi_r = (-1.0/g) * control_siso(y_r,y,v,kp_z,kd_z);
}

// Control aceleration given reference position (m) and current position (m) and velocity (m/s) with given controller gains
float HorizontalController::control_siso(float position_r, float position, float velocity, float kp, float kd)
{
    float velo_r = kp*(position_r-position);
    float acc_r = kd*(velo_r-velocity);
    return acc_r;
}