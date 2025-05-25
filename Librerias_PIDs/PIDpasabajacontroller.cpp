#include "FilteredPIDController.h"

FilteredPIDController::FilteredPIDController(float Kp, float Ki, float Kd, float dt, int N) {
    this->dt = dt;
    this->A0 = Kp + Ki * dt;
    this->A1 = -Kp;
    this->A0d = Kd / dt;
    this->A1d = -2.0 * Kd / dt;
    this->A2d = Kd / dt;
    this->tau = Kd / (Kp * N);
    this->alpha = dt / (2 * tau);
    this->alpha_1 = alpha / (alpha + 1);
    this->alpha_2 = (alpha - 1) / (alpha + 1);
    this->error[0] = 0;
    this->error[1] = 0;
    this->error[2] = 0;
    this->d0 = 0;
    this->d1 = 0;
    this->fd0 = 0;
    this->fd1 = 0;
    this->output = 0; // Initial actuator value
}

float FilteredPIDController::compute(float setpoint, float measured_value) {
    error[2] = error[1];
    error[1] = error[0];
    error[0] = setpoint - measured_value;

    // PI
    output += A0 * error[0] + A1 * error[1];

    // Filtered D
    d1 = d0;
    d0 = A0d * error[0] + A1d * error[1] + A2d * error[2];
    fd1 = fd0;
    fd0 = alpha_1 * (d0 + d1) - alpha_2 * fd1;
    output += fd0;

    return output;
}
