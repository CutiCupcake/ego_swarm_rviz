#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>
#include <mavros_msgs/RCIn.h>  // mavros/rc/in话题对应的消息类型
#include <mavros_msgs/OverrideRCIn.h>  // mavros/rc/override话题对应的消息类型
#include <nav_msgs/Odometry.h>
geometry_msgs::Point current_odom_position;
geometry_msgs::PoseStamped goal;
ros::Publisher pub ;
int LastData ;
int threshold_Confirm = 500;
bool first_flag = true;
ros::Time last_move_time;//global time

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    current_odom_position.x = msg->pose.pose.position.x;
    current_odom_position.y = msg->pose.pose.position.y;
    current_odom_position.z = msg->pose.pose.position.z;
}

void rcInCallback(const mavros_msgs::RCIn::ConstPtr& msg)
{


    ros::Time time_now = ros::Time::now();//modified
    if ((time_now - last_move_time).toSec() < 1.0) {
        return; //modified，需要控制点移动的频率，如果距离上次移动不足1秒，则不进行任何操作。
    }
    
    int chan0 = msg->channels[0];
    int chan1 = msg->channels[1];
    int chan2 = msg->channels[9];//modified，油门改为sc通道，也就是10通道，往上拨rc值为1900
    int chan4 = msg->channels[4];
    int Confirm = msg->channels[5];

    if(chan4 > 1700)
    {
         if(first_flag){
                LastData = Confirm;
                first_flag = false;
                goal.pose.position.x = current_odom_position.x;
                goal.pose.position.y = current_odom_position.y;
                goal.pose.position.z = current_odom_position.z;
            }
        if( std::abs(Confirm - LastData) < threshold_Confirm) {
            if(chan0 > 1700) {
                goal.pose.position.y -= 0.2;
                last_move_time = time_now;//modified，每次移动都要记一次时间。
                ROS_INFO("Y--(channel 1)");
            } else if(chan0 < 1300) {
                goal.pose.position.y += 0.2;
                last_move_time = time_now;
                ROS_INFO("Y++(channel 1)");
            }
            if(chan1 > 1700) {
                goal.pose.position.x -= 0.2;
                last_move_time = time_now;
                ROS_INFO("X--(channel 2)");
            } else if(chan1 < 1300) {
                goal.pose.position.x += 0.2;
                last_move_time = time_now;
                ROS_INFO("X++(channel 2)");
            }
             if(chan2 > 1700) {
                goal.pose.position.z += 0.2;
                last_move_time = time_now;
                ROS_INFO("Z++++(channel 4)");
            } else if(chan2 < 1300) {
                goal.pose.position.z -= 0.2;
                last_move_time = time_now;
                ROS_INFO("Z----(channel 4)");
            }

        } else {
        // 当channel[7]大于1500时，发布目标点
            ROS_INFO("Pub!!!!!!!!");
            LastData = Confirm;
        //ros::NodeHandle nh;
            pub.publish(goal);
        }
    }
    else{
        first_flag = true;
    }
}

int main(int argc, char **argv)
{   
    
    ros::init(argc, argv, "rc_goal_publisher");
    ros::NodeHandle nh;
    last_move_time = ros::Time::now();//modified，添加一个全局变量
    pub = nh.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);

    ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("preview_goal_marker", 1);
    ros::Subscriber OdomSub = nh.subscribe("/Odometry_imu", 1, odomCallback);  // 订阅odom话题
    ros::Subscriber rcInSub = nh.subscribe("/mavros/rc/in", 1, rcInCallback);  // 订阅mavros/rc/in话题

    visualization_msgs::Marker marker;
    goal.header.frame_id = "camera_init";
    marker.header.frame_id = "camera_init";
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = 0.15;//modified ，改小了一点
    marker.scale.y = 0.15;
    marker.scale.z = 0.15;
    marker.color.a = 1.0;
    marker.color.r = 1.0;
    marker.color.g = 1.0;
    marker.color.b = 1.0;

    ROS_INFO("Set Target Point!!");	//使用摇杆设置目标点

    ros::Rate loop_rate(10);

    while (ros::ok()) {
        goal.header.stamp = ros::Time::now();
        marker.header.stamp = ros::Time::now();

        marker.pose.position.x = goal.pose.position.x;
        marker.pose.position.y = goal.pose.position.y;
        marker.pose.position.z = goal.pose.position.z;

        marker_pub.publish(marker);

        //ROS_INFO("The target point has been updated but not yet confirmed. Confirm using the remote control!!!"); //目标点已更新但尚未确认。使用遥控器确认。

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
