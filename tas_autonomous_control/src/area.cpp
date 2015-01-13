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

 std_msgs::Int8 integer;

void positio_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& ort_) {

   ros::Publisher area_pub;
   ros::NodeHandle nh;
   area_pub=nh.advertise<std_msgs::Int8>("area_area",100);
   ros::Rate loop_rate(50);

      if ((ort_ -> pose.pose.position.y > 18 ) && (ort_ -> pose.pose.position.x < 13)){
     integer.data = 1;//oben rechts bis 1/4tel der Wegstrecke(Beschleunigen!)
    }
   else if ((ort_ -> pose.pose.position.y < 9) && (ort_ -> pose.pose.position.x < 13)){
     integer.data = 2;//unten links vor der Kurve(Langsam!)
     }
   else if((ort_ -> pose.pose.position.y < 8) && (ort_ -> pose.pose.position.x > 16)&&(ort_ -> pose.pose.position.x < 20)){
     integer.data = 3;//unten links nach der Kurve(Beschleunigen!)
     }
   else if((ort_ -> pose.pose.position.y < 8) && (ort_ -> pose.pose.position.x > 22)){
     integer.data = 4;//unten rechts vor der Kurve(Langsam!)
     }
 /*   else if((ort_ -> pose.pose.position.y > 8) && (ort_ -> pose.pose.position.x > 21)){
     integer.data = 5;//unten rechts nach der Kurve(Beschleunigen!)
     }*/

    else integer.data = 0;

   std::cout << "Ort x: "<< ort_ -> pose.pose.position.x <<"\n";

    int cou = 0;
     while (ros::ok())
{    
     area_pub.publish(integer);
     ros::spinOnce();
     loop_rate.sleep();
     ++cou;
}

}   


int main(int argc, char **argv){

    ros::init(argc,argv,"area");
    ros::Publisher area_pub;
    ros::NodeHandle nh;


    ros::Subscriber pos_sub = nh.subscribe("amcl_pose",500,positio_Callback);

    ros::spin();

    return 0;

}




 /*   ros::Publisher area_pub = nh.advertise<std_msgs::Int8>("area_area",100);
    ros::Rate loop_rate(50);

    //int berei = 1;

   while(ros::ok()){
   std_msgs::Int8 integer;
   integer.data=8;
   
   if ((Ort_y > 17 ) && (Ort_x < 7)){
     integer.data = 1;
    }
   else if ((Ort_y < 5) && (Ort_x < 7)){
     integer.data = 2;
     }
   else if((Ort_y < 5) && (Ort_y > 17)){
     integer.data = 3;
     }
    else integer.data = 0;

        //std::cout << "Area" << integer.data <<"\n";
        area_pub.publish(integer);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}*/
