/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 21:03:20
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-08 16:02:05
 * @FilePath: /handwritten-SLAM/include/handwritten_slam/MapPoint.h
 * @Description: 地图点相关的类
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#ifndef  MAPPIONT_H
#define MAPPIONT_H
#include "common_include.h"
namespace myslam
{
    class MapPoint
    {
    private:
    /* data */
    public:
    typedef shared_ptr<MapPoint> Ptr;
    unsigned long      id_; // ID
    Vector3d    pos_;          // Position in world
    Vector3d    norm_;      // Normal of viewing direction 
    Mat         descriptor_; // Descriptor for matching 
    int         observed_times_;    // being observed by feature matching algo.
    int         matched_times_;     // being an inliner in pose estimation
    MapPoint(); // 初始构造函数
    MapPoint( long id, Vector3d position, Vector3d norm);  // 构造函数重载
    //
    static MapPoint::Ptr createMapPiont(); // 函数内部创建智能指针，并需要在函数外使用？
    };

}
#endif //namespace myslam