#include "control.h"
#include <iostream>
control::control()
{

control_servo_pub_ = nh_.advertise<geometry_msgs::Vector3>("servo", 1);
cmd_sub_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 1000, &control::cmdCallback,this);
odom_sub_ = nh_.subscribe<geometry_msgs::Twist>("odom_vel",1000,&control::odomCallback,this);
wii_communication_sub = nh_.subscribe<std_msgs::Int16MultiArray>("wii_communication",1000,&control::wiiCommunicationCallback,this);
Area_sub = nh_.subscribe<std_msgs::Int8>("area_area",1000,&control::area_Callback,this);
VelFac_sub = nh_.subscribe<std_msgs::Float64>("vel_factor",1000,&control::vel_factorCallback,this);

}

void control::odomCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
//distribute the world in severel areas to accomodate to the environment
switch (area_) {
case 1 : //Bereich an der Startposition -> selbständiges Beschleunigung
{odom_linearVelocity = 0.13;
odom_angularVelocity = msg->angular.z;
odom_steeringAngle = 180/PI*atan(odom_angularVelocity/odom_linearVelocity*CAR_LENGTH); 
odom_steeringAngle = 1500 + 500/30*odom_steeringAngle;
if(odom_steeringAngle > 2000)
{
odom_steeringAngle = 2000;
}
else if(odom_steeringAngle < 1000)
{
odom_steeringAngle = 1000;
}}
break;

default: //just drive
{ odom_linearVelocity = msg->linear.x * vel_fac + 0.08;
odom_angularVelocity = msg->angular.z;
odom_steeringAngle = 180/PI*atan(odom_angularVelocity/odom_linearVelocity*CAR_LENGTH);
odom_steeringAngle = 1500 + 500/30*odom_steeringAngle;
if(odom_steeringAngle > 2000)
{
odom_steeringAngle = 2000;
}
else if(odom_steeringAngle < 1000)
{
odom_steeringAngle = 1000;
}}
break;
}
}

void control::cmdCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
switch (area_) {
case 1: // area around the starting position -> acceleration
{cmd_linearVelocity = 0.13;
cmd_angularVelocity = msg->angular.z;

cmd_steeringAngle = 180/PI*atan(cmd_angularVelocity/cmd_linearVelocity*CAR_LENGTH);
cmd_steeringAngle = 1500 + 500/30*cmd_steeringAngle;
if(cmd_steeringAngle > 2000)
{
cmd_steeringAngle = 2000;
}
else if(cmd_steeringAngle < 1000)
{
cmd_steeringAngle = 1000;
}}
break;

default: //just drive
{cmd_linearVelocity = msg->linear.x * vel_fac + 0.08;//vel_fac; //increase velocity
cmd_angularVelocity = msg->angular.z;

cmd_steeringAngle = 180/PI*atan(cmd_angularVelocity/cmd_linearVelocity*CAR_LENGTH);
cmd_steeringAngle = 1500 + 500/30*cmd_steeringAngle;
if(cmd_steeringAngle > 2000)
{
cmd_steeringAngle = 2000;
}
else if(cmd_steeringAngle < 1000)
{
cmd_steeringAngle = 1000;
}}
break;
}
}
// a flag method that tells us if we are controlling the car manually or automatically
void control::wiiCommunicationCallback(const std_msgs::Int16MultiArray::ConstPtr& msg)
{
control_Mode.data = msg->data[0];
control_Brake.data = msg->data[1];
}
//vel_fac published of node velocity_control2 
void control::vel_factorCallback(const std_msgs::Float64ConstPtr& msg){
vel_fac = msg->data;
}
//Every area_ has his own interger-value definde definded in node area
void control::area_Callback(const std_msgs::Int8ConstPtr& msg){
area_ = msg->data;
}

