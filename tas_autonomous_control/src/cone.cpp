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
std_msgs::Float64 lenkung;

 int mode = 0;
double last_range = 0;
double  steer = 0, steer_factor = 1.2;
 
void laser_Callback(const sensor_msgs::LaserScan::ConstPtr& scanner_) {

   
   ros::Publisher cone_pub;
   ros::NodeHandle nh;
  
   
   ros::Rate loop_rate(50);


//0 - 359 - 719  (range[])

  if(last_range == 0){
     last_range = scanner_->ranges[0];
  }

  double jump_range = 999;
  double angle = 0;

  int range_id = 0; 

  double min_dist = 0;
  
	//left or right edge of the cone depends on passing it left or right 
  if(mode){
	min_dist = 0.8;
  }else{
	min_dist = -0.8;
  }

	//find the edge of the nearest cone
  for(int j = 0; j < 719; j++){
    	//std::cout << "range: " << j << "  distanz: " << scanner_->ranges[j] << "\n";
      if((scanner_->ranges[j] - last_range) > 0.8 ){

		    	//std::cout << "last_range: " << last_range << "\n";

	  if(last_range < jump_range){
	    
	    jump_range = last_range;
	    range_id = j-1;
	  }
	  
      }
     last_range = scanner_->ranges[j];
  }
  
	//get the angel from lazer_scanner to cone
  angle = range_id * 180 / 719;
	
//std::cout << "\n\n";
	std::cout << "Winkel: " << angle << "  distanz: " << jump_range << "\n";
  
	//If a cone has been passed
  if(angle > 175){
	mode = 1;
  }
  if(angle < 5){
	mode = 0;
  }

	//mode = true => links ausweichen / mode = fals => rechts ausweichen
  if(mode){
	steer = angle / 180 * steer_factor;
  }else{
	steer = (angle - 180) / 180 * steer_factor;
  }
  
    lenkung.data = steer; // -1 < steer < 1 / von rechts nach links

   


}



int main(int argc, char **argv){

    ros::init(argc,argv,"cone");
ros::NodeHandle nh;
   
    

    ros::Subscriber cone_sub = nh.subscribe("/scan",10000,laser_Callback);
 ros::Publisher cone_pub=nh.advertise<std_msgs::Float64>("cone_cone",1000);
    
ros::Rate loop_rate(50);
while(ros::ok()){ 
 cone_pub.publish(lenkung);


   // ros::sleep();
    ros::spinOnce();
    loop_rate.sleep();
   }
 //ros::spin();
    return 0;
}
