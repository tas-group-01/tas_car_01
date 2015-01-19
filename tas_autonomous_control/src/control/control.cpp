#include "control.h"
#include <iostream>
  
control::control()
{   
   control_servo_pub_ = nh_.advertise<geometry_msgs::Vector3>("servo", 1);

    cmd_sub_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 1000, &control::cmdCallback,this);

    odom_sub_ = nh_.subscribe<geometry_msgs::Twist>("odom_vel",1000,&control::odomCallback,this);

    wii_communication_sub = nh_.subscribe<std_msgs::Int16MultiArray>("wii_communication",1000,&control::wiiCommunicationCallback,this);
 
    VelFac_sub = nh_.subscribe<std_msgs::Float64>("vel_factor",1000,&control::vel_factorCallback,this);

    Cone_sub = nh_.subscribe<std_msgs::Float64>("cone_cone",1000,&control::steer_Callback,this);

}

void control::odomCallback(const geometry_msgs::Twist::ConstPtr& msg)
{

odom_linearVelocity = 0.12;
    

   odom_steeringAngle = 1500 + 500*lenk;
  
}

//Subscribe to the local planner and map the steering angle (and the velocity-but we dont do that here-) to pulse width modulation values.
void control::cmdCallback(const geometry_msgs::Twist::ConstPtr& msg)
{  
cmd_linearVelocity =0.12; 
cmd_steeringAngle = 1500 + 500*lenk;


}
// a flag method that tells us if we are controlling the car manually or automatically
void control::wiiCommunicationCallback(const std_msgs::Int16MultiArray::ConstPtr& msg)
{
    control_Mode.data = msg->data[0];
    control_Brake.data = msg->data[1];
}


void control::vel_factorCallback(const std_msgs::Float64ConstPtr& msg){

    vel_fac = msg->data;
}


void control::area_Callback(const std_msgs::Int8ConstPtr& msg){
    area_ = msg->data;
}

 void control::steer_Callback(const std_msgs::Float64ConstPtr& msg){
  lenk = msg->data;
std::cout << "Schinken!!\n" << lenk;
cmd_linearVelocity =0.12; 
cmd_steeringAngle = 1500 + 500*lenk;

odom_linearVelocity =0.12; 
odom_steeringAngle = 1500 + 500*lenk; 
}









