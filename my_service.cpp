#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <sensor_msgs/LaserScan.h>
#include <cstdlib>
#include <ctime>
class Myservice
{ 
public:


void left_turn(){ROS_INFO("turning");vel.linear.x = 0;vel.angular.z = 0.3;}

void go_straight(){ROS_INFO("go straight");vel.angular.z = 0;vel.linear.x = 0.15;}



void right_check_ranges(const sensor_msgs::LaserScan msg){
        i++;
	left_check = 0;
        right_check = 0;
        srand(time(NULL));


	int angle = 150;
	float max_ranges = 0.4;


        int left_random = rand() % angle;
	int right_random = rand() % (360 - (360 - angle) + 1) + (360 - angle);
        for(int k=right_random;k<360;k++){
                if ((msg.ranges[k]<max_ranges)&&(msg.ranges[k]>0.1)) {
                right_check++;
                ROS_INFO("%d right_loop, value = %f",i,msg.ranges[k]);
                ROS_INFO("right_wall close");
                right_state = false;}}
	for(int k=0;k<left_random;k++){
                if ((msg.ranges[k]<max_ranges)&&(msg.ranges[k]>0.1)) {
                left_check++;
                ROS_INFO("%d left_loop, value = %f",i,msg.ranges[k]);
                ROS_INFO("left_wall close");
                left_state = false;}}
	if(left_check == 0) {left_state = true;}
        if(right_check == 0) {right_state = true;}
        }

}

Myservice(){

	
ros::NodeHandle nh_;
move = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
right_range_status = nh_.subscribe("/scan", 1, &Myservice::right_check_ranges,this);


ros::Rate loop_rate(5);


while (ros::ok())
{

if(left_state && right_state){go_straight();}
else{left_turn();}
move.publish(vel);
ros::spinOnce();
loop_rate.sleep();
}
	}
	
private:	


int left_check = 0;
int right_check = 0;

geometry_msgs::Twist vel;


ros::Subscriber right_range_status;


ros::Publisher move;


int i=1;

bool left_state = true;
bool right_state = true;
};

int main(int argc, char **argv)
{

ros::init(argc, argv, "my_service");
Myservice myservice;
ros::spin();
return 0;
}





