#include "ros/ros.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "actionlib/client/simple_action_client.h"
#include "std_msgs/Int8.h"
#include <vector>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  // Node Handle for communication
  ros::NodeHandle n;

  // Publisher to let us know if the robot made it to the goal location
  ros::Publisher robot_pub = n.advertise<std_msgs::Int8>("reached_goal", 1);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  
  std::vector<std::vector<float>> pos_arr;
  pos_arr = {{-3.0,-1.0,-0.7, 0.7},
             {-3.0,-4.0,-0.7, 0.7},
             {-3.0,-1.0, 0.0, 1.0},
             { 2.6,-1.3, 0.7, 0.7},
             { 2.6, 1.8, 0.7, 0.7},
             { 2.6,-1.3, 1.0, 0.0},};

  while(ros::ok)
  {
    for (int i=0; i<pos_arr.size(); i++)
    {
      goal.target_pose.pose.position.x = pos_arr[i][0];
      goal.target_pose.pose.position.y = pos_arr[i][1];
      goal.target_pose.pose.orientation.z = pos_arr[i][2];
      goal.target_pose.pose.orientation.w = pos_arr[i][3];

      // Send the goal position and orientation for the robot to reach
      if (i==1 or i==4)
      {
        ROS_INFO("Sending goal");
      }
      else
      {
        ROS_INFO("Sending to intermediate location");
      }
      ac.sendGoal(goal);

      // Wait an infinite time for the results
      ac.waitForResult();

      std_msgs::Int8 msg;
      msg.data = i+1;
      robot_pub.publish(msg);
      // ROS_INFO("I'm at position # %d", msg.data);

      // Check if the robot reached its goal
      if (i==1)
      {
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
          ROS_INFO("Hooray, the robot moved to first goal position");
        else
          ROS_INFO("The robot failed to move to the commanded location for some reason");
      
        sleep(5);
      }
      else if (i==4)
      {
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
          ROS_INFO("Hooray, the robot moved to second goal position");
        else
          ROS_INFO("The robot failed to move to the commanded location for some reason");
      
        sleep(5);
      }
    }
  }

  return 0;
}
