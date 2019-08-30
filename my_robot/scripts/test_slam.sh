#!/bin/sh
xterm  -e  " roslaunch ~/workspace/catkin_ws/src/my_robot/launch/world.launch " &
sleep 2
xterm  -e  " roslaunch ~/workspace/catkin_ws/src/my_robot/launch/mapping.launch " & 
sleep 2
xterm  -e  " roslaunch ~/workspace/catkin_ws/src/my_robot/launch/teleop.launch "
# sleep 2
# xterm  -e  " roslaunch ~/workspace/catkin_ws/src/my_robot/launch/amcl.launch "
