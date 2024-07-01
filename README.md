**Overview**

This project utilizes odometry information and listens to remote controller signals to dynamically update the goal points in RVIZ. The FSM (Finite State Machine) controls the program mode and uses the Ego-planner algorithm to guide the drone for obstacle avoidance navigation. The project requires you to customize your own ego_swarm algorithm.
Features

    Goal Program Design: Implemented a program to set and update goal points in RVIZ based on received signals.
    Odometry and MavROS RC Message Listening: Listens to odometry data and remote control signals from MavROS.
    Data Processing and Publishing: Processes the received data and publishes the updated goal points to RVIZ.

**Requirements**

    Ego-planner Algorithm: Integrate and customize the Ego-planner algorithm for obstacle avoidance and navigation.
    MavROS: Ensure MavROS is correctly set up to receive and send remote control signals.
    RVIZ: Utilize RVIZ for visualization of the goal points and drone navigation path.
