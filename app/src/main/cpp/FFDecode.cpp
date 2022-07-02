//
// Created by pwjworks on 2022/7/2.
//
extern "C" {
#include <libavcodec/avcodec.h>
}

#include "FFDecode.h"
#include "XLog.h"

bool FFDecode::Open(XParameter para) {
    if (!para.para) return false;
    AVCodecParameters *p = para.para;

    // 查找解码器
    auto *cd = const_cast<AVCodec *>(avcodec_find_decoder(p->codec_id));
    if (!cd) {
        XLOGE("avcodec_find_decoder %d failed!", p->codec_id);
    }
    XLOGI("avccodec_find_decoder success!");
    // 创建解码上下文，并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);

    codec->thread_count = 8;
    // 打开解码器
    int re = avcodec_open2(codec, nullptr, nullptr);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf) - 1);
        XLOGE("%s", buf);
        return false;
    }
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        this->isAudio = false;
    } else {
        this->isAudio = true;
    }
    XLOGI("avcodec_open2 success!");
    return false;
}

bool FFDecode::SendPacket(XData pkt) {
    if (!codec || pkt.size <= 0 || !pkt.data)return false;
    if (!codec) {
        return false;
    }

    int re = avcodec_send_packet(codec, reinterpret_cast<AVPacket *>(pkt.data));
    if (re != 0) {
        return false;
    }


    return true;
}

XData FFDecode::RecvFrame() {
    if (!codec)return {};
    if (!frame) frame = av_frame_alloc();
    int re = avcodec_receive_frame(codec, frame);
    if (re != 0) {
        return {};
    }
    XData d;
    d.data = reinterpret_cast<unsigned char *>(frame);
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO)
        d.size = frame->linesize[0] + frame->linesize[1] + frame->linesize[2];
    else
        // 样本大小 * 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
    return d;
}
