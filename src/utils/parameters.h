#ifndef parameters_h
#define parameters_h

#include <cmath>

// Physical constants
const float pi = 3.1416;
const float g = 9.81;       // m/s^2

// Quadcopter dimensions
const float m = 30.0e-3;    // kg
const float I_xx = 16.0e-6; // kg.m^2
const float I_yy = 16.0e-6; // kg.m^2
const float I_zz = 29.0e-6; // kg.m^2
const float l = 33.0e-3;    // m

// Motor Parameters
const float Motor_a1 = 2.026e-09; //
const float Motor_a2 = 1.344e-07; //
const float Motor_kl = 1.791e-8;  //    
const float Motor_kd = 1.436e-10; //
#endif