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
#include <std_msgs/Int8MultiArray.h>
#include <sensor_msgs/LaserScan.h>
std_msgs::Int8 ergebnis_cone;
double summe_cone_rechts;
double summe_cone_links;
double summe_cone_vorne;
int first_cone = 0;
int cone_on_right = 0;
int cone_on_left = 0;
std_msgs::Int8MultiArray array_;
void laser_Callback(const sensor_msgs::LaserScan::ConstPtr& scanner_) {
ros::Publisher cone_pub;
ros::NodeHandle nh;
cone_pub=nh.advertise<std_msgs::Int8MultiArray>("cone_cone",100);
ros::Rate loop_rate(50);
summe_cone_rechts = 0;
summe_cone_links = 0;
summe_cone_vorne = 0;
for (unsigned int i=10; i<30; ++i){
summe_cone_rechts = summe_cone_rechts + scanner_ -> ranges[i];
summe_cone_links = summe_cone_links + scanner_ -> ranges[i+680]; //scan from 690 to 710
summe_cone_vorne = summe_cone_vorne + scanner_ -> ranges[i+340];
}
//1.)
if (summe_cone_vorne < 50){
first_cone = 1; //reached first cone
}
//2.)
if ((summe_cone_rechts < 50) && (summe_cone_links < 30)) {
cone_on_right = 1;
cone_on_left = 0;
}
if ((summe_cone_links < 50) && (summe_cone_rechts < 30)) {
cone_on_left = 1;
cone_on_right = 0;
}
//3.)
std::cout << "Links: " << summe_cone_links <<' '<< "Vorne: " << summe_cone_vorne << ' ' << "Rechts: " << summe_cone_rechts << '\n';
std::cout <<"first_cone: "<< first_cone <<"\n";
std::cout << "cone_on_left: "<< cone_on_left <<"\n";
std::cout << "cone_on_right: "<< cone_on_right <<"\n";
//std::cout << "cone_on_rigt in array: " << "\n";
array_.data.clear();
array_.data.push_back(first_cone);
array_.data.push_back(cone_on_right);
array_.data.push_back(cone_on_left);
int co = 0;
while (ros::ok())
{
cone_pub.publish(array_);
ros::spinOnce();
loop_rate.sleep();
++co;
}
}
int main(int argc, char **argv){
ros::init(argc,argv,"cone");
ros::Publisher cone_pub;
ros::NodeHandle nh;
ros::Subscriber cone_sub = nh.subscribe("/scan",1,laser_Callback);
ros::spin();
return 0;
}
