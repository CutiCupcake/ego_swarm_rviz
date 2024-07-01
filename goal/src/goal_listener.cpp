#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <quadrotor_msgs/GoalSet.h>
ros::Publisher goal_publisher;
void goalCallback(const geometry_msgs::PoseStamped::ConstPtr& nav_goal){
    quadrotor_msgs::GoalSet goal_set_msg;
    goal_set_msg.drone_id = 0;
    goal_set_msg.goal[0] = nav_goal->pose.position.x;
    goal_set_msg.goal[1] = nav_goal->pose.position.y;
    goal_set_msg.goal[2] = nav_goal->pose.position.z;
    goal_publisher.publish(goal_set_msg);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "goal_listener");
    ros::NodeHandle nh;
    ros::Subscriber goal_subscriber = nh.subscribe<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, goalCallback);
    goal_publisher = nh.advertise<quadrotor_msgs::GoalSet>("/goal" ,1);
    ros::spin();
    return 0;
}
