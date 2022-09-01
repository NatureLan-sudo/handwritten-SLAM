/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 14:01:23
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-01 22:27:27
 * @FilePath: /handwritten-SLAM/src/camera.cpp
 * @Description: 记录相机下的变换
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */

#include "camera.h"
namespace myslam {
    //默认构造函数
    // Camera::Camera() {
    //     //从config文件中读取
    
    // } 
    
    Eigen::Vector3d Camera::world2camera(const Eigen::Vector3d& p_w, const Sophus::SE3d& T_c_w) {
       return T_c_w * p_w;
    }

    Eigen::Vector3d  Camera::camera2world( const Eigen::Vector3d& p_c, const Sophus::SE3d& T_c_w) {
        return T_c_w.inverse()*p_c;
    }
    Eigen::Vector2d Camera::camera2pixel( const Eigen::Vector3d& p_c) {
        return Eigen::Vector2d (
            fx_* ( p_c(0) / p_c(2) ) + cx_,
            fy_* ( p_c(1) / p_c(2) ) + cy_
        );
    }
    
    /**
     * @description: 从像素坐标到归一化平面上的相机坐标，我们将自己输入深度，如果不输入的话，depth的默认值是1 
     * @param {Vector2d&} p_p  像素坐标
     * @param {double} depth
     * @return {*}
     */    
    Eigen::Vector3d Camera::pixel2camera(const Eigen::Vector2d& p_p, double depth ) {
        return Eigen::Vector3d (
            ( p_p(0) - cx_ ) * depth / fx_,
            ( p_p(1) - cy_ ) * depth /fy_,
            depth
        );
    }

    Eigen::Vector2d Camera::world2pixel (const Eigen::Vector3d& p_w , const Sophus::SE3d& T_c_w) {
        Eigen::Vector3d p_c = world2camera(p_w, T_c_w);
        return camera2pixel ( p_c );
    }

    Eigen::Vector3d Camera::pixel2world (const Eigen::Vector2d& p_p, const Sophus::SE3d& T_c_w, double depth ) {
        return camera2world( pixel2camera(p_p, depth), T_c_w );

    }

}