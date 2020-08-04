# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

[![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

---

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

## Rubric Points

1) Your code should compile. Given that we've made CMakeLists.txt as general as possible, it's recommend that you do not change it unless you can guarantee that your changes will still compile on any platform.

    Code is able to compile.

2) The PID procedure follows what was taught in the lessons. It's encouraged to be creative, particularly around hyperparameter tuning/optimization. However, the base algorithm should follow what's presented in the lessons.

    Base algorithm follows what is presented in the lessons.

3) Describe the effect each of the P, I, D components had in your implementation. Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.

    Detailed reflection and also effect of each component (P, I, D) is given in Reflection section of this README.

4) Describe how the final hyperparameters were chosen. Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

    In Reflection section of this README, there is explanation on how final hyperparameters are choosen.

5) The vehicle must successfully drive a lap around the track. No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle).

    Vehicle is able to complete full lap around the track at 30 mph. No tire leaves the drivable portion of the track surface at any given moment.

## Reflection

### Parameter Tuning

When working with PID Controllers, most important part is hyperparamter tuning. Each of the parameters, P, I and D has it's own role in achieveing good controll perforamnces. 

Hyperparameter tuning can be done using different methods such as [Twiddle](https://martin-thoma.com/twiddle/), SGD, Zeigler-Nichols Method and others. In this solution manual (Trial and error) tuning has been used. General description of this process as stated [here](https://www.electronicshub.org/pid-controller-working-and-tuning-methods/) in section "Trial and Error Method":


1) Set integral and derivative terms to zero first and then increase the proportional gain until the output of the control loop oscillates at a constant rate. This increase of proportional gain should be in such that response the system becomes faster provided it should not make system unstable.
2) Once the P-response is fast enough, set the integral term, so that the oscillations will be gradually reduced. Change this I-value until the steady state error is reduced, but it may increase overshoot.
3) Once P and I parameters have been set to a desired values with minimal steady state error, increase the derivative gain until the system reacts quickly to its set point. Increasing derivative term decreases the overshoot of the controller response.

Each of the hyperparameters has it's own role in ensuring stable system:

**P** - Proportional component is used to steer car to the center of the road. The larger values of P correspond to steeper (more agresive) steering angles.

**I** - Integral component is used for compensating potential bias for turning in one direction.

**D** - Differential component is responsible for reducing car's oscilations. What this means is that this component reduces car's steering angle as it approaches it's target value, thus making it less likely to overshoot which would than also steer car away from target angle.

Final values of each parameter ended up the same as it is shown in previous lessons.

**P = 0.2**

**I = 0.0001**

**D = 3.0**

Initially, hyperparameters were all set to 0 and than i started with tweaks on P parameter. Once P reached shown value following [behavior](https://www.youtube.com/watch?v=TO9wpKx3jjw) was observed. As speed increased car started oscilating more and more until it finally crashed. This was expected behavior because at this moment, there is no D component set in order to compensate for oscilations.

Next step was tweaking D component, in order to compensate for oscilations. After reaching mentioned value following [behavior](https://www.youtube.com/watch?v=BLEsM4hwFAU) was observed. Oscilations were suppressed and car was much more stable.

Third step was to try out tuning I component. Tweaks of I component did not prove very usefull, so it is kept low. Observed behavior can be seen [here](https://www.youtube.com/watch?v=RPbrb27b2fQ)


