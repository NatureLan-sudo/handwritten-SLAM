/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 13:32:15
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-01 16:06:00
 * @FilePath: /handwritten-SLAM/include/handwritten-slam/camera.h
 * @Description: 
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
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
        // 定义世界w，相机c，像素p坐标系的变换
        Eigen::Vector3d world2camera( const Eigen::Vector3d& p_w, const Sophus::SE3d& T_c_w); // 模板类Sophus需要给定数据类型了
        Eigen::Vector3d camera2world( const Eigen::Vector3d& p_c, const Sophus::SE3d& T_w_c);
        Eigen::Vector2d camera2pixel( const Eigen::Vector3d& p_c);
        Eigen::Vector3d pixel2camera(const Eigen::Vector2d& p_p, double depth = 1);
        Eigen::Vector3d pixel2world(const Eigen::Vector2d& p_p, const Sophus::SE3d& T_c_w, double depth = 1);
        Eigen::Vector2d world2pixel(const Eigen::Vector3d&p_w, const Sophus::SE3d& T_w_c);
        ~Camera();
    };
    // 通过赋值列表将输入参数给成员变量赋值
    Camera::Camera(float fx, float fy, float cx, float cy, float depth_scale)
    :fx_(fx), fy_(fy), cx_(cx), cy_(cy), depth_scale_(depth_scale)
    {
    }
    
    Camera::~Camera()
    {
    }
    
}

#endif
