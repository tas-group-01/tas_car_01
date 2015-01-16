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
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <std_msgs/Int8.h>
#include <tf/transform_datatypes.h>
std_msgs::Int8 integ;
std_msgs::Float64 theta;
void pose_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& scanner_) {
ros::Publisher angle_pub;
ros::NodeHandle nh;
angle_pub=nh.advertise<std_msgs::Float64>("angle_angle",100);
ros::Rate loop_rate(50);
//tf:: double angle = winkel_->....
tf::Quaternion q(scanner_ -> pose.pose.position.x, scanner_ -> pose.pose.position.y, scanner_ -> pose.pose.orientation.z, scanner_ -> pose.pose.orientation.w);
theta.data= q.getAngle();
/* if (theta > 45) {
deflection_left = 1;
}
if (theta < 45) {*/
//integ.data = 1;
std::cout << "Winkel: "<< theta <<"\n";
int couu = 0;
while (ros::ok())
{
angle_pub.publish(theta);
ros::spinOnce();
loop_rate.sleep();
++couu;
}
}
int main(int argc, char **argv){
ros::init(argc,argv,"angler");
ros::Publisher angle_pub;
ros::NodeHandle nh;
ros::Subscriber angle_sub = nh.subscribe("amcl_pose",100,pose_Callback);
//ros::Subscriber registered_cone = nh.subscribe
ros::spin();
return 0;
}

