//
// Created by pwjworks on 2022/6/28.
//
#pragma once

#include "XData.h"

/*
 * 解封装接口
 */
class IDemux {
public:
    /**
     * 打开文件，或者流媒体 rmtp http rtsp
     * @param url 文件路径
     * @return
     */
    virtual bool Open(const char *url) = 0;

    /*
     * 读取一帧数据，数据由调用者清理。
     */
    virtual XData Read() = 0;

    /*
     * 总时长(单位毫秒)
     */
    int totalMs = 0;
};
