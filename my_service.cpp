#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <sensor_msgs/LaserScan.h>
class Myservice
{ 
public:
	void cbCheckArrivalStatus_0(const move_base_msgs::MoveBaseActionResult rcvMoveBaseActionResult){
	if (rcvMoveBaseActionResult.status.status == 3)
    {
      state = false;
      ROS_INFO("arrive");
      i++;
      
    }
    else
    {
      ROS_INFO("cbCheckArrivalStatus_0 : %d", rcvMoveBaseActionResult.status.status);
    }
  }

void check_ranges(const sensor_msgs::LaserScan msg){
	i++;
	check = 0;
	for(int k=0;k<=360;k++){
       		if ((msg.ranges[k]<0.25)&&(msg.ranges[k]>0.1)) {
		check++;
		ROS_INFO("%d loop, value = %f",i,msg.ranges[k]);
      		ROS_INFO("wall close");
		state = false;
       		vel.linear.x = 0;}}


	if(check == 0) {state = true;}


	}	       

	

void go11()
{
	x = x - 0.3491;
	y = y -0.34;
	z++;
	
	
}

void go12()
{
	x = x - 0.3748;
	y = y + 0.25;
	ow = -0.5;
	count++;
	up = true;
	
}

void go21()
{
	x = x - 0.3491;
	y = y - 0.34;

	ow = 0.35;
	
	z++;
	
	
}

void go22()
{
	x = x + 0.3491;
	y = y + 0.34;
	
	ow = 0.35;
	
	z--;
	
}

void go31()
{
	x = x + 0.3491;
	y = y + 0.34;
	z--;
	
}

void go32()
{
	x = x - 0.3748;
	y = y + 0.25;
	
	ow = 2;
	
	
	up = false;
	
}


void fnPubPose()
{

if(state){
if( (count==3) && (z==3))
{ROS_INFO("everything is done");}
else
{pubPoseStampedTb3p.publish(poseStampedTable);
ROS_INFO("%dpose publish",i);}
}
else{
	if(up)
	{
	if(z<3){go11();}
	else if(z==3){go21();}
	else if(z==4) {go32();}
	
	}
	
	
	else
	{if(z>1){go31();}
	 else if(z==1){go22();}
	 else if(z==0){go12();}
	}
	
	fnInitParam();
	state = true;
	ROS_INFO("STATE CHANGE");
}
}


void fnInitParam()
{
poseStampedTable.header.seq = 0;
poseStampedTable.header.stamp.sec = 0;
poseStampedTable.header.stamp.nsec = 0;
poseStampedTable.header.frame_id = "map";

poseStampedTable.pose.position.x = x;
poseStampedTable.pose.position.y = y;
poseStampedTable.pose.position.z = 0;

poseStampedTable.pose.orientation.x = 0;
poseStampedTable.pose.orientation.y = 0;
poseStampedTable.pose.orientation.z = 1;
poseStampedTable.pose.orientation.w = ow;



/*
poseStampedTable[1].header.seq = 0;
poseStampedTable[1].header.stamp.sec = 0;
poseStampedTable[1].header.stamp.nsec = 0;
poseStampedTable[1].header.frame_id = "map";

poseStampedTable[1].pose.position.x = point[1][0];
poseStampedTable[1].pose.position.y = point[1][1];
poseStampedTable[1].pose.position.z = 0;

poseStampedTable[1].pose.orientation.x = 0;
poseStampedTable[1].pose.orientation.y = 0;
poseStampedTable[1].pose.orientation.z = 1;
poseStampedTable[1].pose.orientation.w = -0.5;*/



}

	Myservice(){

	fnInitParam();
ros::NodeHandle nh_;

pubPoseStampedTb3p = nh_.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);
move = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

sub_arrival_status_0 = nh_.subscribe("/move_base/result", 1, &Myservice::cbCheckArrivalStatus_0, this);

range_status = nh_.subscribe("/scan", 1, &Myservice::check_ranges,this);

ros::Rate loop_rate(5);


while (ros::ok())
{

if(state){vel.angular.z = 0; vel.linear.x = 0.03;}
else{vel.angular.z = 0.3; vel.linear.x = 0;}
move.publish(vel);

//fnPubPose();


ros::spinOnce();
loop_rate.sleep();
}
	}
	
private:	

double x = -0.0179;
double y = 0.1403;
	
int count = 0;
int check = 0;
double ow = -0.5;
	
int z = 0;
bool up = true;	
	
	
geometry_msgs::PoseStamped poseStampedTable;
geometry_msgs::Twist vel;


//sensor_msgs::LaserScan lds;
ros::Subscriber range_status;
ros::Subscriber sub_arrival_status_0;
ros::Subscriber sub_arrival_status_1;

ros::Publisher pubPoseStampedTb3p;
ros::Publisher move;
ros::Publisher lds;

int i=1;

bool state = true;
};

int main(int argc, char **argv)
{

ros::init(argc, argv, "my_service");
Myservice myservice;
ros::spin();
return 0;
}





