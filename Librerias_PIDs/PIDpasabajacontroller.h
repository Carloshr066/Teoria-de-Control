#ifndef FILTEREDPIDCONTROLLER_H
#define FILTEREDPIDCONTROLLER_H

class FilteredPIDController {
public:
    FilteredPIDController(float Kp, float Ki, float Kd, float dt, int N);
    float compute(float setpoint, float measured_value);

private:
    float A0;
    float A1;
    float A0d;
    float A1d;
    float A2d;
    float tau;
    float alpha;
    float alpha_1;
    float alpha_2;
    float dt;
    float error[3];
    float d0;
    float d1;
    float fd0;
    float fd1;
    float output;
};

#endif
