#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <stdio.h>
#include <dji_sdk/dji_drone.h>
#include <cstdlib>
#include <stdlib.h>
class Servo_Remote_Class
{
Servo_Remote_Class()
{
	pub = node.advertise<std_msgs::Int32>("switch_servo", 1);	
	sub = node.subscribe("dji_sdk/rc_channels", 1, servoCallback);
}

void servoCallback(const dji_sdk::RCChannels& msg)
{
	std_msgs::Int32 servo_msg;
	if(msg.gear<=-5000)
	{	
		servo_msg.data=1;
	}
	else
	{
		servo_msg.data=100;
	}
	printf("mode: %d\n", servo_msg.data);
	pub.publish(servo_msg);
	
}

private:
	ros::NodeHandle node;
	ros::Publisher pub;
	ros::Subscriber sub;
}



int main(int argc, char **argv)
{
ros::init(argc,argv,"servo_remote");
ros::Rate rate(20);
while(1)
{
	rate.sleep();
	ros::spinOnce();
}
return 0;
}
