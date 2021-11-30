#ifndef horizontal_controller_h
#define horizontal_controller_h

#include "mbed.h"
#include "crazyflie.h"

// Classe do controlador horizontal
class HorizontalController
{
    public:
      HorizontalController();

      void control (float x_r, float y_r, float x, float y, float u, float v);

      float phi_r, theta_r;
    
    private:
      float control_siso(float position_r, float position, float velocity, float kp, float kd);
};

#endif