package com.uniaball.project1_android;

public class JNIUtils {
    
    // 本地方法声明
    public static native long getNativePointer(Object obj);
    
    public static native void releaseNativePointer(long ptr);
    
    // 设置回调方法
    public interface NativeObjectCallback {
        void callbackMethod(String message);
    }
}