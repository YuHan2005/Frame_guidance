#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "../include/detect/detect.hpp"
#include <gtest/gtest.h>
#include <opencv2/videoio.hpp>


// 将需要硬件的测试标记为可能被跳过
TEST(Detector, Detect) {
    
    cv::VideoCapture video("/home/rm/cod/Frame_gudiance/video/Video_20250906125314976.avi");
    

    if(!video.isOpened()){
        GTEST_SKIP() << "没有打开对应的视频文件";}

    cv::Mat camera_matrix = (cv::Mat_<double>(3,3) <<
    2133,    0, 640,   // fx, 0, cx
       0, 2276, 512,   // 0, fy, cy
       0,    0,   1);

    cv::Mat dist_coeffs = (cv::Mat_<double>(1,5) << -0.05, 0.02, 0, 0, 0);
    Detector detect(80,20,0.8,0.7,0.85,camera_matrix,dist_coeffs);

    cv::Mat img;
    while(video.read(img)){
        if(img.empty())
        {
            std::cout<<"读取视频失败"<<std::endl;
        }

        EXPECT_TRUE(detect.detect(img));



    }
    // 清理窗口
    cv::destroyAllWindows();


    

    //EXPECT_FALSE(frame.empty());
    // EXPECT_TRUE(cam.isOpened());

}