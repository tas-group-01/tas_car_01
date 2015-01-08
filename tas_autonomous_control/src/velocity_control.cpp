#include <ros/ros.h>

#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include <math.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <iostream>

geometry_msgs::Point slamPoint;
geometry_msgs::Point goalPoint;
void setslam(const geometry_msgs::PoseStampedConstPtr& smsg){
     slamPoint= smsg->pose.position;
}

void setgoal(const geometry_msgs::PoseStampedConstPtr& gmsg){
goalPoint =gmsg->pose.position;
}

void ComboCallback(const geometry_msgs::PoseStampedConstPtr& smsg,const geometry_msgs::PoseStampedConstPtr& gmsg, ros::Publisher *pub){
    //geometry_msgs::Point goalPoint = gmsg->pose.position;
    //geometry_msgs::Point slamPoint = smsg->pose.position;
std_msgs::Float32 answer;
    float distance = sqrt(pow((goalPoint.x - slamPoint.x),2) + pow((goalPoint.y - slamPoint.y),2) + pow((goalPoint.z - slamPoint.z),2));
        if(distance > 3){
	answer.data=1.5;
        }else{
	answer.data=(distance / 3) + 0.5;
        }
pub->publish(answer);
std::cout << "Should have published\n";

}

int main(int argc, char **argv){

    ros::init(argc,argv,"velocity_control");

    ros::NodeHandle nh;
    ros::Publisher velocity_pub = nh.advertise<std_msgs::Float32>("vel_factor",100);

    ros::Rate loop_rate(50);

/* Saubere Variante die nicht funktioniert...
	message_filters::Subscriber<geometry_msgs::PoseStamped> slamsub(nh,"slam_out_pose",100);
	message_filters::Subscriber<geometry_msgs::PoseStamped> goalsub(nh,"curtarget",100);
	typedef message_filters::sync_policies::ApproximateTime<geometry_msgs::PoseStamped,geometry_msgs::PoseStamped> mysync;
	message_filters::Synchronizer<mysync> sync(mysync(100),slamsub,goalsub);
	sync.registerCallback(boost::bind(&ComboCallback, _1, _2, &velocity_pub));
*/




    while(ros::ok()){

std_msgs::Float32 answer;
    float distance = sqrt(pow((goalPoint.x - slamPoint.x),2) + pow((goalPoint.y - slamPoint.y),2) + pow((goalPoint.z - slamPoint.z),2));
        if(distance > 3){
	answer.data=1.5;
        }else{
	answer.data=(distance / 3) + 0.5;
        }

	velocity_pub.publish(answer);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
