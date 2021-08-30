#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseActionResult.h>


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


sub_arrival_status_0 = nh_.subscribe("/move_base/result", 1, &Myservice::cbCheckArrivalStatus_0, this);
ros::Rate loop_rate(5);


while (ros::ok())
{


fnPubPose();

sleep(1);

ros::spinOnce();
loop_rate.sleep();
}
	}
	
private:
	

double x = -0.0179;
double y = 0.1403;
	
int count = 0;
double ow = -0.5;
	
int z = 0;
bool up = true;	
	
	
geometry_msgs::PoseStamped poseStampedTable;

ros::Subscriber sub_arrival_status_0;
ros::Subscriber sub_arrival_status_1;
ros::Publisher pubPoseStampedTb3p;
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





