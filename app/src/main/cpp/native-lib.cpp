#include <jni.h>
#include <string>
#include <android/native_window_jni.h>

#include "FFDemux.h"
#include "XLog.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"

class TestObs : public IObserver {
public:
    void Update(XData d) override {
        //XLOGI("TestObs Update data size is %d",d.size);
    }
};


IVideoView *view = nullptr;
extern "C"
JNIEXPORT jstring
JNICALL
Java_com_pwjworks_pplayer_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    //XLOGI("S begin!");
    //XSleep(3000);
    //XLOGI("S end!");
    //return env->NewStringUTF(hello.c_str());

    ///////////////////////////////////
    ///测试用代码
    auto *tobs = new TestObs();
    IDemux *de = new FFDemux();
    //de->AddObs(tobs);
    de->Open("/sdcard/v1080.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());
    de->AddObs(vdecode);
    de->AddObs(adecode);

    if (view == nullptr)
        view = new GLVideoView();
    vdecode->AddObs(view);


    //vdecode->Open();
    de->Start();
    vdecode->Start();
    adecode->Start();

    //XSleep(3000);
    //de->Stop();
    /*for(;;)
    {
        XData d = de->Read();
        XLOGI("Read data size is %d",d.size);


    }*/

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_pwjworks_pplayer_PPlay_InitView(JNIEnv *env, jobject thiz, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    if (view == nullptr)
        view = new GLVideoView();
    view->SetRender(win);
    //XEGL::Get()->Init(win);
    //XShader shader;
}