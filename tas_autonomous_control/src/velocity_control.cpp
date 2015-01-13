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

geometry_msgs::Point slamPoint;
geometry_msgs::Point last_goalPoint;
geometry_msgs::Point goalPoint;

void setslam(const move_base_msgs::MoveBaseActionFeedbackConstPtr& smsg){
    slamPoint = smsg->feedback.base_position.pose.position;
}

void setgoal(const geometry_msgs::PoseStampedConstPtr& gmsg){
    if((goalPoint.x != gmsg->pose.position.x) && (goalPoint.x != gmsg->pose.position.x))
        last_goalPoint = goalPoint;

    goalPoint = gmsg->pose.position;

    //std::cout << "goal: " << goalPoint << "  last goal: " << last_goalPoint << "\n";
}
/*
void ComboCallback(const geometry_msgs::PoseStampedConstPtr& smsg,const geometry_msgs::PoseStampedConstPtr& gmsg, ros::Publisher *pub){
    //geometry_msgs::Point goalPoint = gmsg->pose.position;
    //geometry_msgs::Point slamPoint = smsg->pose.position;
    double answer;
    float distance = sqrt(pow((goalPoint.x - slamPoint.x),2) + pow((goalPoint.y - slamPoint.y),2) + pow((goalPoint.z - slamPoint.z),2));
    if(distance > 3){
        answer=1.5;
    }else{
        answer=(distance / 3) + 0.5;
    }
    pub->publish(answer);
    std::cout << "Should have published\n";

}
*/

double factor(float distance){
    double fac = -0.6/121.0 *(distance*distance)+1.9;
    return fac ?  fac > 0 : 1.3;
}

int main(int argc, char **argv){
    ros::init(argc,argv,"velocity_control");
    float distance_to_current=0;
    float distance_to_last=0;

    ros::NodeHandle nh;
    ros::Subscriber sub_slam = nh.subscribe("move_base/feedback",500,setslam);
    ros::Subscriber sub_goal = nh.subscribe("curtarget",500,setgoal);
    ros::Publisher velocity_pub = nh.advertise<std_msgs::Float64>("vel_factor",100);

    ros::Rate loop_rate(50);

    tf::TransformListener listener;

/* Saubere Variante die nicht funktioniert...
	message_filters::Subscriber<geometry_msgs::PoseStamped> slamsub(nh,"slam_out_pose",100);
	message_filters::Subscriber<geometry_msgs::PoseStamped> goalsub(nh,"curtarget",100);
	typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::PoseStamped,geometry_msgs::PoseStamped> mysync;
	message_filters::Synchronizer<mysync> sync(mysync(100),slamsub,goalsub);
	sync.registerCallback(boost::bind(&ComboCallback, _1, _2, &velocity_pub));
*/

   // ros::Rate rate(50.0);


    while(ros::ok()){

       /* tf::StampedTransform slam_transform;

        try{
            listener.lookupTransform("/base_link","map",ros::Time(0),slam_transform);
        }
        catch (tf::TransformException ex){
              ROS_ERROR("%s",ex.what());
              ros::Duration(1.0).sleep();
        }
        */

        std_msgs::Float64 answer;
        //float distance = sqrt(pow((goalPoint.x - slamPoint.x),2)
        //                    + pow((goalPoint.y - slamPoint.y),2));
        distance_to_current = sqrt(pow((goalPoint.x - slamPoint.x),2)
                              + pow((goalPoint.y - slamPoint.y),2));
       if(last_goalPoint.x != 0 && last_goalPoint.x !=0){//on our map we cannot get into the corners
        distance_to_last= sqrt(pow((last_goalPoint.x - slamPoint.x),2)
                              + pow((last_goalPoint.y - slamPoint.y),2));
        }

       std::cout << "distance_to_current: " << distance_to_current << "distance_to_last" << distance_to_last << "\n";

        //since we cannot go into the corners, we check like this
        answer.data = factor(distance_to_current)? (distance_to_current < distance_to_last || last_goalPoint.x ==0) : factor(distance_to_last);
        if (last_goalPoint.x == 0 && goalPoint.x == 0){//no goal yet
            answer.data = 0;
        }


            //std::cout << distance << "\n";


        velocity_pub.publish(answer);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
