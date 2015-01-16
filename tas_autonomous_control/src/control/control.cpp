#include "control.h"
#include <iostream>
  
control::control()
{
     //Ort_sub = nh_.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",0.2,&control::position_Callback,this);

   
   control_servo_pub_ = nh_.advertise<geometry_msgs::Vector3>("servo", 1);

    cmd_sub_ = nh_.subscribe<geometry_msgs::Twist>("cmd_vel", 1000, &control::cmdCallback,this);

    odom_sub_ = nh_.subscribe<geometry_msgs::Twist>("odom_vel",1000,&control::odomCallback,this);

    wii_communication_sub = nh_.subscribe<std_msgs::Int16MultiArray>("wii_communication",1000,&control::wiiCommunicationCallback,this);

    //Area_sub = nh_.subscribe<std_msgs::Int8>("area_area",1000,&control::area_Callback,this);
 
    VelFac_sub = nh_.subscribe<std_msgs::Float64>("vel_factor",1000,&control::vel_factorCallback,this);

    Cone_sub = nh_.subscribe<std_msgs::Float64>("cone_cone",1000,&control::steer_Callback,this);

   

    //Bereich_sub = nh_.subscribe<
  

 // update vel_factor   pos_sub = nh_.subscribe<geometry_msgs::PoseWithCovarianceStamped>("vel_factor".1000,&control::Callback2,this);

//    Fp = 10;// need to test! defult:125

//    current_ServoMsg.x = 1500;
//    current_ServoMsg.y = 1500;

//    previous_ServoMsg.x = 1500;
//    previous_ServoMsg.y = 1500;

}
// We can subscribe to the odom here and get some feedback signals so later we can build our controllers

 


void control::odomCallback(const geometry_msgs::Twist::ConstPtr& msg)
{

odom_linearVelocity = 0.12;//lenk;//0.12;//vel_fac; //increase velocity
    
    //odom_angularVelocity = msg->angular.z;

   odom_steeringAngle = 1500 + 500*lenk;
    //std::cout<<"vel_fac: "<<  vel_fac << "\n";
    //std::cout<<"Ort_y: "<<  ort_y << "\n";

 /* if ((ort_y > 17 ) && (ort_x < 7)){
     bereich = 1;
    }
   else if ((ort_y < 5) && (ort_x < 7)){
     bereich = 2;
     }
   else if((ort_y < 5) && (ort_y > 17)){
     bereich = 3;
     }
    else bereich = 0; *//*
   

//bereich = 1; 

area_ = 1;

switch (area_) {

    case 1 :  //Bereich an der Startposition -> selbständige Beschleunigung
    {odom_linearVelocity = 0.12;//lenk;//0.12;//vel_fac; //increase velocity
    
    odom_angularVelocity = msg->angular.z;

   odom_steeringAngle = 1500 + 500*lenk;

    /*odom_steeringAngle = 180/PI*atan(odom_angularVelocity/odom_linearVelocity*CAR_LENGTH); //könnte man evtl auch festsetzen

    odom_steeringAngle = 1500 + 500/30*odom_steeringAngle;

    if(odom_steeringAngle > 2000)
    {
        odom_steeringAngle = 2000;
    }
    else if(odom_steeringAngle < 1000)
    {
        odom_steeringAngle = 1000;
    }*//*}
    break;

    case 2:   // if the robot passes this area succefully then leave the parameters alone
    {odom_linearVelocity = 0.10;//msg->linear.x * vel_fac;//vel_fac; //increase velocity
    
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

    case 3:  // now we have to adjust the parameters in respect to the robot passing the tight door
    {odom_linearVelocity = 0.13;//vel_fac; //increase velocity
    
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

    case 4:  // now we have to adjust the parameters in respect to the robot passing the tight door
    {odom_linearVelocity = 0.09;//vel_fac; //increase velocity
    
    odom_angularVelocity = msg->angular.z;

    odom_steeringAngle = 1699;//180/PI*atan(odom_angularVelocity/odom_linearVelocity*CAR_LENGTH);

    odom_steeringAngle =1699; //1500 + 500/30*odom_steeringAngle;

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
   { odom_linearVelocity = msg->linear.x * vel_fac;//vel_fac; //increase velocity
    
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
 */   
}

//Subscribe to the local planner and map the steering angle (and the velocity-but we dont do that here-) to pulse width modulation values.
void control::cmdCallback(const geometry_msgs::Twist::ConstPtr& msg)
{  
cmd_linearVelocity =0.12; //lenk;
cmd_steeringAngle = 1500 + 500*lenk;
/*
area_=1;

//bereich = 1;  

switch (area_) {
    
     case 1:   // area around the starting position -> autonomous acceleration
    {cmd_linearVelocity =0.12; //lenk; //0.12;//vel_fac; //increase velocity
     
    cmd_angularVelocity = msg->angular.z;

   // std::cout << "vel_fac" << vel_fac << "\n";

   cmd_steeringAngle = 1500 + 500*lenk;
    /*cmd_steeringAngle = 180/PI*atan(cmd_angularVelocity/cmd_linearVelocity*CAR_LENGTH);

    cmd_steeringAngle = 1500 + 500/30*cmd_steeringAngle;

    if(cmd_steeringAngle > 2000)
    {
        cmd_steeringAngle = 2000;
    }
    else if(cmd_steeringAngle < 1000)
    {
        cmd_steeringAngle = 1000;
    }*//*}
    break;

    case 2: // if the robot passes succesfully leave this parameters alone
    {cmd_linearVelocity = 0.10; //msg->linear.x * vel_fac;//vel_fac; //increase velocity
     
    cmd_angularVelocity = msg->angular.z;

   // std::cout << "vel_fac" << vel_fac << "\n";


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

    case 3:// now we have to adjust the parameters in respect to the robot passes the tight door
    {cmd_linearVelocity = 0.13;//vel_fac; //increase velocity
     
    cmd_angularVelocity = msg->angular.z;

   // std::cout << "vel_fac" << vel_fac << "\n";


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

    case 4:// now we have to adjust the parameters in respect to the robot passes the tight door
    {cmd_linearVelocity = 0.09;//vel_fac; //increase velocity
     
    cmd_angularVelocity = msg->angular.z;

   // std::cout << "vel_fac" << vel_fac << "\n";


    cmd_steeringAngle = 1699;//180/PI*atan(cmd_angularVelocity/cmd_linearVelocity*CAR_LENGTH);

    cmd_steeringAngle = 1699;//1500 + 500/30*cmd_steeringAngle;

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
    {cmd_linearVelocity = msg->linear.x * vel_fac;//vel_fac; //increase velocity
     
    cmd_angularVelocity = msg->angular.z;

   // std::cout << "vel_fac" << vel_fac << "\n";


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

*/
 

}
// a flag method that tells us if we are controlling the car manually or automatically
void control::wiiCommunicationCallback(const std_msgs::Int16MultiArray::ConstPtr& msg)
{
    control_Mode.data = msg->data[0];
    control_Brake.data = msg->data[1];
}

//geometry_msgs::Vector3 control::P_Controller()
//{
//    current_ServoMsg.x = previous_ServoMsg.x + Fp*(cmd_linearVelocity - odom_linearVelocity);

//    current_ServoMsg.y = cmd_steeringAngle;


//    if(current_ServoMsg.x > 1580)
//    {
//        current_ServoMsg.x = 1580;
//    }
//    else if(current_ServoMsg.x < 1300)
//    {
//        current_ServoMsg.x = 1300;
//    }

//    if(current_ServoMsg.y > 2000)
//    {
//        current_ServoMsg.y = 2000;
//    }
//    else if(current_ServoMsg.y < 1000)
//    {
//        current_ServoMsg.y = 1000;
//    }

//    previous_ServoMsg = current_ServoMsg;

//    return current_ServoMsg;
//}


void control::vel_factorCallback(const std_msgs::Float64ConstPtr& msg){

    vel_fac = msg->data;
}


void control::area_Callback(const std_msgs::Int8ConstPtr& msg){
    area_ = msg->data;
}

 void control::steer_Callback(const std_msgs::Float64ConstPtr& msg){
  lenk = msg->data;
std::cout << "Schinken!!\n" << lenk;
cmd_linearVelocity =0.12; //lenk;
cmd_steeringAngle = 1500 + 500*lenk;

odom_linearVelocity =0.12; //lenk;
odom_steeringAngle = 1500 + 500*lenk; 
}



/*void control::position_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& ort_) {
 
   ort_y = ort_ -> pose.pose.position.y;
   ort_x = ort_ -> pose.pose.position.x;

      if ((ort_y > 17 ) && (ort_x < 7)){
     bereich = 1;
    }
   else if ((ort_y < 5) && (ort_x < 7)){
     bereich = 2;
     }
   else if((ort_y < 5) && (ort_y > 17)){
     bereich = 3;
     }
    else bereich = 0;

  if ((ort_y > 17 ) && (ort_x < 7)){
     bereich = 1;
    }
   else if ((ort_y < 5) && (ort_x < 7)){
     bereich = 2;
     }
   else if((ort_y < 5) && (ort_y > 17)){
     bereich = 3;
     }
    else bereich = 0; 
} */




