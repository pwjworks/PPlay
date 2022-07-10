//
// Created by pwjworks on 2022/7/2.
//

#pragma once

#include "XData.h"
#include "IObserver.h"

class IVideoView : public IObserver {
public:
    virtual void SetRender(void *win) = 0;

    virtual void Render(XData data) = 0;

    virtual void Update(XData data);
};