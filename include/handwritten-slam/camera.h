#ifndef CAMERA_H
#define CAMERA_H
#include "common_include.h"
namespace myslam {
    class Camera
    {
    private:
        // 存放公共访问的相机信息，不设置私有成员
    public:
        //内参
        float fx_, fy_, cx_, cy_, depth_scale_;
        typedef std::shared_ptr<Camera> Ptr;
        Camera(float fx, float fy, float cx, float cy, float depth_scale);
        ~Camera();
    };
    
    Camera::Camera(float fx, float fy, float cx, float cy, float depth_scale)
    :fx_(fx), fy_(fy), cx_(cx), cy_(cy), depth_scale_(depth_scale)
    {
    }
    
    Camera::~Camera()
    {
    }
    
}

#endif
