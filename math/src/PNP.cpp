#include "../include/PNP.hpp"




Pnp::Pnp(const cv::Mat &camera_matrix,const cv::Mat &dist_coeffs):
camera_matrix(camera_matrix),dist_coeffs(dist_coeffs)
{

    //中心，左，上，右，下
    world_points.push_back(cv::Point3d(0.0f, 0.0f, 0));
	world_points.push_back(cv::Point3d(-0.0275f, 0.0f, 0));
	world_points.push_back(cv::Point3d(0.0f, -0.0275f, 0));
	world_points.push_back(cv::Point3d(+0.0275f, 0.0f, 0));
    world_points.push_back(cv::Point3d(0.0f, +0.0275f, 0));

}



bool Pnp::Pnp_solver(const std::vector<cv::Point2d> image_points,cv::Mat&rotation_vector,cv::Mat&translation_vector){

    // 要求：world_points.size() == image_points.size()，且 >= 4
    if (world_points.size() != image_points.size() || world_points.size() < 4) {
        return false; // 点数不匹配，直接失败
    }

    bool success = cv::solvePnP(world_points, 
                                image_points, 
                                camera_matrix, 
                                dist_coeffs, 
                                rotation_vector, 
                                translation_vector, 
                                false,                // useExtrinsicGuess
                                cv::SOLVEPNP_IPPE);  // 方法

    return success;
    
};
