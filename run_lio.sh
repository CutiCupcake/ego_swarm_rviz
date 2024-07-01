source ../devel/setup.bash
sudo chmod 777 /dev/ttyACM0
# sudo chmod 777 /dev/ttyUSB0

#如果在空地上跑换成apm.launch
roslaunch mavros px4.launch & sleep 4;
roslaunch px4ctrl run_ctrl.launch & sleep 1;
roslaunch ego_planner run_in_exp.launch & sleep 1;
rosrun mavros mavcmd long 511 105 5000 0 0 0 0 0 & sleep 1;
rosrun mavros mavcmd long 511 31 5000 0 0 0 0 0 & sleep 1;
rosrun mavros mavcmd long 511 83 5000 0 0 0 0 0 & sleep 1;
roslaunch goal goal_listener.launch ;

wait;
