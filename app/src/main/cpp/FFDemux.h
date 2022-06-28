//
// Created by pwjworks on 2022/6/28.
//
#pragma once

#include "IDemux.h"

class FFDemux : public IDemux {
public:
    bool Open(const char *url) override;

    XData Read() override;
};
