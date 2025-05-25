#ifndef ADVANCEDPIDCONTROLLER_H
#define ADVANCEDPIDCONTROLLER_H

class AdvancedPIDController {
public:
    AdvancedPIDController(float Kp, float Ki, float Kd, float dt);
    float compute(float setpoint, float measured_value);

private:
    float A0;
    float A1;
    float A2;
    float dt;
    float error[3];
    float output;
};

#endif
