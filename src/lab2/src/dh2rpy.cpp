#include <ros/ros.h>
#include <iostream>
#include <kdl/kdl.hpp>
#include <kdl/tree.hpp>
#include <kdl/chain.hpp>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;
int main(int argc, char *argv[]){
	ros::init(argc, argv, "robot_coordinates");
	ros::NodeHandle nh("~");

	KDL::Chain chain;
	double theta1, theta2, theta3;
	double a2;


	nh.param("a2", a2, 0.5);
	nh.param("theta1", theta1, 0.0);
	nh.param("theta2", theta2, 0.0);
	nh.param("theta3", theta3, 0.0);

	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(0, 0, 0, theta1)));
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(0, -M_PI/2, 0, theta2)));
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(a2, 0, 0, theta3)));

	vector <double>joint;
	vector <double>tip;
	double roll, pitch, yaw;
	vector <double> RPY(3);
	std::string name_RPY;
	std::string name_frame;

	for(int i=0; i<3 ;i++){
		for(int j=0;j<3;j++){
			//joint[j] = chain.getSegment(i).getJoint().JointAxis().data[j]		
			tip.push_back(chain.getSegment(i).getFrameToTip().p.data[j]);
		}
		chain.getSegment(i).getFrameToTip().M.GetRPY(roll, pitch, yaw);
		
	cout << "Zlacze " << i << " xyz : " << tip[0] << ", " <<tip[1] << ", " << tip[2] << endl;		
	cout << "Zlacze " << i << " rpy : " << roll << ", " << pitch << ", " << yaw << endl;
	RPY[0]= roll;
	RPY[1]= pitch;
	RPY[2]= yaw;

	name_RPY = "/RPY/"+std::to_string(i);
	name_frame = "/frame/"+std::to_string(i);
	nh.setParam(name_RPY, RPY);
	nh.setParam(name_frame, tip);
	tip.clear();
	}
	
	nh.deleteParam("theta1");
	nh.deleteParam("theta2");
	nh.deleteParam("theta3");
	return 0;

}
