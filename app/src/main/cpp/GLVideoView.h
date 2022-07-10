//
// Created by pwjworks on 2022/7/2.
//

#pragma once

#include "IVideoView.h"

class XTexture;


class GLVideoView : public IVideoView {
public:
    void SetRender(void *win) override;

    void Render(XData data) override;

protected:
    void *view = nullptr;
    XTexture *txt = nullptr;
};
