/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 21:01:56
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-08 16:15:00
 * @FilePath: /handwritten-SLAM/include/handwritten_slam/Map.h
 * @Description: 地图相关的类
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#ifndef MAP_H
#define MAP_H
#include "common_include.h"
#include "Frame.h"
#include "MapPoint.h"
namespace myslam {
    class Map {
        public: 
        typedef shared_ptr<Map> Ptr;
        // 每一个点、每一个关键帧都是用自己类定义的智能指针管理的
        // 下面定义了两个map， 第一项是id ，第二是对应的指针
        unordered_map<unsigned long, MapPoint::Ptr >  map_points_;        // all landmarks
        unordered_map<unsigned long, Frame::Ptr >     keyframes_;         // all key-frames 
        Map();
        void insertKeyFrame ( Frame::Ptr frame);
        void insertMapPoint ( MapPoint::Ptr map_point);
        private:

    };
}

#endif //MAP_H