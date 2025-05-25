#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController {
public:
    PIDController(float Kp, float Ki, float Kd, float dt);
    float compute(float setpoint, float measured_value);

private:
    float Kp;
    float Ki;
    float Kd;
    float dt;
    float previous_error;
    float integral;
};

#endif
