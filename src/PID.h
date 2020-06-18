#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();
  
  void twiddle(double cte);
  /**
   * find best controller parameters for given cross track error.
   * @param cte The current cross track error
   */

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  
  /**
  * twiddle variables
  */
  
  bool start_;
  double bestErr;  
  double bestErrEver;
  double p [3] = {0,0,0};
  double dp [3] = {0,0,0};
  double sum_dp;
  bool firstCheckIncrement;
  bool firstCheckDecrement;
  int Counter;
  bool firstCheck;
  
};

#endif  // PID_H