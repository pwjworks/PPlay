#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,"testff",__VA_ARGS__)


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

static double r2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0. : (double) r.num / r.den;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_pwjworks_pplayer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    hello += avcodec_configuration();

    avformat_network_init();

    AVFormatContext *ic = nullptr;
    char path[] = "/sdcard/20051210-w50s.flv";
    int re = avformat_open_input(&ic, path, nullptr, nullptr);
    if (re != 0) {
        LOGW("avformat open input %s failed:%s", path, av_err2str(re));
    }
    LOGW("avformat open input %s success", path);
    re = avformat_find_stream_info(ic, nullptr);
    if (re != 0) {
        LOGW("avformat_open_input %s failed!", path);

    }
    LOGW("duration = %ld nb_stream = %d", ic->duration, ic->nb_streams);
    double fps = 0;
    int width = 0;
    int height = 0;
    int videoStream = 0;
    int audioStream = 0;
    for (int i = 0; i < ic->nb_streams; i++) {
        AVStream *as = ic->streams[i];
        if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            LOGW("视频数据");
            videoStream = i;
            fps = r2d(as->avg_frame_rate);
            LOGW("fps=%f,witdth=%d,height=%d codecid=%d pixformat=%d", fps, as->codecpar->width,
                 as->codecpar->height, as->codecpar->codec_id, as->codecpar->format);
        } else if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            LOGW("音频数据");
            audioStream = i;
            LOGW("sample rate=%d channels=%d sample format=%d",
                 as->codecpar->sample_rate,
                 as->codecpar->channels,
                 as->codecpar->format
            );
        }
    }
    audioStream = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    LOGW("av find best stream audioStream =%d ", audioStream);

    // 解码器
    AVCodec *codec = const_cast<AVCodec *>(avcodec_find_decoder(
            ic->streams[videoStream]->codecpar->codec_id));

    //  硬解码
    AVCodec *hardcodec = const_cast<AVCodec *>(avcodec_find_decoder_by_name("h264_mediacodec"));

    if (!codec) {
        LOGW("avcodec find failed!");
        return env->NewStringUTF(hello.c_str());
    }
    // 解码器初始化
    AVCodecContext *cc = avcodec_alloc_context3(codec);

    avcodec_parameters_to_context(cc, ic->streams[videoStream]->codecpar);
    cc->thread_count = 1;

    re = avcodec_open2(cc, nullptr, nullptr);
    if (re != 0) {
        LOGW("avcodec_open2 failed!");
        return env->NewStringUTF(hello.c_str());
    }

    AVPacket *pkt = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    for (;;) {
        int re = av_read_frame(ic, pkt);

        if (re != 0) {
            LOGW("读取到结尾处！");
//            int pos = 0;
//            av_seek_frame(ic, videoStream, 0,
//                          AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
            break;
        }
        if (pkt->stream_index != videoStream) {
            continue;
        }
        LOGW("stream= %d size= %d pts= %ld flag=%d",
             pkt->stream_index, pkt->size, pkt->pts, pkt->flags
        );
        // 发送到线程中解码
        re = avcodec_send_packet(cc, pkt);
        // 清理
        av_packet_unref(pkt);
        if (re != 0) {
            LOGW("avcodec send packet failed!");
            continue;
        }
        re = avcodec_receive_frame(cc, frame);
        if (re != 0) {
            LOGW("avcodec receive frame failed!");
            continue;
        }
        LOGW("avcodec receive frame %ld", frame->pts);
    }
    avformat_close_input(&ic);
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_pwjworks_pplayer_MainActivity_Open(JNIEnv *env, jobject thiz, jstring url,
                                            jobject handle) {
    const char *url_ = env->GetStringUTFChars(url, nullptr);
    printf("%s", url_);
    FILE *fp = fopen(url_, "rb");
    if (!fp) {
        LOGW("%s open failed!", url_);
    } else {
        LOGW("%s open success!", url_);
        fclose(fp);
    }
    env->ReleaseStringUTFChars(url, url_);
    return static_cast<jboolean>(true);
}