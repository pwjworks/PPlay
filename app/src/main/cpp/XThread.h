//
// Created by pwjworks on 2022/7/1.
//
#pragma once

// sleep 毫秒
void XSleep(int mis);

class XThread {
public:
    /**
     * 启动线程
     */
    virtual void Start();

    /**
     * 通过控制isExit安全停止线程
     */
    virtual void Stop();

    /**
     * 入口主函数
     */
    virtual void Main() {}

protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void ThreadMain();
};