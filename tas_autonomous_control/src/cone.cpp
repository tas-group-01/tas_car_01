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

   

//std::cout << "Lenkung: "<< lenkung << '\n'; 
  
/*
   summe_cone_rechts = 0;
   summe_cone_links = 0;
   summe_cone_vorne = 0;
   for (unsigned int i=309; i<409; ++i){
   summe_cone_rechts = summe_cone_rechts + scanner_ -> ranges[i-308];
   summe_cone_links = summe_cone_links + scanner_ -> ranges[i+309]; //scan from 690 to 710
   summe_cone_vorne = summe_cone_vorne + scanner_ -> ranges[i]; 
  }

int smallest_vorne = 9999;
for (int j = 310; j < 408; ++j) {
    if (scanner_ -> ranges[j] < smallest_vorne) {
        smallest_vorne = scanner_ -> ranges[j];
    }
}

int smallest_rechts = 9999;
for (int k = 310; k < 408; ++k) {
    if (scanner_ -> ranges[k-308] < smallest_rechts) {
        smallest_rechts = scanner_ -> ranges[k-308];
    }
}

int smallest_links = 9999;
for (int l = 310; l < 408; ++l) {
    if (scanner_ -> ranges[l+308] < smallest_links) {
        smallest_links = scanner_ -> ranges[l+308];
    }
}

std::cout <<"Vorne: "<< smallest_vorne <<"\n";
std::cout <<"Rechts: "<< smallest_rechts <<"\n";
std::cout <<"Links: " << smallest_links << "\n";



/*   
//1.)
   if (summe_cone_vorne < 50){
       first_cone = 1;   //reached first cone     
       }
//2.)   
   if ((summe_cone_rechts < 50) && (summe_cone_links < 30)) {
      cone_on_right = 1;    
      cone_on_left = 0;
     }

 
   if ((summe_cone_links < 50) && (summe_cone_rechts < 30)) {
      cone_on_left = 1;   
      cone_on_right = 0;
     }*/
//3.)
   /*std::cout << "Links: " << summe_cone_links <<' '<< "Vorne: " << summe_cone_vorne << ' ' << "Rechts: " << summe_cone_rechts << '\n';
   std::cout <<"first_cone: "<< first_cone <<"\n";
   std::cout << "cone_on_left: "<< cone_on_left  <<"\n";
   std::cout << "cone_on_right: "<< cone_on_right <<"\n";
   //std::cout << "cone_on_rigt in array: " << "\n"; 
*/


   //array_.data.clear();
   //array_.data.push_back(first_cone);
   //array_.data.push_back(cone_on_right);
   //array_.data.push_back(cone_on_left);
   


  /*  int co = 0;
     while (ros::ok())
{    
   
     ros::spinOnce();
     loop_rate.sleep();
     ++co;
}*/

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
