#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>

const auto window = "camera/image";

void onImgReceived(const sensor_msgs::ImageConstPtr &imgMsg) {
    cv::imshow(window, cv_bridge::toCvShare(imgMsg, "bgr8")->image);
    cv::waitKey(1);
}

int main(int argc, char **argv) {
    // Initialize ROS channels
    ros::init(argc, argv, "rosbot_station");
    ros::NodeHandle nh;

    image_transport::ImageTransport imgTransport(nh);
    auto imgSub = imgTransport.subscribe("camera/image", 1, &onImgReceived);

    // Setup display window
    cv::namedWindow(window);

    ros::spin();

    cv::destroyAllWindows();

    return 0;
}
