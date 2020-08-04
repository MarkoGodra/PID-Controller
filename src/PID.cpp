#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_)
{

    Kp = Kp_;
    Ki = Ki_;
    Kd = Kd_;

    is_initialized = false;
    previous_cte = 0.0;
}

void PID::UpdateError(double cte)
{
    if(!is_initialized)
    {
        previous_cte = cte;
        is_initialized = true;
    }

    previous_cte = p_error;
    p_error = cte;
    d_error = cte - previous_cte;
    i_error += cte;
}

double PID::TotalError()
{

    double steer = -Kp * p_error - Kd * d_error - Ki * i_error;

    if(steer > 1.0)
    {
        steer = 1.0;
    }
    else if(steer < -1.0)
    {
        steer = -1.0;
    }

    return steer;
}
