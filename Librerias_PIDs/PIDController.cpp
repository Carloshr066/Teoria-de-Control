#include "PIDController.h"

PIDController::PIDController(float Kp, float Ki, float Kd, float dt) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->dt = dt;
    this->previous_error = 0;
    this->integral = 0;
}

float PIDController::compute(float setpoint, float measured_value) {
    float error = setpoint - measured_value;
    integral += error * dt;
    float derivative = (error - previous_error) / dt;
    float output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;
    return output;
}
