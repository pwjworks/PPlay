//
// Created by pwjworks on 2022/7/2.
//

#include "GLVideoView.h"
#include "XTexture.h"
#include "XLog.h"

void GLVideoView::SetRender(void *win) {
    view = win;
}

void GLVideoView::Render(XData data) {
    if (!view) return;
    if (!txt) {
        txt = XTexture::Create();
        txt->Init(view);
    }
    txt->Draw(data.datas, data.width, data.height);
    XLOGE("OK!");
}
