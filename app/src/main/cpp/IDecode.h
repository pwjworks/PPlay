//
// Created by pwjworks on 2022/7/2.
//

#pragma once

#include "XParameter.h"
#include "IObserver.h"
#include <list>

// 解码接口，支持硬解码
class IDecode : public IObserver {
public:
    // 打开解码器
    virtual bool Open(XParameter para) = 0;

    // future模型 发送数据到线程解码
    virtual bool SendPacket(XData pkt) = 0;

    // 从线程中获取解码结果，再次调用会服用上次空间，线程不安全
    virtual XData RecvFrame() = 0;

    void Update(XData pkt) override;

    bool isAudio = false;

    // 最大的队列缓冲
    int maxList = 100;

protected:
    void Main() override;

    std::list<XData> packs;
    std::mutex packsMutex;
};

