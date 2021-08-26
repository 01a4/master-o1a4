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
      if(i==0){i++;}
      else{i--;}
    }
    else
    {
      ROS_INFO("cbCheckArrivalStatus_0 : %d", rcvMoveBaseActionResult.status.status);
    }
  }


/*	void cbCheckArrivalStatus_1(const move_base_msgs::MoveBaseActionResult rcvMoveBaseActionResult){
        if (rcvMoveBaseActionResult.status.status == 3)
    {
      state[1] = true;
      ROS_INFO("change state[1]");
    }
    else
    {
      ROS_INFO("cbCheckArrivalStatus_1 : %d", rcvMoveBaseActionResult.status.status);
    }
  }
*/

void fnPubPose()
{/*
if(state[0])
{
pubPoseStampedTb3p.publish(poseStampedTable[0]);
ROS_INFO("state[0] publish");
state[0] = false;
}
else if(state[1])
{
pubPoseStampedTb3p.publish(poseStampedTable[1]);
ROS_INFO("state[1] publish");
state[1] = false;

}*/

if(state){
pubPoseStampedTb3p.publish(poseStampedTable[i]);
ROS_INFO("%dpose publish",i);
}
else{
	state = true;
	ROS_INFO("STATE CHANGE");
}
}


void fnInitParam()
{
poseStampedTable[0].header.seq = 0;
poseStampedTable[0].header.stamp.sec = 0;
poseStampedTable[0].header.stamp.nsec = 0;
poseStampedTable[0].header.frame_id = "map";

poseStampedTable[0].pose.position.x = point[0][0];
poseStampedTable[0].pose.position.y = point[0][1];
poseStampedTable[0].pose.position.z = 0;

poseStampedTable[0].pose.orientation.x = 0;
poseStampedTable[0].pose.orientation.y = 0;
poseStampedTable[0].pose.orientation.z = 1;
poseStampedTable[0].pose.orientation.w = -0.5;
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
poseStampedTable[1].pose.orientation.w = -0.5;



}




	Myservice(){

	fnInitParam();
ros::NodeHandle nh_;
//geometry_msgs::PoseStamped poseStampedTable[2];
//ros::Rate loop_rate(5);

/*
double point[2][2] = {

	{-1.6285, -0.4183,},

	{-2.1424, 1.1759}
};



poseStampedTable[0].header.seq = 0;
poseStampedTable[0].header.stamp.sec = 0;
poseStampedTable[0].header.stamp.nsec = 0;
poseStampedTable[0].header.frame_id = "map";

poseStampedTable[0].pose.position.x = point[0][0];
poseStampedTable[0].pose.position.y = point[0][1];
poseStampedTable[0].pose.position.z = 0;

poseStampedTable[0].pose.orientation.x = 0;
poseStampedTable[0].pose.orientation.y = 0;
poseStampedTable[0].pose.orientation.z = 1;
poseStampedTable[0].pose.orientation.w = -0.5;


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
poseStampedTable[1].pose.orientation.w = -0.5;

*/
//ros::Publisher pubServiceStatusPadtb3p;

/*ros::Subscriber sub_arrival_status_0;
ros::Subscriber sub_arrival_status_1;
ros::Publisher pubPoseStampedTb3p;
*/

pubPoseStampedTb3p = nh_.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);


sub_arrival_status_0 = nh_.subscribe("/move_base/result", 1, &Myservice::cbCheckArrivalStatus_0, this);
//sub_arrival_status_1 = nh_.subscribe("/move_base/result", 1, &Myservice::cbCheckArrivalStatus_1, this);
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
	double point[2][2] = {

        {-1.6285, -0.4183,},

        {-0.8057, 0.3931}
};

geometry_msgs::PoseStamped poseStampedTable[2];

ros::Subscriber sub_arrival_status_0;
ros::Subscriber sub_arrival_status_1;
ros::Publisher pubPoseStampedTb3p;
int i=0;
/*poseStampedTable[0].header.seq = 0;
poseStampedTable[0].header.stamp.sec = 0;
poseStampedTable[0].header.stamp.nsec = 0;
poseStampedTable[0].header.frame_id = "map";

poseStampedTable[0].pose.position.x = point[0][0];
poseStampedTable[0].pose.position.y = point[0][1];
poseStampedTable[0].pose.position.z = 0;

poseStampedTable[0].pose.orientation.x = 0;
poseStampedTable[0].pose.orientation.y = 0;
poseStampedTable[0].pose.orientation.z = 1;
poseStampedTable[0].pose.orientation.w = -0.5;
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
poseStampedTable[1].pose.orientation.w = -0.5;

*/
bool state = true;
};

int main(int argc, char **argv)
{

ros::init(argc, argv, "my_service");
Myservice myservice;
ros::spin();
return 0;
}




