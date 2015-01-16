#ifndef CONTROL_H
#define CONTROL_H

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float64.h"

#include "std_msgs/Int16MultiArray.h"

#include <math.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Int8.h>

#define PI                     3.14159265
#define CAR_LENGTH              0.355
#define SCALE_FAKTOR_STEERING   500

class control
{
public:
    control();

    ros::NodeHandle nh_;
    ros::Publisher control_servo_pub_;
    ros::Subscriber cmd_sub_;
    ros::Subscriber odom_sub_;
    ros::Subscriber wii_communication_sub;
    ros::Subscriber VelFac_sub;
    ros::Subscriber Area_sub;
    ros::Subscriber Scan_sub;
    ros::Subscriber Cone_sub;
   /* ros::Subscriber sub; nicht hier deklarieren sondern in main*/
  /*  ros::Subscriber pos_sub; */

    std_msgs::Int16 control_Brake; /* flag for brake */
    std_msgs::Int16 control_Mode; /* flag for car mode: manual or autonomous */

    double cmd_linearVelocity;
    double cmd_angularVelocity;
    double cmd_steeringAngle;

    double odom_linearVelocity;
    double odom_angularVelocity;
    double odom_steeringAngle;

    double vel_fac;
    int area_;
    double lenk;
    //geometry_msgs::PoseWithCovariance ort_y;
 
    double wert_winkel_1;
    double wert_winkel_2;

     float ort_y;
    float ort_x;
   int bereich;
      // ohne Initialisierung, beim launchen drauf achten, dass 
                   // die Position im autonomen Bereich, da sonst gleich beim Start Wert gespeichert bleibt
    

    geometry_msgs::Vector3 control_servo;

 

private:
    /* subscribe the cmd message from move_base */
    void cmdCallback(const geometry_msgs::Twist::ConstPtr& msg);

    /* subscribe the virtual odom message as a feedback for controller */
    void odomCallback(const geometry_msgs::Twist::ConstPtr& msg);

    /* check the wii states and switch the flag for manual mode and autonomous mode */
    void wiiCommunicationCallback(const std_msgs::Int16MultiArray::ConstPtr& msg);

    void vel_factorCallback(const std_msgs::Float64ConstPtr& msg);

    void area_Callback(const std_msgs::Int8ConstPtr& msg);    

    //void position_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& ort_);
   /*listen to pose for acceleration*/
   
    void scan_Callback(const sensor_msgs::LaserScan::ConstPtr& scan_);
   /*listen to topic /scan */

   void steer_Callback(const std_msgs::Float64ConstPtr& msg);

};

#endif // CONTROL_H
