//
// Created by pwjworks on 2022/6/28.
//

#include "XData.h"

extern "C" {
#include <libavformat/avformat.h>
}

void XData::Drop() {
    if (!data) return;
    av_packet_free(reinterpret_cast<AVPacket **>(&data));
    data = nullptr;
    size = 0;
}
