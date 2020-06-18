# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## PID controller

It is a well known control algorithm which is widely used in automation industries where it is generally accepted and widely used.

### P Proportional controller

It is used to get a proportional output using ratio of result and set value. It increases controller speed. When proportional control coefficient becomes large, system oscillates which does not fit to the solution.

### I integral Controller

Integral controller controls integral error that produces by the system over time. Controller tries to overcome this integral error by integrating over time.

### D Defferential Controller

Deferential controller is used to control the output from short time incremental variation. It gives further stebility to the system. 

## implementation

### function: init

initializing all variable at the beginning is done by this function. 

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

### function: UpdateError

Error is constantly updates this function. At the end, twiddle function is called for tuning parameters.

      if (start_)
      {
        p_error = cte;
        start_ = false;
      }

      d_error=cte-p_error;
      p_error=cte;
      i_error+=cte;


      twiddle(cte);

### function: TotalError

		return -p[0]*p_error-p[1]*i_error-p[2]*d_error;

### function: twiddle

This function tunes PID constants. First trying coefficients by adding a small value. If it favours, adds again. It it fails to reduce cross track error, reduces coefficients values by small amounts. This step is continued till it finds the best value. Now it is implemented as a combination of all three coefficients. For better results, every single coefficient could be tuned separately to find the optimum value.

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

            std::cout<<"values p ["<<i<<"]"<<p[i]<<",";

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
                std::cout<<"test11";
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
                  std::cout<<"test";
                }        

            }
          }

        }

## Result

I started with initial value obtained from manuel trials which is (0.15, 0.01, 3.0)

		pid.Init(0.15, 0.01, 3.0);

After applying twiddle for 2 successful laps, best results found as Kp = 0.226823,Ki = 0.0151215,Kd = 4.53646.

Here is short video of simulator with pid controller.

<!-- blank line -->
<figure class="video_container">
  <video controls="true" allowfullscreen="true" poster="../master/poster.PNG">
    <source src="../master/video.mp4" type="video/mp4">
    <source src="../master/video.ogg" type="video/ogg">
    <source src="../master/video.webm" type="video/webm">
  </video>
</figure>
<!-- blank line -->

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

