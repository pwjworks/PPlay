package com.pwjworks.pplayer;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

public class PPlay extends GLSurfaceView implements SurfaceHolder.Callback {

    public PPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        this.setZOrderOnTop(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        // 初始化opengl egl
        InitView(holder.getSurface());
    }


    @Override
    public void surfaceChanged(SurfaceHolder holder, int var1, int var2, int var3) {

    }

    public native void InitView(Object surface);
}
