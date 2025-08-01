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

    // �� C++ ����
    public static void outputText(String text) {
        if (listener != null) {
            listener.onOutput(text);
        }
    }

    // �������뵽 C++
    public native static void sendInput(String input);
    
    // ������Ϸ
    public native static void startGame();
    
    // ֹͣ��Ϸ
    public native static void stopGame();
}