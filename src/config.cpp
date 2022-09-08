/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-08 21:56:52
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-08 22:21:01
 * @FilePath: /handwritten-SLAM/src/config.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#include "config.h"
namespace myslam {
/**
 * @description: 从配置文件中读取信息 
 * @param {string&} filename
 * @return {*}
 */    
void Config::setParameterFile( const std::string& filename )
{
    if ( config_ == nullptr )
        config_ = shared_ptr<Config>(new Config);  //如果指向参数设置文件的指针为空，创建新的指针
    config_->file_ = cv::FileStorage( filename.c_str(), cv::FileStorage::READ );  // 利用智能指针以及cv提供的功能，读取config文件的内容
    if ( config_->file_.isOpened() == false )  // 检查文件不存在的报错
    {
        std::cerr<<"parameter file "<<filename<<" does not exist."<<std::endl;
        config_->file_.release();
        return;
    }
}

/**
 * @description: 析构函数，将打开的文件释放掉
 * @return {*}
 */
Config::~Config()
{
    if ( file_.isOpened() )
        file_.release();
}
shared_ptr<Config> Config::config_ = nullptr;   //初始化成员变量为null

}