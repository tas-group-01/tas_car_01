#include "ros/ros.h"
#include <move_base_msgs/MoveBaseActionFeedback.h>
#include <math.h>
#include <geometry_msgs/Twist.h>
float minDistance = 2.0;
bool used = false; 
//---- Point coming from another node
geometry_msgs::Point actualPoint;
//---- Given start point
geometry_msgs::Point startPoint;
/**
* Callback function to receive the current position from the move_base node
*/
void moveBaseCallback(const move_base_msgs::MoveBaseActionFeedbackConstPtr& msg)
{
actualPoint = msg->feedback.base_position.pose.position;
}
/**
* Main function
*/
int main(int argc, char **argv)
{
ros::init(argc, argv, "start_velocity");
ros::NodeHandle nh;
//--- set up subscriber and publisher TODO: add 2nd subscriber about free front space
ros::Subscriber start_sub = nh.subscribe("move_base/feedback",500, moveBaseCallback);
ros::Publisher car_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 100);
//---- Frequency for while-loop 50Hz
ros::Rate loop_rate(50);
int count = 0;
while (ros::ok())
{
//---- set start position TODO: set coordinates
startPoint.x=0.0;
startPoint.y=0.0;
startPoint.z=0.0;
//---- set car velocity
geometry_msgs::Twist carVelocity;
carVelocity.linear.x= 1.5;
//---- calculate distance betewenn start and actual position
float distance = sqrt(pow((startPoint.x - actualPoint.x),2) + pow((startPoint.y - actualPoint.y),2) + pow((startPoint.z - actualPoint.z),2));
if((distance < minDistance) && (used == false) /*TODO: && (spaceFree == true)*/)
{
//--- publish mesage for topic cmd_vel
car_vel_pub.publish(carVelocity);
std::cout << "Robot starting" << "\n"; //ROS_INFO("Robot starting");
used = true;
}
std::cout << distance << "\n"; //ROS_INFO("distance = %f", distance);
//---- Function for subscription and using of callBack
ros::spinOnce(); // Check also ros::spin() instead
loop_rate.sleep();
++count;
}
return 0;
=======


/**
 * Callback function to receive the current position from the move_base node
 */
void moveBaseCallback(const move_base_msgs::MoveBaseActionFeedbackConstPtr& msg)
{

   actualPoint = msg->feedback.base_position.pose.position; 
     
}


/**
 * Main function
 */
int main(int argc, char **argv)
{

  ros::init(argc, argv, "start_velocity");

  ros::NodeHandle nh;
  
  //--- set up subscriber and publisher TODO: add 2nd subscriber about free front space
  ros::Subscriber start_sub = nh.subscribe("move_base/feedback",500, moveBaseCallback);
  ros::Publisher car_vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 100);

  //---- Frequency for while-loop 50Hz
  ros::Rate loop_rate(50);

  int count = 0;
  while (ros::ok())
  {
   
   //---- set start position TODO: set coordinates
   startPoint.x=0.0;
   startPoint.y=0.0;
   startPoint.z=0.0;

   //---- set car velocity
   geometry_msgs::Twist carVelocity;
   carVelocity.linear.x= 1.5;
  
   


   //---- calculate distance betewenn start and actual position
   float distance = sqrt(pow((startPoint.x - actualPoint.x),2) + pow((startPoint.y - actualPoint.y),2) + pow((startPoint.z - actualPoint.z),2));

   if((distance < minDistance) && (used == false) /*TODO: && (spaceFree == true)*/)
   {
      
        //--- publish mesage for topic cmd_vel 
        car_vel_pub.publish(carVelocity);
        
	std::cout << "Robot starting" << "\n"; //ROS_INFO("Robot starting");

	used = true;

   }


    std::cout << distance << "\n"; //ROS_INFO("distance = %f", distance); 


    //---- Function for subscription and using of callBack
    ros::spinOnce(); // Check also ros::spin() instead

    loop_rate.sleep(); 

    ++count;

  }

  return 0;

>>>>>>> c37784ec18256bd9cfcff7184c65c9e23601bcfd
}
