#include <opencv2/core/types.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "../math/include/Extend_Kalman_FIlter.hpp"

#include <Eigen/Dense>
#include <deque>
#include <functional>
#include <map>
#include <vector>


struct Target{

    Eigen::Vector3d target_xyz_chassis;

};


class Track{


public:
    ExtendedKalmanFilter ekf;

    Track()= default;

    Track(const Eigen::Vector3d&target_xyz_cam);


private:
    Target target;

};
