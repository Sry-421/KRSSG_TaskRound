#!/usr/bin/env python
#!/usr/bin/env python

import sys
import rospy
from turtlesim.srv import *
from std_srvs.srv import *
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from math import atan2, sqrt, pow

################################################################################

def update_pose(data):
	global current_pos
	current_pos=data

rospy.init_node('turtle_controller',anonymous='True')
velocity_publisher=rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)
pose_subscriber   =rospy.Subscriber('/turtle1/pose',Pose,update_pose)
rate=rospy.Rate(10)

################################################################################

current_pos=Pose()
vel_msg=Twist()
start_point=Pose()
next_point=Pose()
vel_magn =2
avel_magn=2
tolerance=0.01

################################################################################



def distance(point1,point2):
	return sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2))

def dist(point1):
	global current_pos
	return sqrt(pow(point1.x-current_pos.x,2)+pow(point1.y-current_pos.y,2))


def P_value_linear(start_point,next_point):
	global current_pos
	return (dist(next_point)/distance(next_point,start_point))
	


def P_value_angular(start_theta,next_theta):
	global current_pos
	current_theta=current_pos.theta
	value=(next_theta-current_theta)
	return value	

def cal_angle(start_point,next_point):
	return atan2(next_point.y-start_point.y,next_point.x-start_point.x)

##################################################################################

def move(start_point,next_point):
	global current_pos

	steer_angle=cal_angle(start_point,next_point)

	while (abs(current_pos.theta-steer_angle)>tolerance/100):


		P_value=P_value_angular(start_point.theta,steer_angle)

		direction=0.0

		if current_pos.theta > steer_angle:
			direction=1
		else:
			direction= 1

		vel_msg.linear.x=0
		vel_msg.linear.y=0
		vel_msg.linear.z=0

		vel_msg.angular.x=0
		vel_msg.angular.y=0
		vel_msg.angular.z=direction*avel_magn*P_value

		velocity_publisher.publish(vel_msg)

		rate.sleep()

	vel_msg.linear.x=0
	vel_msg.linear.y=0
	vel_msg.linear.z=0

	vel_msg.angular.x=0
	vel_msg.angular.y=0
	vel_msg.angular.z=0

	velocity_publisher.publish(vel_msg)	


	while(dist(next_point)>tolerance):

		
		P_value=P_value_linear(start_point,next_point)

		direction=0.0

		if current_pos.x > next_point.x:
			direction=1
		else:
			direction= 1

		vel_msg.linear.x=direction*vel_magn*P_value
		vel_msg.linear.y=0
		vel_msg.linear.z=0

		vel_msg.angular.x=0
		vel_msg.angular.y=0
		vel_msg.angular.z=0

		velocity_publisher.publish(vel_msg)

		rate.sleep()

	vel_msg.linear.x=0
	vel_msg.linear.y=0
	vel_msg.linear.z=0

	vel_msg.angular.x=0
	vel_msg.angular.y=0
	vel_msg.angular.z=0

	velocity_publisher.publish(vel_msg)	

##############################################################################


if __name__ == '__main__':
	
	
	print "Move the turtle"
	file =open("/home/sriyash/KRSSG/task/data.txt","r")
	count=int(file.readline())

	start_point.x=float(file.readline())
	start_point.y=float(file.readline())
	count=count-1

	rospy.wait_for_service('/turtle1/teleport_absolute')
	begin=rospy.ServiceProxy('/turtle1/teleport_absolute',TeleportAbsolute)
	begin(start_point.x,start_point.y,0)
	print "Teleporting to (%f,%f)"%(start_point.x,start_point.y)
	rospy.wait_for_service('/clear')
	clear_screen=rospy.ServiceProxy('/clear',Empty)
	clear_screen()

	while count > 0:
		next_point.x=float(file.readline())
		next_point.y=float(file.readline())
		print "Moving from (%f,%f) to (%f,%f)"%(start_point.x,start_point.y,next_point.x,next_point.y)
		move(start_point,next_point)
		#rate.sleep()
		print "Moved from (%f,%f) to (%f,%f)"%(start_point.x,start_point.y,current_pos.x,current_pos.y)
		start_point.x=next_point.x
		start_point.y=next_point.y
		count=count-1
		
