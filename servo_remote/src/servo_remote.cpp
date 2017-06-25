#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <stdio.h>
#include <dji_sdk/dji_drone.h>
#include <cstdlib>
#include <stdlib.h>
std_msgs::Int32 servo_msg;

void servoCallback(const dji_sdk::RCChannels& msg)
{
	//printf("gear: %f\n", msg.gear);
	if(msg.gear<=-5000)
	{	
		servo_msg.data=1;
	}
	else
	{
		servo_msg.data=100;
	}
	printf("mode: %d\n", servo_msg.data);
	
}

int main(int argc, char **argv)
{
ros::init(argc,argv,"servo_remote");
ros::NodeHandle node;
ros::Publisher pub = node.advertise<std_msgs::Int32>("switch_servo", 10);
ros::Subscriber sub = node.subscribe("dji_sdk/rc_channels", 10, servoCallback);
while(1)
{	
	ros::spinOnce();  
	pub.publish(servo_msg);
}
}
