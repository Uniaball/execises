package com.uniaball.project1_android;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import com.termux.view.TerminalView;
import com.termux.terminal.TerminalSession;
import com.termux.terminal.TerminalBuffer;

public class GameActivity extends AppCompatActivity implements TerminalBridge.OutputListener {
    private TerminalView terminalView;
    private TerminalBridge terminalBridge;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        
        // ��ʼ���ն���ͼ
        terminalView = findViewById(R.id.terminal_view);
        terminalView.setTextSize(14);
        terminalView.setEmitCtrlKeyOnVolumeDown(false);
        
        // ��ʼ���ն��Ž�
        terminalBridge = new TerminalBridge();
        terminalBridge.setOutputListener(this);
        
        // ���ü����������
        terminalView.setOnKeyListener((view, keyCode, event) -> {
            if (event.getAction() == KeyEvent.ACTION_DOWN) {
                handleKeyEvent(keyCode, event);
            }
            return true;
        });
        
        // ������Ϸ
        terminalBridge.startGame();
        terminalView.append("\n��Ϸ������! �뿪ʼ��Ϸ...\n");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        terminalBridge.stopGame();
    }

    @Override
    public void onOutput(String text) {
        runOnUiThread(() -> {
            terminalView.append(text);
        });
    }

    private void handleKeyEvent(int keyCode, KeyEvent event) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_NUMPAD_ENTER:
                handleSubmit();
                break;
            case KeyEvent.KEYCODE_DEL:
                handleBackspace();
                break;
            default:
                char inputChar = (char) event.getUnicodeChar();
                handleCharacter(inputChar);
                break;
        }
    }

    private void handleCharacter(char c) {
        TerminalBuffer buffer = terminalView.getCurrentTerminalBuffer();
        buffer.setChar(buffer.getCursorX(), buffer.getCursorY(), c);
        buffer.setCursorX(buffer.getCursorX() + 1);
        terminalView.invalidate();
    }

    private void handleBackspace() {
        TerminalBuffer buffer = terminalView.getCurrentTerminalBuffer();
        if (buffer.getCursorX() > 0) {
            buffer.setCursorX(buffer.getCursorX() - 1);
            buffer.setChar(buffer.getCursorX(), buffer.getCursorY(), ' ');
            terminalView.invalidate();
        }
    }

    private void handleSubmit() {
        TerminalBuffer buffer = terminalView.getCurrentTerminalBuffer();
        StringBuilder inputBuilder = new StringBuilder();
        
        // ��ȡ��ǰ������
        int cursorY = buffer.getCursorY();
        for (int i = 0; i < buffer.getCursorX(); i++) {
            char c = buffer.getChar(i, cursorY);
            if (c != 0) {
                inputBuilder.append(c);
            }
        }
        
        String input = inputBuilder.toString().trim();
        if (!input.isEmpty()) {
            // �������뵽��Ϸ�߼�
            terminalBridge.sendInput(input);
        }
        
        // ���������
        for (int i = 0; i < buffer.getCursorX(); i++) {
            buffer.setChar(i, cursorY, ' ');
        }
        buffer.setCursorX(0);
        terminalView.invalidate();
    }
}
