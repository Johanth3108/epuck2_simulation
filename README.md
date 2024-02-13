# epuck2 webots simulation for Obstacle Avoidance

## Description
This repository contains code for simulating obstacle avoidance behavior of an e-puck robot using Webots simulation environment. The simulated e-puck robot is equipped with distance sensors to detect obstacles in its surroundings and maneuver accordingly to avoid collisions.

## Contents
- **epuck_UoS_sim_fin.c**: This file contains the main simulation code for controlling the e-puck robot in the Webots environment.
- **README.md**: This file.

## Requirements
- Webots: Ensure that Webots is installed and properly configured in your development environment to run the simulation.
- Compiler: Use a compatible C compiler to compile the code for the simulated e-puck robot.

## Usage
1. Clone the repository to your local machine:

```bash
git clone [https://github.com/Johanth3108/epuck2_simulation]
```

2. Open the `epuck_UoS_sim_fin.c` file in your preferred text editor or integrated development environment (IDE).

3. Compile the code using a C compiler compatible with Webots.

4. Open Webots and load the e-puck robot simulation environment.

5. Upload the compiled binary to the simulated e-puck robot in Webots.

6. Run the simulation and observe the behavior of the e-puck robot as it avoids obstacles using the simulated distance sensors.

## Functionality
The main functionality of the simulation code is to control the movement of the simulated e-puck robot based on readings from its distance sensors. The robot will:
- Move forward if no obstacles are detected.
- Turn left or right if obstacles are detected on either side.
- Stop if obstacles are detected in front of the robot.

## Customization
You can customize the behavior of the simulated e-puck robot by adjusting parameters such as:
- Threshold values for obstacle detection (`thresh`).
- Maximum speed of the robot (`MAX_SPEED`).
- Angular speed for rotation (`ang_speed_deg`).
- Duration of rotation for specific angles.

## Contributors
- Johanth P S(https://github.com/Johanth3108)
