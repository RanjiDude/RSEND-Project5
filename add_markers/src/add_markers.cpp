#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "std_msgs/Int8.h"

int at_goal = 0;

void markerCallback(const std_msgs::Int8::ConstPtr& msg)
{
  at_goal = msg->data;
//   ROS_INFO("at_goal value = %d", at_goal);
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber marker_sub = n.subscribe("reached_goal", 1, markerCallback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    ros::spinOnce();

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 1;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -3.0;
    marker.pose.position.y = -4.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = -0.7;
    marker.pose.orientation.w = 0.7;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    if (at_goal == 1 or at_goal == 6)
    {
        marker.pose.position.x = -3.0;
        marker.pose.position.y = -4.0;
        marker.pose.orientation.z = -0.7;
        marker.pose.orientation.w = 0.7;
        marker.action = visualization_msgs::Marker::ADD;
    }
    else if (at_goal >=2 and at_goal <=4)
    {
        marker.action = visualization_msgs::Marker::DELETE;
    }
    else if (at_goal == 5)
    {
        marker.pose.position.x = 2.6;
        marker.pose.position.y = 1.8;
        marker.pose.orientation.z = 0.7;
        marker.pose.orientation.w = 0.7;
        marker.action = visualization_msgs::Marker::ADD;
    }

    marker_pub.publish(marker);
  }
}
