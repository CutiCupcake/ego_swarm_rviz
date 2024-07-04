**Overview**

This project utilizes odometry information and listens to remote controller signals to dynamically update the goal points in RVIZ. The FSM (Finite State Machine) controls the program mode and uses the Ego-planner algorithm to guide the drone for obstacle avoidance navigation. The project requires you to customize your own ego_swarm algorithm.


Relative experiments video shown in:https://youtu.be/cB2DgIYcgro

https://youtu.be/HU8LMn0RQXs

![image](https://github.com/CutiCupcake/ego_swarm_rviz/assets/113587573/b6afb467-9ebe-4824-b6f2-d4761dc25ec6)

![image](https://github.com/CutiCupcake/ego_swarm_rviz/assets/113587573/f33cbfef-3981-4c29-9035-a8d7ed46bb02)



**Features**

1.Goal Program Design: Implemented a program to set and update goal points in RVIZ based on received signals.

2.Odometry and MavROS RC Message Listening: Listens to odometry data and remote control signals from MavROS.

3.Data Processing and Publishing: Processes the received data and publishes the updated goal points to RVIZ.

**Requirements**

1.Ego-planner Algorithm: Integrate and customize the Ego-planner algorithm for obstacle avoidance and navigation.

2.MavROS: Ensure MavROS is correctly set up to receive and send remote control signals.

3.RVIZ: Utilize RVIZ for visualization of the goal points and drone navigation path.
