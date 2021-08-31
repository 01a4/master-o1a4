#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseActionResult.h>

class Myservice
{
public:
	void cbCheckArrivalStatus_0(const move_base_msgs::MoveBaseActionResult rcvMoveBaseActionResult) {
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
		x = x - 1.1886 / sero_n;
		y = y - 1.3838 / garo_n;
		z++;
	}

	void go12()
	{
		x = x - 2.2493 / sero_n;
		y = y + 1.5308 / garo_n;
		ow = -0.5;
		count++;
		up = true;
	}

	void go21()
	{
		x = x - 1.1886 / sero_n;
		y = y - 1.3838 / garo_n;
		ow = 0.35;
		z++;
	}

	void go22()
	{
		x = x + 1.1886 / sero_n;
		y = y + 1.3838 / garo_n;
		ow = 0.35;
		z--;
	}

	void go31()
	{
		x = x + 1.1886 / sero_n;
		y = y + 1.3838 / garo_n;
		z--;
	}

	void go32()
	{
		x = x - 2.2493 / sero_n;
		y = y + 1.5308 / garo_n;
		ow = 2;
		up = false;
	}

	void fnPubPose()
	{
		if (state) {
			if ((count == (garo_n / 2)) && (z == sero_n))
			{
				ROS_INFO("everything is done");
			}
			else
			{
				pubPoseStampedTb3p.publish(poseStampedTable);
				ROS_INFO("%dpose publish", i);
			}
		}
		else {
			if (up)
			{
				if (z < sero_n) { go11(); }
				else if (z == sero_n) { go21(); }
				else if (z == (sero_n + 1)) { go32(); }
			}
			else
			{
				if (z > 1) { go31(); }
				else if (z == 1) { go22(); }
				else if (z == 0) { go12(); }
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
	}

	Myservice() {

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
	//초기 좌표
	double x = -0.0179;
	double y = 0.1403;

	int count = 0;  //아래로 가고 오른쪽을 보는횟수임. 긴 변(가로)을 나눈 횟수에 따라 값이 달라짐 현재는 6으로 나누었기 때문에 최대값이 3임.
	double ow = -0.5; //바라보는 방향

	int z = 0; // bool변수 up이 true일때 로봇이 움직일때마다 값이 1씩 증가하고 
		   // bool변수 up이 false일때 로봇이 움직일때마다 값이 1씩 감소함
		// 위,아래로 움직일건지, 방향을 바꿀차례인지 확인하는 변수

	bool up = true;

	geometry_msgs::PoseStamped poseStampedTable;

	ros::Subscriber sub_arrival_status_0;
	ros::Subscriber sub_arrival_status_1;
	ros::Publisher pubPoseStampedTb3p;

	int i = 1;
	bool state = true;
	int sero_n = 3; // 세로를 몇번 나눌것인지
	int garo_n = 6; // 가로를 몇번 나눌것인지
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "my_service");
	Myservice myservice;
	ros::spin();
	return 0;
}
