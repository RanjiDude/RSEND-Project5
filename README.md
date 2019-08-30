# RSEND-Project5
Home Service Robot - Programming a home service robot to autonomously map an environment and pickup and deliver objects

#### Packages used:
RTAB-Map (Real-Time Appearance-Based Mapping) - For mapping an environment and creating a database. This database was later used to generate a map file with the help of the rtabmap-databaseViewer.

teleop_twist_keyboard - To navigate the robot using keyboard keys.

AMCL (Adaptive Monte Carlo Localization) - For localizing the robot in an environment using the map genrated above.

add_markers - This package was created to simulate virtual objects on the map in RVIZ that the robot would "pick-up" and "drop-off".

pick_objects - This package was created to replicate the funtionality of the 2D Nav Goal command in RVIZ. It publishes different points on the map that the robot must travel to. In our case these positions happen to be where the virtual objects need to be "picked up" and "dropped off".

#### Instructions
1. To run the scripts, copy all the files into your catkin_ws/src folder.
1. Build the packages from the main workspace location with the catkin_make command.
1. You have to make the shell scripts executable first using the command: chmod +x add_markers.sh home_service.sh pick_objects.sh
1. Feel free to make your own shell scripts and add it to that list to make them executable.
1. You may run a particular script as follows: ./pick_objects.sh (OR) ./home_service.sh
