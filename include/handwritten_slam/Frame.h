/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 20:06:11
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-01 20:49:50
 * @FilePath: /handwritten-SLAM/include/handwritten_slam/Frame.h
 * @Description:  定义 ID 时间戳，位姿，相机，图像，即一帧中最重要的一些信息
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#ifndef FRAME_H
#define FRAME_H
#include "common_include.h"
#include "camera.h"
namespace myslam {
    class Frame
    {
    private:
        /* data */
    public:
        typedef std::shared_ptr<Frame> Ptr; //智能指针，能够一定成都的避免内存泄露
        unsigned long id_; //记录当前关键帧的id
        double time_stamp_;
        Sophus::SE3d T_c_w_; //世界坐标系到相机坐标系的变换，记为当前帧的位姿
        Camera::Ptr camera_; 
        Mat color_, depth_;
    public:
    //类函数
        Frame();
        ~Frame();
        Frame ( long id, double time_stamp = 0, SE3d T_c_w = SE3d(), Camera::Ptr camera = nullptr, Mat color = Mat(), Mat depth = Mat() ); //不明白为什么这里要进行这个等于 
        // 创建关键帧
        static Frame::Ptr createFrame();
        // 在深度图中获取深度
        double findDepth (const cv::KeyPoint& kp);
        
        //获得相机光心 ，这是什么定义方式？
        Vector3d getCamCenter() const;
        // 判断某个点是否在这一帧中
        bool isInFrame( const  Vector3d& pt_world );
    };
    
}
#endif