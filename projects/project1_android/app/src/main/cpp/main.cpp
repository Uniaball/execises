#include <jni.h>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

// 全局变量
mutex input_mutex;
condition_variable input_cv;
queue<string> input_queue;
bool game_running = true;

// 输出回调函数指针
void (*output_callback)(const char*) = nullptr;

// 替换 Windows Sleep
void Sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// 自定义输出函数
void android_print(const string& msg) {
    if (output_callback) {
        output_callback(msg.c_str());
    }
}

// 重定向 cout
class AndroidStream : public streambuf {
public:
    virtual streamsize xsputn(const char_type* s, streamsize n) override {
        string msg(s, n);
        android_print(msg);
        return n;
    }

    virtual int_type overflow(int_type c) override {
        if (c != EOF) {
            char msg = static_cast<char>(c);
            android_print(string(&msg, 1));
        }
        return c;
    }
};

// 游戏主逻辑
void gameMain() {
    // 初始化随机数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 2);

    // 游戏状态变量
    bool LeftHandWin = false;
    bool RightHandWin = false;
    bool LeftHandWin2 = false;
    bool RightHandWin2 = false;

    android_print("游戏开始\n");

    // 初始化左右手
    short LeftNum = 1, RightNum = 1;
    android_print("这是你的两个手，左、右手此时都是1\n");
    android_print("左：1 右：1\n");

    short LeftNum2 = 1, RightNum2 = 1;
    android_print("这是你的对手（弱智ai）的左、右手\n");
    android_print("左：1 右：1\n");

    // 选择自己出的手
    while (game_running) {
        android_print("选择你的一只手（输入L或R）\n");

        bool ChooseLeftHand = false;
        bool ChooseRightHand = false;
        char Choice;

        // 获取用户输入
        string user_input;
        {
            unique_lock<mutex> lock(input_mutex);
            input_cv.wait(lock, [] { return !input_queue.empty(); });
            user_input = input_queue.front();
            input_queue.pop();
        }

        if (user_input.length() > 0) {
            Choice = toupper(user_input[0]);
        }
        else {
            Choice = ' ';
        }

        switch (Choice) {
        case 'L': {
            if (!LeftHandWin) {
                ChooseLeftHand = true;
                android_print("你选择了左手（" + to_string(LeftNum) + ")\n");
            }
            else {
                android_print("这只手已经赢了捏，帮你选右手了\n");
                Sleep(500);
                ChooseRightHand = true;
                android_print("你选择了右手（" + to_string(RightNum) + "）\n");
            }
            break;
        }
        case 'R': {
            if (!RightHandWin) {
                ChooseRightHand = true;
                android_print("你选择了右手（" + to_string(RightNum) + "）\n");
            }
            else {
                android_print("这只手已经赢了捏，帮你选左手了\n");
                Sleep(500);
                ChooseLeftHand = true;
                android_print("你选择了左手（" + to_string(LeftNum) + "）\n");
            }
            break;
        }
        default: {
            android_print("无效输入，请重新输入\n");
            continue;
        }
        }

        // 加ai哪只手
        android_print("你要加ai的哪只手（输入L或R）\n");

        // 获取用户输入
        {
            unique_lock<mutex> lock(input_mutex);
            input_cv.wait(lock, [] { return !input_queue.empty(); });
            user_input = input_queue.front();
            input_queue.pop();
        }

        char ChooseHand = ' ';
        if (user_input.length() > 0) {
            ChooseHand = toupper(user_input[0]);
        }

        switch (ChooseHand) {
        case 'L': {
            if (!LeftHandWin2) {
                if (ChooseLeftHand) {
                    android_print("你选择了ai的左手（" + to_string(LeftNum2) + ")\n");
                    LeftNum += LeftNum2;
                    if (LeftNum > 10) LeftNum -= 10;
                    android_print("计算完毕，此时你的左手是：" + to_string(LeftNum) + "\n");
                }
                else if (ChooseRightHand) {
                    android_print("你选择了ai的左手（" + to_string(LeftNum2) + ")\n");
                    RightNum += LeftNum2;
                    if (RightNum > 10) RightNum -= 10;
                    android_print("计算完毕，此时你的右手是：" + to_string(RightNum) + "\n");
                }
            }
            else {
                android_print("AI的左手已经获胜，不能选择\n");
            }
            break;
        }
        case 'R': {
            if (!RightHandWin2) {
                if (ChooseLeftHand) {
                    android_print("你选择了ai的右手（" + to_string(RightNum2) + ")\n");
                    LeftNum += RightNum2;
                    if (LeftNum > 10) LeftNum -= 10;
                    android_print("计算完毕，此时你的左手是：" + to_string(LeftNum) + "\n");
                }
                else if (ChooseRightHand) {
                    android_print("你选择了ai的右手（" + to_string(RightNum2) + ")\n");
                    RightNum += RightNum2;
                    if (RightNum > 10) RightNum -= 10;
                    android_print("计算完毕，此时你的右手是：" + to_string(RightNum) + "\n");
                }
            }
            else {
                android_print("AI的右手已经获胜，不能选择\n");
            }
            break;
        }
        default: {
            android_print("无效输入，请重新输入\n");
            continue;
        }
        }

        // 显示左右手
        android_print("这是你的左、右手\n");
        android_print("左：" + to_string(LeftNum) + " 右：" + to_string(RightNum) + "\n");

        android_print("这是ai的左、右手\n");
        android_print("左：" + to_string(LeftNum2) + " 右：" + to_string(RightNum2) + "\n");

        // AI回合
        android_print("ai回合\n");
        Sleep(2000);

        short RandomSelfHandChoice = dist(gen);
        short RandomHandChoice = dist(gen);
        bool aiActionTaken = false;

        // AI选择自己的手
        if (RandomSelfHandChoice == 1 && !LeftHandWin2) {
            android_print("ai使用了左手（" + to_string(LeftNum2) + "）\n");
            Sleep(2000);

            // AI选择玩家的手
            if (RandomHandChoice == 1 && !LeftHandWin) {
                android_print("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                LeftNum2 += LeftNum;
                if (LeftNum2 > 10) LeftNum2 -= 10;
                Sleep(2000);
                android_print("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                aiActionTaken = true;
            }
            else if (!RightHandWin) {
                android_print("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                LeftNum2 += RightNum;
                if (LeftNum2 > 10) LeftNum2 -= 10;
                Sleep(2000);
                android_print("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                aiActionTaken = true;
            }
        }
        else if (RandomSelfHandChoice == 2 && !RightHandWin2) {
            android_print("ai使用了右手（" + to_string(RightNum2) + "）\n");
            Sleep(2000);

            // AI选择玩家的手
            if (RandomHandChoice == 1 && !LeftHandWin) {
                android_print("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                RightNum2 += LeftNum;
                if (RightNum2 > 10) RightNum2 -= 10;
                Sleep(2000);
                android_print("ai此时右手的数：" + to_string(RightNum2) + "\n");
                aiActionTaken = true;
            }
            else if (!RightHandWin) {
                android_print("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                RightNum2 += RightNum;
                if (RightNum2 > 10) RightNum2 -= 10;
                Sleep(2000);
                android_print("ai此时右手的数：" + to_string(RightNum2) + "\n");
                aiActionTaken = true;
            }
        }

        // 如果AI没有执行动作，尝试另一只手
        if (!aiActionTaken) {
            if (RandomSelfHandChoice == 1 && !RightHandWin2) {
                android_print("ai改用了右手（" + to_string(RightNum2) + "）\n");
                Sleep(2000);

                if (RandomHandChoice == 1 && !LeftHandWin) {
                    android_print("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                    RightNum2 += LeftNum;
                    if (RightNum2 > 10) RightNum2 -= 10;
                    Sleep(2000);
                    android_print("ai此时右手的数：" + to_string(RightNum2) + "\n");
                }
                else if (!RightHandWin) {
                    android_print("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                    RightNum2 += RightNum;
                    if (RightNum2 > 10) RightNum2 -= 10;
                    Sleep(2000);
                    android_print("ai此时右手的数：" + to_string(RightNum2) + "\n");
                }
            }
            else if (RandomSelfHandChoice == 2 && !LeftHandWin2) {
                android_print("ai改用了左手（" + to_string(LeftNum2) + "）\n");
                Sleep(2000);

                if (RandomHandChoice == 1 && !LeftHandWin) {
                    android_print("ai选择了你的左手（" + to_string(LeftNum) + "）\n");
                    LeftNum2 += LeftNum;
                    if (LeftNum2 > 10) LeftNum2 -= 10;
                    Sleep(2000);
                    android_print("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                }
                else if (!RightHandWin) {
                    android_print("ai选择了你的右手（" + to_string(RightNum) + "）\n");
                    LeftNum2 += RightNum;
                    if (LeftNum2 > 10) LeftNum2 -= 10;
                    Sleep(2000);
                    android_print("ai此时左手的数：" + to_string(LeftNum2) + "\n");
                }
            }
        }

        // 显示左右手
        android_print("这是你的左、右手\n");
        android_print("左：" + to_string(LeftNum) + " 右：" + to_string(RightNum) + "\n");

        android_print("这是ai的左、右手\n");
        android_print("左：" + to_string(LeftNum2) + " 右：" + to_string(RightNum2) + "\n");

        // 获胜条件
        if (LeftNum == 10 && !LeftHandWin) {
            LeftHandWin = true;
            android_print("你的左手已获胜，将不可用\n");
            if (RightHandWin) {
                android_print("你已获胜！\n");
                return;
            }
        }

        if (RightNum == 10 && !RightHandWin) {
            RightHandWin = true;
            android_print("你的右手已获胜，将不可用\n");
            if (LeftHandWin) {
                android_print("你已获胜！\n");
                return;
            }
        }

        if (LeftNum2 == 10 && !LeftHandWin2) {
            LeftHandWin2 = true;
            android_print("ai的左手已获胜，将不可用\n");
            if (RightHandWin2) {
                android_print("你输了！\n");
                return;
            }
        }

        if (RightNum2 == 10 && !RightHandWin2) {
            RightHandWin2 = true;
            android_print("ai的右手已获胜，将不可用\n");
            if (LeftHandWin2) {
                android_print("你输了！\n");
                return;
            }
        }
    }
}

// JNI 函数
extern "C" JNIEXPORT void JNICALL
Java_com_uniaball_project1_1android_GameActivity_startGame(
    JNIEnv* env,
    jobject /* this */) {
    // 重定向输出
    static AndroidStream androidStream;
    cout.rdbuf(&androidStream);

    // 启动游戏线程
    thread game_thread([] {
        gameMain();
        });
    game_thread.detach();
}

extern "C" JNIEXPORT void JNICALL
Java_com_uniaball_project1_1android_GameActivity_sendInput(
    JNIEnv* env,
    jobject /* this */,
    jstring input) {
    const char* chars = env->GetStringUTFChars(input, nullptr);
    string input_str(chars);
    env->ReleaseStringUTFChars(input, chars);

    lock_guard<mutex> lock(input_mutex);
    input_queue.push(input_str);
    input_cv.notify_one();
}

extern "C" JNIEXPORT void JNICALL
Java_com_uniaball_project1_1android_GameActivity_setOutputCallback(
    JNIEnv* env,
    jobject /* this */,
    jlong callback_ptr) {
    output_callback = reinterpret_cast<void (*)(const char*)>(callback_ptr);
}

extern "C" JNIEXPORT void JNICALL
Java_com_uniaball_project1_1android_GameActivity_stopGame(
    JNIEnv* env,
    jobject /* this */) {
    game_running = false;
    // 唤醒任何等待输入的线程
    input_cv.notify_all();
}