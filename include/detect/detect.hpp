#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES  // 必须放在 <cmath> 之前
#include <cmath>
#include <Eigen/Dense>

#include "../math/include/PNP.hpp"

class Detector{
public:

    Detector() = default;

    Detector(const double &thre,
        const double &radius_thr,
        const double &C_thr,const double &Area_thr,const double &S_thr,
        const cv::Mat &camera_matrix,const cv::Mat &dist_coeffs);

    cv::Mat Process_Image(const cv::Mat &img) noexcept;

    bool detect(const cv::Mat &img) noexcept;

    

    Eigen::Vector3d target_xyz_cam;



private:
    double thre;//二值化阈值
    double radius_thr;//筛选圆的半径
    double C_thr;//圆度的阈值
    double Area_thr ;//面积比
    double S_thr;//凸包面积比


    Pnp pnp;

    


};