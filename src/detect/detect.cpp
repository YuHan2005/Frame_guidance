#include "../include/detect/detect.hpp"
#include <complex>
#include <cstddef>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/wait.h>


Detector::Detector(const double &thre,
        const double &radius_thr,
        const double &C_thr,const double &Area_thr,const double &S_thr,
        const cv::Mat &camera_matrix,const cv::Mat &dist_coeffs):
    thre(thre),radius_thr(radius_thr),C_thr(C_thr),Area_thr(Area_thr),S_thr(S_thr),
    pnp(camera_matrix,dist_coeffs){}




cv::Mat Detector::Process_Image(const cv::Mat &img) noexcept{

    cv::Mat frame = img.clone();
    cv::Mat gray_img,binary_img;

    cv::cvtColor(frame, gray_img, cv::COLOR_BGR2GRAY);  //灰度化
    cv::GaussianBlur(gray_img, gray_img, cv::Size(5, 5), 0, 0);

    cv::threshold(gray_img, binary_img,thre, 255, cv::THRESH_BINARY_INV);

    // 定义腐蚀核（3x3 矩形核）
    //Size越大腐蚀越强
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));

    // 腐蚀
    //iterations腐蚀次数
    cv::erode(binary_img, binary_img, element, cv::Point(-1,-1), 1);
    
    return binary_img;

}



 bool Detector::detect(const cv::Mat &img) noexcept
 {
    if(img.empty()){
        return false;
    }

    cv::Mat binary_img = Process_Image(img);

    
    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary_img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    std::vector<cv::Point2f> centers;
    std::vector<float> radiuss;

    for(auto contour:contours){

        // 假设：img是原图尺寸（用于可选IoU），contour为当前轮廓
        double area = std::fabs(cv::contourArea(contour));
        if (area < 50) continue; // 面积过小直接丢

        //计算轮廓周长
        double peri = cv::arcLength(contour, true);


        //计算圆度 (circularity)
        //C = 4PI*area/peri^2
        //C越接近1,怎证明该图形越接近圆
        double circularity = (peri > 1e-6) ? (4.0 * CV_PI * area / (peri * peri)) : 0.0;


        //最小圆形拟合
        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contour, center, radius);


        //面积比
        double area_ratio = (CV_PI * radius * radius > 1e-6) ? (area / (CV_PI * radius * radius)) : 0.0;

        // 凸包实心度
        std::vector<cv::Point> hull;
        cv::convexHull(contour, hull);
        double hull_area = std::fabs(cv::contourArea(hull));
        double solidity = (hull_area > 1e-6) ? (area / hull_area) : 0.0;





        if(radius<radius_thr||circularity<C_thr||area_ratio<Area_thr||solidity<S_thr){
            continue;
        }

        
        centers.push_back(center);
        radiuss.push_back(radius); 
    }

    for(size_t i = 0;i<centers.size();i++){
        cv::circle(img, centers[i], (int)radiuss[i], cv::Scalar(0, 255, 0), 2);
    }


    if(centers.size()!=1){

        return false;
    }
    std::vector<cv::Point2d> target;
    target.push_back(centers[0]);
    target.push_back(cv::Point2d(centers[0].x-radiuss[0],centers[0].y));//左
    target.push_back(cv::Point2d(centers[0].x,centers[0].y-radiuss[0]));//上
    target.push_back(cv::Point2d(centers[0].x+radiuss[0],centers[0].y));//右
    target.push_back(cv::Point2d(centers[0].x,centers[0].y+radiuss[0]));

    cv::Mat rotation_vector;
    cv::Mat translation_vector;

    if (pnp.Pnp_solver(target, rotation_vector, translation_vector) == 1) {
       
    
        std::cout << "SolvePnP 成功！" << std::endl;

        std::cout << "旋转向量 (Rodrigues): " << std::endl;
        std::cout << rotation_vector << std::endl;

        cv::Mat rotation_matrix;
        cv::Rodrigues(rotation_vector, rotation_matrix); // 转换成旋转矩阵
        std::cout << "旋转矩阵:" << std::endl;
        std::cout << rotation_matrix << std::endl;

        std::cout << "平移向量:" << std::endl;
        std::cout << translation_vector << std::endl;

        target_xyz_cam << translation_vector.at<double>(0), translation_vector.at<double>(1), translation_vector.at<double>(2);

    }
    else {
        std::cout << "SolvePnP 失败！" << std::endl;
    }


    cv::imshow("img",img);
    cv::imshow("bianry",binary_img);

    cv::waitKey(10);

    return true;

}