#include "../include/tracked/track.hpp"



Track::Track(const Eigen::Vector3d&target_xyz_cam;){

    target.center = points[0];
    for(int i = 1;i<5;i++)
    {
        target.points[i] = points[i];
    }

}