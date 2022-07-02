//
// Created by pwjworks on 2022/7/2.
//

#pragma oncce

#include "IDecode.h"


struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:
    bool Open(XParameter para) override;

    bool SendPacket(XData pkt) override;

    XData RecvFrame() override;

protected:
    AVCodecContext *codec = nullptr;
    AVFrame *frame = nullptr;
};