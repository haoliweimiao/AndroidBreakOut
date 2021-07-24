package com.von.breakout;

import android.app.NativeActivity;

public class OpenGLNativeActivity extends NativeActivity {

    static {
        System.loadLibrary("BreakOut");
    }
}
