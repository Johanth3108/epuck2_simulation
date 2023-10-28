/*
 * File:          epuck_UoS_sim_fin.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */

#include <stdio.h>
#include <math.h>
#include <webots/robot.h>
#include <webots/distance_sensor.h>
#include <webots/motor.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

#define tot_sens 8
static WbDeviceTag distance_sensors[tot_sens];
static const char *distance_sensors_names[tot_sens] = {"ps0", "ps1", "ps2", "ps3", "ps4", "ps5", "ps6", "ps7"};
static WbDeviceTag left_motor, right_motor;

#define thresh 120

/* angular speed of bot in rad/s */
#define MAX_SPEED 6.28

/* angular speed in degrees */
#define ang_speed_deg 283.588111888

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
 
bool * get_sensors_condition()
{
  static bool sensors_condition[tot_sens] = {false};
  for (int i = 0; i < tot_sens ; i++) {
  /*
  * Obstacle detected condition is true if the sensor values is larger then the threshold value
  * */
    if (wb_distance_sensor_get_value(distance_sensors[i]) > thresh) {
      sensors_condition[i] = true;
    }
    else {
      sensors_condition[i] = false;
    }
  }
  return sensors_condition;
}

void print_sensor_values() {
  printf("%s sensor values: ", wb_robot_get_name());
  for (int i = 0; i < tot_sens ; i++) {
    printf("%d:%.3f ", i, wb_distance_sensor_get_value(distance_sensors[i]));
  }
  printf("\n");
}

/* Stop the robot */
void motor_stop() {
  wb_motor_set_velocity(left_motor, 0);
  wb_motor_set_velocity(right_motor, 0);
}

/* move the robot forward */
void motor_move_forward() {
  wb_motor_set_velocity(left_motor, MAX_SPEED);
  wb_motor_set_velocity(right_motor, MAX_SPEED);
}

/* move the robot rightwards */
void motor_rotate_right() {
  wb_motor_set_velocity(left_motor, MAX_SPEED);
  wb_motor_set_velocity(right_motor, -MAX_SPEED);
}

/* move the robot leftwards */
void motor_rotate_left() {
  wb_motor_set_velocity(left_motor, -MAX_SPEED);
  wb_motor_set_velocity(right_motor, MAX_SPEED);
}

static float calculate_rotation_time(float degrees)
{
  return abs(degrees) / ang_speed_deg;
}

void motor_rotate_left_in_degrees(float degrees) {
  motor_rotate_left();
  float duration = calculate_rotation_time(degrees);
  float start_time = wb_robot_get_time();
  do
  {
    wb_robot_step(TIME_STEP);
  } while (wb_robot_get_time() < start_time + duration);
  motor_stop();
}

void motor_rotate_right_in_degrees(float degrees) {
  motor_rotate_right();
  float duration = calculate_rotation_time(degrees);
  float start_time = wb_robot_get_time();
  do
  {
    wb_robot_step(TIME_STEP);
  } while (wb_robot_get_time() < start_time + duration);
  motor_stop();
}


/* function for initialisation */
static void init_robot() {
  wb_robot_init();
  
  /* get simulator time step */
  // TIME_STEP = (int)wb_robot_get_basic_time_step();
	
  /* get a handler to the motors and set target position to infinity (speed control) */
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);
  
  /* get a handler to the sensors */
  for (int i = 0; i < tot_sens; i++) {
    distance_sensors[i] = wb_robot_get_device(distance_sensors_names[i]);
    wb_distance_sensor_enable(distance_sensors[i], TIME_STEP);
  }
}


int main(int argc, char **argv) {
  init_robot();

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(TIME_STEP) != -1) {
  
    // print_sensor_values();
		
    bool *is_sensors_active = get_sensors_condition();
		
    if (is_sensors_active[1] && is_sensors_active[6]) {
      motor_rotate_left_in_degrees(180);
      printf("corner lock");
    } else if (is_sensors_active[0] || is_sensors_active[1]) {
      motor_rotate_left();
      printf("right corner");
    } else if (is_sensors_active[7] || is_sensors_active[6]) {
      motor_rotate_right();
      printf("left corner");
    } else {
      motor_move_forward();
    }
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */

    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
