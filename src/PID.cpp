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
  dp[0] = Kp_*.05;
  dp[1] = Ki_*.05;  
  dp[2] = Kd_*.05;
  
  bestErr = std::numeric_limits<double>::max();
  bestErrEver = std::numeric_limits<double>::max();
  
  firstCheckIncrement = true;
  firstCheckDecrement = true;
  firstCheck = true;
  Counter = 0;
  

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
if(!firstCheck)
 {
  if(Counter>500)
  { 
    firstCheck = false;
   	firstCheckIncrement = true;
  	firstCheckDecrement = true;
    Counter = 0;
  }
  Counter++;
 }

  
for( int i=0; i<3; i++)
  {
	
  	std::cout<<"values p ["<<i<<"]"<<p[i]<<","<< "   ";

    if (cte < bestErr)
    { 
      firstCheck = false;   
      if (firstCheckIncrement)
      {
        dp[i] *= 1.1;
        p[i] += dp[i];
        if(i==2)
        {
          firstCheckIncrement = false;
          bestErr = cte;
        } 
      } 

      else if (firstCheckDecrement)
      {    
        dp[i] *= 0.9;
      	p[i] += dp[i];
        if(i==2)
        {
          firstCheckDecrement = false;
          bestErr = cte;
        }  
      }
      
    }
	else if (bestErrEver < bestErr)
    {      
        if(!firstCheckIncrement && firstCheckDecrement)
        {
          dp[i] *= 0.9;
          p[i] += dp[i];
          if(i==2)
          {
            firstCheck = true;
            bestErrEver = bestErr;
          }
          
        }
        if(!firstCheckIncrement && !firstCheckDecrement)
        {
          dp[i] *= 1.1;
          p[i] += dp[i];
          if(i==2)
          {
            firstCheck = true;
            bestErrEver = bestErr;
          }
        }        
      
    }
  }
  
}

