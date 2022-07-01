//
// Created by pwjworks on 2022/6/28.
//

#include "FFDemux.h"
#include "XLog.h"

extern "C" {
#include <libavformat/avformat.h>
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        // 初始化网络
        avformat_network_init();
        XLOGI("register ffmpeg.");
    }
}

bool FFDemux::Open(const char *url) {
    XLOGW("Open file %s begin", url);
    // 打开文件
    int re = avformat_open_input(&ic, url, nullptr, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("FFDemux open %s failed!", url);
        return false;
    }
    XLOGE("FFDemux open %s success!", url);
    // 读取文件信息
    re = avformat_find_stream_info(ic, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGE("Avformat_find_stream_info open %s failed!", url);
        return false;
    }
    // 视频总时长
    this->totalMs = ic->duration / (AV_TIME_BASE / 1000);
    XLOGI("total ms= %d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1", this->totalMs);
    return false;
}

XData FFDemux::Read() {
    if (!ic) return {};
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0) {
        av_packet_free(&pkt);
        return {};
    }
    XLOGI("pack size is %d ptss %ld", pkt->size, pkt->pts);
    d.data = reinterpret_cast<unsigned char *>(pkt);
    d.size = pkt->size;
    return d;
}

