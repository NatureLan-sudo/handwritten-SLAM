/*
 * @Author: NatureLan-sudo lantianran282@163.com
 * @Date: 2022-09-08 16:15:30
 * @LastEditors: NatureLan-sudo lantianran282@163.com
 * @LastEditTime: 2022-09-08 22:06:03
 * @FilePath: /handwritten-SLAM/include/handwritten_slam/config.h
 * @Description: 
 * 
 * Copyright (c) 2022 by NatureLan-sudo lantianran282@163.com, All Rights Reserved. 
 */
#ifndef CONFIG_H
#define CONFIG_H
#include "common_include.h"
namespace myslam 
{
class Config
{
private:
    static std::shared_ptr<Config> config_; 
    cv::FileStorage file_;
    
    Config () {}// private constructor makes a singleton
public:
    ~Config();  // close the file when deconstructing  析构函数设为私有，创建单例模型
    
    // set a new config file 
    static void setParameterFile( const std::string& filename );
    
    // access the parameter values
    template<  typename T >
    static T get( const std::string& key )
    {
        return T( Config::config_->file_[key] );
    }
};

}

#endif // CONFIG_H