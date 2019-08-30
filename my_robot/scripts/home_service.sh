#!/bin/sh
xterm  -e  " roslaunch ~/workspace/catkin_ws/src/my_robot/launch/world.launch " &
sleep 2
xterm  -e  " roslaunch ~/workspace/catkin_ws/src/my_robot/launch/amcl.launch " &
sleep 2
xterm -e " rosrun add_markers add_markers " &
sleep 2
xterm -e " rosrun pick_objects pick_objects "