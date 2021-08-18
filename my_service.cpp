#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseActionResult.h>

/*void cbCheckArrivalStatusTB3P(const move_base_msgs::MoveBaseActionResult rcvMoveBaseActionResult)
  {
    if (rcvMoveBaseActionResult.status.status == 3)
    {
      state = true;
      
    }
    else
    {
      ROS_INFO("cbCheckArrivalStatusTB3P : %d", rcvMoveBaseActionResult.status.status);
    }
  }

*/
int main(int argc, char **argv)
{
ros::init(argc, argv, "my_service");
ros::NodeHandle nh_;
geometry_msgs::PoseStamped poseStampedTable;
ros::Rate loop_rate(5);


double point[2][2] = {

	{-1.6285, -0.4183,},

	{-2.1424, 1.1759}
};

bool state = true;
void cbCheckArrivalStatusTB3P(const move_base_msgs::MoveBaseActionResult rcvMoveBaseActionResult)
  {
    if (rcvMoveBaseActionResult.status.status == 3)
    {
      state = true;

    }
    else
    {
      ROS_INFO("cbCheckArrivalStatusTB3P : %d", rcvMoveBaseActionResult.status.status);
    }
  }

poseStampedTable.header.seq = 0;
poseStampedTable.header.stamp.sec = 0;
poseStampedTable.header.stamp.nsec = 0;
poseStampedTable.header.frame_id = "map";

poseStampedTable.pose.position.x = point[0][0];
poseStampedTable.pose.position.y = point[0][1];
poseStampedTable.pose.position.z = 0;

poseStampedTable.pose.orientation.x = 0;
poseStampedTable.pose.orientation.y = 0;
poseStampedTable.pose.orientation.z = 1;
poseStampedTable.pose.orientation.w = -0.5;

//ros::Publisher pubServiceStatusPadtb3p;

ros::Subscriber sub_arrival_status_tb3p;

ros::Publisher pubPoseStampedTb3p;
pubPoseStampedTb3p = nh_.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);


sub_arrival_status_tb3p = nh_.subscribe("/move_base/result", 1, &cbCheckArrivalStatusTB3P, this);

while (ros::ok())
{
if(state == true)
{
	pubPoseStampedTb3p.publish(poseStampedTable);
	ROS_INFO("point publish done");
	state = false;
}


ros::spinOnce();
loop_rate.sleep();
}

ros::spin();
return 0;
}



