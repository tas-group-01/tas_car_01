#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include "process_laserscan_data/process_laserscan_data.h"

#include <math.h> 

using std::vector;
using std::cout;
using std::endl;

class BypassObstacle
{
private:
  ros::NodeHandle nh_;
  ros::Publisher cmd_vel_pub_;
  ros::Subscriber laser_sub;
  ros::Subscriber pose_sub;
  geometry_msgs::Twist base_cmd;
  
public:
//Constructor
  BypassObstacle(ros::NodeHandle &nh)
  {
    nh_ = nh;
    }
    
  int CheckForCollision(vector<float> data){
  
    int length=data.size();
    int i=0;
    int j=0;
    int flag=0; //indicates collision
    float d_min=0.2; //minimum distance to an obstacle
    float b=0.2; //width of the car 
    float phi=atan(2.0*d_min/b);
    float p=(phi/3.14)*length;
    int p2=ceil(p);
    float data_relevant[2*p2+1];
    
    for(i=0;i<=2*p2;i++){
      data_relevant[i]=data[length/2-p2+i];
    }
    
    int counter=0; //counts how many measurement points imply a critical distance to an obstacle
    
    for (j=0;j<=2*p2;j++){
      
      if (data_relevant[j]<=d_min){
        counter++;
      }
      
    }
    
    //if the minimum distance is undercut a critical amount of times, a near obstacle is assumed
    if (counter>3){
      flag=1; //it is very likely that an obstacle is right in front of the car
    }
    
     return flag;
   
  } 


  void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
  {    

    vector<float> data = scan->ranges;
    int length=data.size();
    
    int Collision=CheckForCollision(data);
    //write laserscan data to file
    laserscan_data_write(data,length);
  }

};

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "get_laserscan_data");
  ros::NodeHandle nh;
  BypassObstacle bypass(nh);
  ros::Subscriber laser_sub = nh.subscribe("scan", 1000, &BypassObstacle::laserCallback,&bypass);
  ros::spin();

}
