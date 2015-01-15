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
#include <sensor_msgs/LaserScan.h>
std_msgs::Int8 integer;
double summe_links;
std_msgs::Int8 ergebnis__;
void Laserscan_Callback(const sensor_msgs::LaserScan::ConstPtr& scanner_) {
ros::Publisher obstacle_pub;
ros::NodeHandle nh;
obstacle_pub=nh.advertise<std_msgs::Int8>("obstacle_obstcle",100);
ros::Rate loop_rate(50);
summe_links=0;
for(unsigned int i = 10; i < 30; ++i){
summe_links = summe_links + scanner_ -> ranges[i];
}
if (summe_links < 50 ){
ergebnis__.data = 1;//Hindernis vorhanden
}
else ergebnis__.data = 0;//freie Bahn
std::cout << "Summe ergibt: " << summe_links <<"\n";
std::cout << "logisches Ergebnis: " << ergebnis__ << "\n";
int co = 0;
while (ros::ok())
{
obstacle_pub.publish(ergebnis__);
ros::spinOnce();
loop_rate.sleep();
++co;
}
}
int main(int argc, char **argv){
ros::init(argc,argv,"obstacle");
ros::Publisher obstacle_pub;
ros::NodeHandle nh;
ros::Subscriber obstacle_sub = nh.subscribe("/scan",1,Laserscan_Callback);
ros::spin();
return 0;
}
