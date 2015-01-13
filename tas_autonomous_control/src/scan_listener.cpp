#include <ros/ros.h>
#include <stdio.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include <sstream>



#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
//#include "control/control.h"
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



void scan_Callback2(const sensor_msgs::LaserScan::ConstPtr& scanner_){
  
    ros::Rate loop_rate(50.0);
    ros::NodeHandle nh;
    
    double wert_1 = scanner_ -> ranges[1];
    double wert_2 = scanner_ -> ranges[400];
    double wert_3 = scanner_ -> ranges[600];

    ROS_INFO("Erste 3 Array-Elemente: (%f, %f, %f,)", wert_1, wert_2, wert_3);
/*
    int counter=0;
    while (ros::ok()){
    
    std::cout<< "1.tes Element " << scanner_ -> intensities[1] << ", 2.tes Element " << scanner_ -> intensities[2] << ", 3.tes Element, " << scanner_ -> intensities[3] << "\n";
    //hier könnte man Parameter setzen und publishen
    ros::spinOnce();
    loop_rate.sleep();
    ++counter;
    std::cout << "while-Schleife: " << counter << "\n";
    }*/
} 



int main(int argc, char** argv) 
{

    ros::init(argc, argv, "scan_listener");
    ros::NodeHandle nh;
    int zzz = 0;
    
    ros::Subscriber sub_ = nh.subscribe("/scan",100,scan_Callback2);

    ++zzz;
    std::cout<<"main-Funktion: " << zzz << "\n";

    ros::spin();

    return 0;

}
