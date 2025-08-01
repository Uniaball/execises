package com.uniaball.project1_android;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import com.termux.view.TerminalView;

public class GameActivity extends AppCompatActivity {

    private TerminalView terminalView;
    private EditText inputEditText;
    private Button submitButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        
        // 初始化视图
        terminalView = findViewById(R.id.terminal_view);
        inputEditText = findViewById(R.id.inputEditText);
        submitButton = findViewById(R.id.submitButton);
        
        // 设置终端属性
        configureTerminalView();
        
        // 设置输入监听
        setupInputListeners();
        
        // 启动游戏
        startGame();
    }

    private void configureTerminalView() {
        // 设置终端视图属性
        terminalView.setTextSize(12); // 12sp
        terminalView.setTerminalMargin(4); // 4px
        terminalView.setCursorBlink(true);
        terminalView.setBackgroundColor(getResources().getColor(android.R.color.black));
        terminalView.setTextColor(getResources().getColor(android.R.color.white));
    }

    private void setupInputListeners() {
        // 键盘输入监听
        terminalView.setOnKeyListener((view, keyCode, event) -> {
            if (event.getAction() == KeyEvent.ACTION_DOWN) {
                if (keyCode == KeyEvent.KEYCODE_ENTER) {
                    sendUserInput();
                    return true;
                }
            }
            return false;
        });
        
        // 输入框监听
        inputEditText.setOnEditorActionListener((v, actionId, event) -> {
            if (actionId == EditorInfo.IME_ACTION_SEND) {
                sendUserInput();
                return true;
            }
            return false;
        });
        
        // 提交按钮监听
        submitButton.setOnClickListener(v -> sendUserInput());
    }

    private void sendUserInput() {
        String input = inputEditText.getText().toString().trim();
        if (!input.isEmpty()) {
            // 发送到原生代码
            TerminalBridge.sendInput(input);
            // 清空输入框
            inputEditText.setText("");
        }
    }

    private void startGame() {
        // 设置输出监听器
        TerminalBridge.setOutputListener(this::handleOutput);
        
        // 启动游戏线程
        new Thread(() -> {
            TerminalBridge.startGame();
        }).start();
    }

    private void handleOutput(String text) {
        runOnUiThread(() -> {
            terminalView.append(text);
            // 自动滚动到底部
            terminalView.scrollToEnd();
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // 停止游戏并清理资源
        TerminalBridge.stopGame();
    }
}
