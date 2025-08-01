package com.uniaball.project1_android;

public class TerminalBridge {
    static {
        System.loadLibrary("uniball-game");
    }

    public interface OutputListener {
        void onOutput(String text);
    }

    private static OutputListener listener;

    public static void setOutputListener(OutputListener l) {
        listener = l;
    }

    // 被 C++ 调用
    public static void outputText(String text) {
        if (listener != null) {
            listener.onOutput(text);
        }
    }

    // 发送输入到 C++
    public native static void sendInput(String input);
    
    // 启动游戏
    public native static void startGame();
    
    // 停止游戏
    public native static void stopGame();
}