//
// Created by pwjworks on 2022/6/28.
//
#pragma once

#include "IDemux.h"

struct AVFormatContext;

class FFDemux : public IDemux {
public:
    FFDemux();

    XParameter GetVPara() override;

    XParameter GetAPara() override;

    bool Open(const char *url) override;

    XData Read() override;

private:
    AVFormatContext *ic = 0;
    int audioStream = 1;
    int videoStream = 0;
};
