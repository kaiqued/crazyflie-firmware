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

// Estimador de Atitude
const float EstAti_dt = 2e-3;
const float EstAti_wc = 3;        // rad/s
const float EstAti_alpha = (EstAti_wc * EstAti_dt)/(1 + (EstAti_wc * EstAti_dt));

// Controlador de Atitude
const float Ts = 0.4;
const float OS = 0.005;
const float Zet = abs(log(OS)) / sqrt( pow(log(OS),2) + pow(pi,2));
const float Wn = 4.0/(Zet*Ts);
const float Ati_kp = Wn / ( 2.0*Zet );
const float Ati_kd = 2.0 * Zet * Wn;

// Controlador de Atitude psi
const float psi_Ts = 0.4;
const float psi_OS = 0.005;
const float psi_Zet = abs(log(OS)) / sqrt( pow(log(OS),2) + pow(pi,2));
const float psi_Wn = 4.0/(Zet*Ts);
const float psi_kp = Wn / ( 2.0*Zet );
const float psi_kd = 2.0 * Zet * Wn;

// Estimador Vertical
const float Est_Ver_dt = 1.0/20.0;
const float Est_Ver_wc = 10.0;
const float Est_Ver_ze = sqrt(2.0)/2.0;

const float Est_Ver_l1 = pow(Est_Ver_wc, 2);
const float Est_Ver_l2 = 2 * Est_Ver_ze * Est_Ver_wc;

// Vertical controller gains
const float Ts_z = 3.0;                
const float OS_z = 0.020;              
const float zeta_z = abs(log(OS_z))/sqrt(pow(log(OS_z),2)+pow(pi,2));
const float omega_n_z = 4.0/(Ts_z*zeta_z);
const float kp_z = pow(omega_n_z,2.0);       
const float kd_z = 2.0*zeta_z*omega_n_z; 


// Estimador Vertical
const float Sigma = (2.0*tan((42.0*pi/180.0)/2.0))/(420.0*EstAti_dt);
const float EstHor_l = 50.0;

// Controlador Vertical
const float Ts_hor = 2.0;                
const float OS_hor = 0.010;              
const float zeta_hor = abs(log(OS_hor))/sqrt(pow(log(OS_hor),2)+pow(pi,2));
const float omega_n_hor = 4.0/(Ts_hor*zeta_hor);
const float kp_hor = pow(omega_n_hor,2.0);       
const float kd_hor = 2.0*zeta_hor*omega_n_hor; 
#endif