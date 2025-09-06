#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>






class Pnp{

public:

    Pnp() = default;

    Pnp(const cv::Mat &camera_matrix,const cv::Mat &dist_coeffs);


    bool Pnp_solver(const std::vector<cv::Point2d> image_points,cv::Mat&rotation_vector,cv::Mat&translation_vector);



private:


    std::vector<cv::Point3d>world_points;

    // 相机内参矩阵
    cv::Mat camera_matrix;

    // 相机畸变系数
    cv::Mat dist_coeffs;





};