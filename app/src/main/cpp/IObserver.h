//
// Created by pwjworks on 2022/7/1.
//
#pragma once

#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>

/*
 * 观察者和主体
 */
class IObserver : public XThread {
public:
    // 观察者接收数据函数。
    virtual void Update(XData data) {}

    //主体函数，添加观察者，线程安全
    void AddObs(IObserver *obs);

    //通知所有观察者
    void Notify(XData data);

protected:
    std::mutex mux;
    std::vector<IObserver *> obss;
};