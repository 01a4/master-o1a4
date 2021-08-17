#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>


int main(int argc, char **argv)
{



ros::init(argc, argv, "my_service");

ros::NodeHandle nh_;

geometry_msgs::PoseStamped poseStampedTable;

ros::Rate loop_rate(5);

poseStampedTable.header.seq = 0;
poseStampedTable.header.stamp.sec = 0;
poseStampedTable.header.stamp.nsec = 0;
poseStampedTable.header.frame_id = "map";
//poseStampedTable.header.stamp = ros::Time::now();

poseStampedTable.pose.position.x = -1.8;
poseStampedTable.pose.position.y = -0.7;
poseStampedTable.pose.position.z = 0;

poseStampedTable.pose.orientation.x = 0;
poseStampedTable.pose.orientation.y = 0;
poseStampedTable.pose.orientation.z = 1;
poseStampedTable.pose.orientation.w = -0.5;

//ros::Publisher pubServiceStatusPadtb3p;

ros::Publisher pubPoseStampedTb3p;
pubPoseStampedTb3p = nh_.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);

//ros::Subscriber sub_arrival_status_tb3p;

//poseStampedTable.header.frame_id = "map";
//poseStampedTable.header.stamp = ros::Time::now();

//poseStampedTable.pose.position.x = -1.2065;
//poseStampedTable.pose.position.y = -1.2435;
//poseStampedTable.pose.position.z = 0;

//poseStampedTable.pose.orientation.x = 0;
//poseStampedTable.pose.orientation.y = 0;
//poseStampedTable.pose.orientation.z = 1;
//poseStampedTable.pose.orientation.w = -0.5;


while (ros::ok())
{
pubPoseStampedTb3p.publish(poseStampedTable);
ROS_INFO("pose publish done");
ros::spinOnce();
loop_rate.sleep();
}

ros::spin();
return 0;
}



