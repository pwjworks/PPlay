//
// Created by pwjworks on 2022/6/28.
//
#pragma once

#include "XData.h"
#include "IObserver.h"
#include "XParameter.h"

/*
 * 解封装接口
 */
class IDemux : public IObserver {
public:
    /**
     * 打开文件，或者流媒体 rmtp http rtsp
     * @param url 文件路径
     * @return
     */
    virtual bool Open(const char *url) = 0;

    // 获取视频参数
    virtual XParameter GetVPara() = 0;

    // 获取音频参数
    virtual XParameter GetAPara() = 0;

    // 读取一帧数据，数据由调用者清理。
    virtual XData Read() = 0;

    // 总时长(单位毫秒)
    int totalMs = 0;

protected:
    void Main() override;
};
