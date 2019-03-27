#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <sstream>
#include <iostream>
int main(int argc, char **argv)
{

	ros::init(argc, argv, "sterowanie");

	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

	ros::Rate loop_rate(10);
	
	geometry_msgs::Twist turtle_command;
	char comm;
	while (ros::ok())
	{

		ROS_INFO("\n w - forward \n a - left \n d - right \n s- back \n ctrl+C - quit \n");
		std::cin >> comm;
		ROS_INFO("You pressed %c \n", comm);
		switch(comm){
			case 'w':
				turtle_command.linear.x = 1.0;
				turtle_command.angular.z = 0.0;
			break;
			case 's':
				turtle_command.linear.x = -1.0;
				turtle_command.angular.z = 0.0;
			break;
			case 'a':
				turtle_command.linear.x = 0.0;
				turtle_command.angular.z = 1.5;
			break;
			case 'd':
				turtle_command.linear.x = 0.0;
				turtle_command.angular.z = -1.5;
			break;
			default:
				turtle_command.angular.z = 0.0;
				turtle_command.linear.x = 0.0;
			break;
		}
	

	chatter_pub.publish(turtle_command);

	ros::spinOnce();

	loop_rate.sleep();

	}


  return 0;
}

