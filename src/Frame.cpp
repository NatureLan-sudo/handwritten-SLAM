/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 20:49:59
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-01 22:26:18
 * @FilePath: /handwritten-SLAM/src/Frame.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#include "Frame.h"
namespace myslam{
    /**
     * @description: 构造函数， 通过：进行默认赋值
     * @return {*}
     */    
    Frame::Frame() : id_(-1), time_stamp_(-1), camera_(nullptr) {
    }
    /**
     * @description: 析构函数
     * @return {*}
     */    
    Frame::~Frame() {}

    /**
     * @description: 通过赋值构造关键帧，此时所有的类成员变量都被赋值了。对于每一个帧来说都有这些数值
     * @return {*}
     */    
    Frame::Frame ( long id, double time_stamp, SE3d T_c_w ,  Camera::Ptr camera , Mat color , Mat depth ) :
    id_(id), time_stamp_(time_stamp), T_c_w_(T_c_w), camera_(camera), color_(color), depth_(depth) {           
    }
     /**
      * @description:  获取相机的光心，就是相机坐标系相对于世界坐标系的平移
      * @return {*}
      */    
     Vector3d Frame::getCamCenter() const { // TODO: 不知道后面的const是什么意思
         return T_c_w_.inverse().translation();
     }

     bool Frame::isInFrame(const Vector3d& pt_world ) {
         Vector3d pt_c = camera_-> world2camera(pt_world, T_c_w_);  //我们需要一个实例来引用Camera类当中的函数
        if ( pt_c(2) < 0) return false;   // TODO:不知道为什么在用这个的时候都在后面加了一个0  pt_c(0,0)
        Vector2d pixel = camera_ -> world2pixel (pt_world, T_c_w_);
        return pixel(0) > 0&& pixel(1) >0 &&  pixel(0) < color_.rows  &&  pixel(1) <color_.cols ;   //* 像素值均大于零， 同时，对于象征着图像的矩阵color，像素值应该小于相应的行和列。
     }

     /**
      * @description: 创造一个关键帧
      * @return {*}
      */
     Frame::Ptr Frame::createFrame()
{
    static long factory_id = 0;
    return Frame::Ptr( new Frame(factory_id++) );
}
/**
 * @description: 获取三维点的深度
 * @param {KeyPoint&} kp 
 * @return {*}
 */
double Frame::findDepth ( const cv::KeyPoint& kp )
{
    // cvRound()：返回跟参数最接近的整数值，即四舍五入；即对x,y值取整
    // point2f  pt (x,y) 二维位置
    int x = cvRound(kp.pt.x);
    int y = cvRound(kp.pt.y);
    // * opencv 中用于对MAT 矩指定一个位置
    ushort d = depth_.ptr<ushort>(y)[x];     // d是指向 depth矩阵第y行的第x元素的指针
    if ( d!=0 )   //如果深度不为空
    {
        return double(d)/camera_->depth_scale_;  // ! 要记得除以深度的尺度
    }
    else  // 如果此时我们还没获得深度，就去检查周围的点的深度，如果周围点的深度存在，就返回周围点的深度。
    {
        // check the nearby points 
        int dx[4] = {-1,0,1,0};
        int dy[4] = {0,-1,0,1};
        for ( int i=0; i<4; i++ )
        {
            d = depth_.ptr<ushort>( y+dy[i] )[x+dx[i]];
            if ( d!=0 )
            {
                return double(d)/camera_->depth_scale_;
            }
        }
    }
    return -1.0; //这个点的周围的点也没有深度 ，最后就智能返回错误了。
}

    } // namespace myslam