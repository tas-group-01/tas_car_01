#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <actionlib/client/simple_action_client.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
void prepareGoalList(std::vector<move_base_msgs::MoveBaseGoal>& goalList);
int main(int argc, char** argv){
ros::init(argc, argv, "set_goallist");
ros::NodeHandle n;
ros::Publisher curtarget_pub = n.advertise<geometry_msgs::PoseStamped>("curtarget",100);
MoveBaseClient ac("move_base", true);

while(!ac.waitForServer(ros::Duration(5.0))){
ROS_INFO("Waiting for the move_base action server to come up");
}
std::vector<move_base_msgs::MoveBaseGoal> goalList;
prepareGoalList(goalList);
while (n.ok())
{
for (std::vector<move_base_msgs::MoveBaseGoal>::iterator it = goalList.begin(); it != goalList.end() && n.ok(); ++it)
{
it->target_pose.header.stamp = ros::Time::now();
ROS_INFO("Sending goal");
ac.sendGoal(*it);
bool wait = true;
while (n.ok() && wait)
{
ac.waitForResult(ros::Duration(1));
curtarget_pub.publish(it->target_pose);
if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
{
wait = false;
ROS_INFO("Hooray, the base reached goal");
}
else
ROS_INFO("The base is still trying to reach the goal");
}
}
}
ac.cancelAllGoals();
return 0;
}
void prepareGoalList(std::vector<move_base_msgs::MoveBaseGoal>& goalList)
{
{
        /*
        //test
        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.pose.position.x = 1;
        goal.target_pose.pose.position.y = 1;
        goal.target_pose.pose.orientation.z = -0.61;
        goal.target_pose.pose.orientation.w = 0.79;
        goalList.push_back(goal);
        }*/

//unten links
move_base_msgs::MoveBaseGoal goal;
goal.target_pose.header.frame_id = "map";
goal.target_pose.pose.position.x = 10.4184093475;
goal.target_pose.pose.position.y = 9.0916;
goal.target_pose.pose.orientation.z = -0.7;
goal.target_pose.pose.orientation.w = 0.71;
goalList.push_back(goal);
}
//unten rechts
{
move_base_msgs::MoveBaseGoal goal;
goal.target_pose.header.frame_id = "map";
goal.target_pose.pose.position.x = 21.12;
goal.target_pose.pose.position.y = 5.97;
goal.target_pose.pose.orientation.z = 0;
goal.target_pose.pose.orientation.w = 0.99;
goalList.push_back(goal);
}

//unten mitte
{
move_base_msgs::MoveBaseGoal goal;
goal.target_pose.header.frame_id = "map";
goal.target_pose.pose.position.x = 17.58232;
goal.target_pose.pose.position.y = 6.24;
goal.target_pose.pose.orientation.z = 0.0;
goal.target_pose.pose.orientation.w = 1;
goalList.push_back(goal);
}


//oben rechts
{
move_base_msgs::MoveBaseGoal goal;
goal.target_pose.header.frame_id = "map";
goal.target_pose.pose.position.x = 23.536;
goal.target_pose.pose.position.y = 17.80;
goal.target_pose.pose.orientation.z = 0.76;
goal.target_pose.pose.orientation.w = 0.65;
goalList.push_back(goal);
}

    //nirvana
    {
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.pose.position.x = 99;
    goal.target_pose.pose.position.y = 99;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1;
    goalList.push_back(goal);
    }

}
