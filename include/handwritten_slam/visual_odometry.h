/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-08 20:50:48
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-08 21:52:33
 * @FilePath: /handwritten-SLAM/include/handwritten_slam/visual_odometry.h
 * @Description: 
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#ifndef VISUALODOMETRY_H
#define VISUALODOMETRY_H

#include "common_include.h"
#include "Map.h"

#include <opencv2/features2d/features2d.hpp>

namespace myslam 
{
class VisualOdometry
{
public:
    typedef shared_ptr<VisualOdometry> Ptr;
    enum VOState { // 枚举，第一个设定为-1，第二个为0，第三个就是1
        INITIALIZING=-1,
        OK=0,
        LOST
    };
    // 两帧之间的VO
    VOState     state_;     // current VO status
    Map::Ptr    map_;       // map with all frames and map points 有所有关键帧和地图点的图
    Frame::Ptr  ref_;       // reference frame  参考帧
    Frame::Ptr  curr_;      // current frame    当前帧
    
    cv::Ptr<cv::ORB> orb_;  // orb detector and computer 
    vector<cv::Point3f>     pts_3d_ref_;        // 3d points in reference frame 
    vector<cv::KeyPoint>    keypoints_curr_;    // keypoints in current frame
    Mat descriptors_curr_;  // descriptor in current frame 
    Mat descriptors_ref_;   // descriptor in reference frame 
    vector<cv::DMatch>      feature_matches_;
    
    SE3d T_c_r_estimated_;  // the estimated pose of current frame 
    int num_inliers_;        // number of inlier features in icp
    int num_lost_;           // number of lost times
    
    // parameters 
    int num_of_features_;   // number of features
    double scale_factor_;   // scale in image pyramid 图像金字塔的尺度
    int level_pyramid_;     // number of pyramid levels 图像金字塔的层级
    float match_ratio_;      // ratio for selecting  good matches 
    int max_num_lost_;      // max number of continuous lost times
    int min_inliers_;       // minimum inliers  最小的内点数
    
    double key_frame_min_rot;   // minimal rotation of two key-frames 两帧间的最小旋转
    double key_frame_min_trans; // minimal translation of two key-frames 两帧间的最小平移
    
public: // functions 
     VisualOdometry();
    ~VisualOdometry();
    
    bool addFrame( Frame::Ptr frame );      // add a new frame 添加一个新的关键帧
    
protected:   //受保护的函数在派生类中可以被访问
    // inner operation 
    void extractKeyPoints();
    void computeDescriptors(); 
    void featureMatching();
    void poseEstimationPnP(); 
    void setRef3DPoints();
    
    void addKeyFrame();
    bool checkEstimatedPose(); 
    bool checkKeyFrame();
    
};
}
#endif // VISUALODOMETRY_H
