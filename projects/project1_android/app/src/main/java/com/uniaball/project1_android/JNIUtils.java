package com.uniaball.project1_android;

public class JNIUtils {
    
    // ���ط�������
    public static native long getNativePointer(Object obj);
    
    public static native void releaseNativePointer(long ptr);
    
    // ���ûص�����
    public interface NativeObjectCallback {
        void callbackMethod(String message);
    }
}