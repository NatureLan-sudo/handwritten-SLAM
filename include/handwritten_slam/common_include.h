/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-01 13:32:15
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-08 16:26:34
 * @FilePath: /handwritten-SLAM/include/handwritten_slam/common_include.h
 * @Description: 添加常用的头文件
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#ifndef COMMON_INCLUDE_H
#define COMMON_INCLUDE_H
// for Eigen
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
using namespace Eigen;
//for sophus
#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
using namespace Sophus;

//for opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

//for std
#include <iostream>
#include <vector>
#include <list>
#include <memory>  //智能指针
#include <unordered_map>
#include <string>
#include <set>
#include <map>
using namespace std;


#endif//COMMON_INCLUDE_H
