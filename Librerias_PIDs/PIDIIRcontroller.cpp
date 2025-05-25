#include "AdvancedPIDController.h"

AdvancedPIDController::AdvancedPIDController(float Kp, float Ki, float Kd, float dt) {
    this->dt = dt;
    this->A0 = Kp + Ki * dt + Kd / dt;
    this->A1 = -Kp - 2 * Kd / dt;
    this->A2 = Kd / dt;
    this->error[0] = 0;
    this->error[1] = 0;
    this->error[2] = 0;
    this->output = 0; // Initial actuator value
}

float AdvancedPIDController::compute(float setpoint, float measured_value) {
    error[2] = error[1];
    error[1] = error[0];
    error[0] = setpoint - measured_value;
    output = A0 * error[0] + A1 * error[1] + A2 * error[2];
    return output;
}
