
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <ros/ros.h>

#include "std_msgs/Int16.h"
#include "std_msgs/Float64.h"
#include <math.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tf/transform_listener.h>
#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <iostream>

#include <signal.h>

#include "stdio.h"
#include <sstream>

std_msgs::Float64  answer;
double factor;

void Callback2(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pos_) {

   ros::Rate loop_rate(50.0);  
   ros::NodeHandle nh;

    float x_Pos = pos_ -> pose.pose.position.x;   
    float y_Pos = pos_ -> pose.pose.position.y;
    float z_Pos = pos_ -> pose.pose.position.z;
   
   ROS_INFO("Pose: (%f, %f, %f)", x_Pos, y_Pos, z_Pos);  
   ros::Publisher velocity_pub;
   velocity_pub=nh.advertise<std_msgs::Float64>("vel_factor",100);
   ros::Publisher location_pub;
   location_pub=nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("loc_factor",100);
   
   int count = 0;
     while (ros::ok()){
  //set velocity_factor depending the position of the robot in the world
  
    std::cout<<"POSITION X: " << pos_ -> pose.pose.position.x << "\n" << "POSITION Y: " << pos_ -> pose.pose.position.y  << "\n";
    if ((pos_ -> pose.pose.position.y < 15.0) && (pos_ -> pose.pose.position.y > 9.5))  {
        factor = 1.8;
         }
    else {
        factor = 1.2;
         }
    
     std::cout<<"Geschwindigkeitsfaktor: "<<  factor << "\n";
    answer.data = factor;
    velocity_pub.publish(answer);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;  
     std::cout<<"while-Schleife: " << count << "\n";
}


}



int main(int argc, char** argv)
{

ros::init(argc, argv, "velocity_control2");

ros::Publisher pub;
ros::NodeHandle nh;
ros::Publisher velocity_pub;
int z=0;

ros::Subscriber  sub = nh.subscribe("/amcl_pose",50,Callback2);
++z;
std::cout<<"main-Funktion: " << z << "\n";
ros::spin(); 

return 0;
}





