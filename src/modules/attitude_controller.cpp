# include "attitude_controller.h"

// Class constructor
AttitudeController :: AttitudeController ()
{
    tau_phi   = 0.0;
    tau_theta = 0.0;
    tau_psi   = 0.0;
}

// Control torques (N.m) given reference angles ( rad) and current angles ( rad ) and angular velocities ( rad /s)
void AttitudeController :: control ( float phi_r , float theta_r , float psi_r , float phi, 
                                     float theta , float psi , float p, float q, float r)
{
    tau_phi   = I_xx*control_siso(phi_r, phi, p, Ati_kp, Ati_kd);
    tau_theta = I_yy*control_siso(theta_r, theta, q, Ati_kp, Ati_kd);
    tau_psi   = I_zz*control_siso(psi_r, psi, r, psi_kp, psi_kd);
}

 // Control torque (N.m) given reference angle ( rad ) and current angle ( rad ) and angular velocity ( rad /s) with given controller gains
float AttitudeController :: control_siso ( float angle_r , float angle , float rate ,
                                           float kp , float kd)
{
    float velo_r = kp*(angle_r-angle);
    float acc_r = kd*(velo_r-rate);
    return acc_r;
}