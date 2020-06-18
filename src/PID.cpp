#include "PID.h"
#include <limits>
#include <iostream>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  
  //p = {Kp_, Ki_, Kd_};
  p[0] = Kp_;
  p[1] = Ki_;  
  p[2] = Kd_;
  dp[0] = Kp_*.1;
  dp[1] = Ki_*.1;  
  dp[2] = Kd_*.1;
  
  bestErr = std::numeric_limits<double>::max();
  
  firstCheckIncrement = true;
  firstCheckDecrement = true;
  

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  if (start_)
  {
    p_error = cte;
    start_ = false;
  }
  
  d_error=cte-p_error;
  p_error=cte;
  i_error+=cte;
  

  twiddle(cte);

}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return -p[0]*p_error-p[1]*i_error-p[2]*d_error;  // TODO: Add your total error calc here!
}

void PID::twiddle(double cte)
{
sum_dp = 0;
sum_dp = dp[0] + dp[1] + dp[2];
for( int i=0; i<3; i++)
  {

    if (firstCheckIncrement)
    {
        p[i] += dp[i];        

        bestErr = cte;
        firstCheckIncrement = false;
    }

    if (cte < bestErr)
    {
      if (!firstCheckIncrement && firstCheckDecrement)
      {
        bestErr = cte;
        dp[i] *= 1.1;
      } 

      if (!firstCheckIncrement && !firstCheckDecrement)
      {
        bestErr = cte;
        dp[0] *=  0.9;
      } 

        p[0] += dp[0];

    }
    else
    {
      if ( !firstCheckIncrement && firstCheckDecrement)
      {
        p[0] -=2 * dp[0];
        bestErr = cte;
        firstCheckDecrement = false;
      }
    }

  }
  
}

