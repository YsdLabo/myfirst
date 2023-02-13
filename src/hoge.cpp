#include<ros/ros.h>
#include<std_msgs/String.h>
#include<chrono>

class TEST
{
private:
	int num;
public:
	TEST() : TEST(0) {}
	TEST(int n) {
		if(n > 5) {
			throw std::logic_error("hoge");
//			throw std::out_of_range("out of rage: KrsLib::id > 31");
		}
		num = n;
	}
	~TEST() { ROS_INFO("destructor!!!"); }
	int get() { return num; }
};

class TIMER
{
private:
	ros::NodeHandle nh;
	ros::Subscriber sub;
	ros::Publisher pub;
	ros::Timer timer;
	void timer_callback(const ros::TimerEvent& e)
	{
		ROS_INFO("publish");
	}
	void callback(const std_msgs::String::ConstPtr& msg)
	{
		ROS_INFO("subscribe");
	}
public:
	void run()
	{
		sub = nh.subscribe("listener", 10, &TIMER::callback, this);
		pub = nh.advertise<std_msgs::String>("talker", 10);
		timer = nh.createTimer(ros::Duration(0.1), &TIMER::timer_callback, this);
	}
};


int main(int argc, char** argv)
{/*
	TEST *a;
	try{
		a = new TEST(10);
		ROS_INFO("make a");
	}
	catch(std::out_of_range& ex)
	{
		ROS_ERROR("%s", ex.what());
		delete a;
		throw;
	}
	catch(...) {
		ROS_ERROR("exception");
		//throw;
	}
	ROS_INFO("success: %d\n", a->get());
	delete a;
*/

/*	int raw_data[10];
	for(int i=0;i<10;i++)
		raw_data[i] = i * i;

	std::list<std::string>  rawData;

	for(int i=0;i<10;i++) {
		rawData.push_back(std::to_string(raw_data[i]));
	}
	for(auto itr = rawData.begin(); itr != rawData.end(); itr++) {
		printf("%s\n", itr->c_str());
	}
*/
/*
//	std::chrono::system_clock::time_point  start, end;
	std::chrono::high_resolution_clock::time_point start, end;
	start = std::chrono::system_clock::now();
	usleep(123456);
	end = std::chrono::system_clock::now();
	double d = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
	printf("time = %lf\n", d);
*/
	ros::init(argc, argv, "timer_test");
	TIMER timer;
	timer.run();
	ros::spin();

	return 0;
}
