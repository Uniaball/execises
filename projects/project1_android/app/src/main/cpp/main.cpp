#include <jni.h>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

// ȫ�ֱ���
mutex input_mutex;
condition_variable input_cv;
queue<string> input_queue;
bool game_running = true;

// ����ص�����ָ��
void (*output_callback)(const char*) = nullptr;

// �滻 Windows Sleep
void Sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// �Զ����������
void android_print(const string& msg) {
    if (output_callback) {
        output_callback(msg.c_str());
    }
}

// �ض��� cout
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

// ��Ϸ���߼�
void gameMain() {
    // ��ʼ�������������
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 2);

    // ��Ϸ״̬����
    bool LeftHandWin = false;
    bool RightHandWin = false;
    bool LeftHandWin2 = false;
    bool RightHandWin2 = false;

    android_print("��Ϸ��ʼ\n");

    // ��ʼ��������
    short LeftNum = 1, RightNum = 1;
    android_print("������������֣������ִ�ʱ����1\n");
    android_print("��1 �ң�1\n");

    short LeftNum2 = 1, RightNum2 = 1;
    android_print("������Ķ��֣�����ai����������\n");
    android_print("��1 �ң�1\n");

    // ѡ���Լ�������
    while (game_running) {
        android_print("ѡ�����һֻ�֣�����L��R��\n");

        bool ChooseLeftHand = false;
        bool ChooseRightHand = false;
        char Choice;

        // ��ȡ�û�����
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
                android_print("��ѡ�������֣�" + to_string(LeftNum) + ")\n");
            }
            else {
                android_print("��ֻ���Ѿ�Ӯ���󣬰���ѡ������\n");
                Sleep(500);
                ChooseRightHand = true;
                android_print("��ѡ�������֣�" + to_string(RightNum) + "��\n");
            }
            break;
        }
        case 'R': {
            if (!RightHandWin) {
                ChooseRightHand = true;
                android_print("��ѡ�������֣�" + to_string(RightNum) + "��\n");
            }
            else {
                android_print("��ֻ���Ѿ�Ӯ���󣬰���ѡ������\n");
                Sleep(500);
                ChooseLeftHand = true;
                android_print("��ѡ�������֣�" + to_string(LeftNum) + "��\n");
            }
            break;
        }
        default: {
            android_print("��Ч���룬����������\n");
            continue;
        }
        }

        // ��ai��ֻ��
        android_print("��Ҫ��ai����ֻ�֣�����L��R��\n");

        // ��ȡ�û�����
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
                    android_print("��ѡ����ai�����֣�" + to_string(LeftNum2) + ")\n");
                    LeftNum += LeftNum2;
                    if (LeftNum > 10) LeftNum -= 10;
                    android_print("������ϣ���ʱ��������ǣ�" + to_string(LeftNum) + "\n");
                }
                else if (ChooseRightHand) {
                    android_print("��ѡ����ai�����֣�" + to_string(LeftNum2) + ")\n");
                    RightNum += LeftNum2;
                    if (RightNum > 10) RightNum -= 10;
                    android_print("������ϣ���ʱ��������ǣ�" + to_string(RightNum) + "\n");
                }
            }
            else {
                android_print("AI�������Ѿ���ʤ������ѡ��\n");
            }
            break;
        }
        case 'R': {
            if (!RightHandWin2) {
                if (ChooseLeftHand) {
                    android_print("��ѡ����ai�����֣�" + to_string(RightNum2) + ")\n");
                    LeftNum += RightNum2;
                    if (LeftNum > 10) LeftNum -= 10;
                    android_print("������ϣ���ʱ��������ǣ�" + to_string(LeftNum) + "\n");
                }
                else if (ChooseRightHand) {
                    android_print("��ѡ����ai�����֣�" + to_string(RightNum2) + ")\n");
                    RightNum += RightNum2;
                    if (RightNum > 10) RightNum -= 10;
                    android_print("������ϣ���ʱ��������ǣ�" + to_string(RightNum) + "\n");
                }
            }
            else {
                android_print("AI�������Ѿ���ʤ������ѡ��\n");
            }
            break;
        }
        default: {
            android_print("��Ч���룬����������\n");
            continue;
        }
        }

        // ��ʾ������
        android_print("�������������\n");
        android_print("��" + to_string(LeftNum) + " �ң�" + to_string(RightNum) + "\n");

        android_print("����ai��������\n");
        android_print("��" + to_string(LeftNum2) + " �ң�" + to_string(RightNum2) + "\n");

        // AI�غ�
        android_print("ai�غ�\n");
        Sleep(2000);

        short RandomSelfHandChoice = dist(gen);
        short RandomHandChoice = dist(gen);
        bool aiActionTaken = false;

        // AIѡ���Լ�����
        if (RandomSelfHandChoice == 1 && !LeftHandWin2) {
            android_print("aiʹ�������֣�" + to_string(LeftNum2) + "��\n");
            Sleep(2000);

            // AIѡ����ҵ���
            if (RandomHandChoice == 1 && !LeftHandWin) {
                android_print("aiѡ����������֣�" + to_string(LeftNum) + "��\n");
                LeftNum2 += LeftNum;
                if (LeftNum2 > 10) LeftNum2 -= 10;
                Sleep(2000);
                android_print("ai��ʱ���ֵ�����" + to_string(LeftNum2) + "\n");
                aiActionTaken = true;
            }
            else if (!RightHandWin) {
                android_print("aiѡ����������֣�" + to_string(RightNum) + "��\n");
                LeftNum2 += RightNum;
                if (LeftNum2 > 10) LeftNum2 -= 10;
                Sleep(2000);
                android_print("ai��ʱ���ֵ�����" + to_string(LeftNum2) + "\n");
                aiActionTaken = true;
            }
        }
        else if (RandomSelfHandChoice == 2 && !RightHandWin2) {
            android_print("aiʹ�������֣�" + to_string(RightNum2) + "��\n");
            Sleep(2000);

            // AIѡ����ҵ���
            if (RandomHandChoice == 1 && !LeftHandWin) {
                android_print("aiѡ����������֣�" + to_string(LeftNum) + "��\n");
                RightNum2 += LeftNum;
                if (RightNum2 > 10) RightNum2 -= 10;
                Sleep(2000);
                android_print("ai��ʱ���ֵ�����" + to_string(RightNum2) + "\n");
                aiActionTaken = true;
            }
            else if (!RightHandWin) {
                android_print("aiѡ����������֣�" + to_string(RightNum) + "��\n");
                RightNum2 += RightNum;
                if (RightNum2 > 10) RightNum2 -= 10;
                Sleep(2000);
                android_print("ai��ʱ���ֵ�����" + to_string(RightNum2) + "\n");
                aiActionTaken = true;
            }
        }

        // ���AIû��ִ�ж�����������һֻ��
        if (!aiActionTaken) {
            if (RandomSelfHandChoice == 1 && !RightHandWin2) {
                android_print("ai���������֣�" + to_string(RightNum2) + "��\n");
                Sleep(2000);

                if (RandomHandChoice == 1 && !LeftHandWin) {
                    android_print("aiѡ����������֣�" + to_string(LeftNum) + "��\n");
                    RightNum2 += LeftNum;
                    if (RightNum2 > 10) RightNum2 -= 10;
                    Sleep(2000);
                    android_print("ai��ʱ���ֵ�����" + to_string(RightNum2) + "\n");
                }
                else if (!RightHandWin) {
                    android_print("aiѡ����������֣�" + to_string(RightNum) + "��\n");
                    RightNum2 += RightNum;
                    if (RightNum2 > 10) RightNum2 -= 10;
                    Sleep(2000);
                    android_print("ai��ʱ���ֵ�����" + to_string(RightNum2) + "\n");
                }
            }
            else if (RandomSelfHandChoice == 2 && !LeftHandWin2) {
                android_print("ai���������֣�" + to_string(LeftNum2) + "��\n");
                Sleep(2000);

                if (RandomHandChoice == 1 && !LeftHandWin) {
                    android_print("aiѡ����������֣�" + to_string(LeftNum) + "��\n");
                    LeftNum2 += LeftNum;
                    if (LeftNum2 > 10) LeftNum2 -= 10;
                    Sleep(2000);
                    android_print("ai��ʱ���ֵ�����" + to_string(LeftNum2) + "\n");
                }
                else if (!RightHandWin) {
                    android_print("aiѡ����������֣�" + to_string(RightNum) + "��\n");
                    LeftNum2 += RightNum;
                    if (LeftNum2 > 10) LeftNum2 -= 10;
                    Sleep(2000);
                    android_print("ai��ʱ���ֵ�����" + to_string(LeftNum2) + "\n");
                }
            }
        }

        // ��ʾ������
        android_print("�������������\n");
        android_print("��" + to_string(LeftNum) + " �ң�" + to_string(RightNum) + "\n");

        android_print("����ai��������\n");
        android_print("��" + to_string(LeftNum2) + " �ң�" + to_string(RightNum2) + "\n");

        // ��ʤ����
        if (LeftNum == 10 && !LeftHandWin) {
            LeftHandWin = true;
            android_print("��������ѻ�ʤ����������\n");
            if (RightHandWin) {
                android_print("���ѻ�ʤ��\n");
                return;
            }
        }

        if (RightNum == 10 && !RightHandWin) {
            RightHandWin = true;
            android_print("��������ѻ�ʤ����������\n");
            if (LeftHandWin) {
                android_print("���ѻ�ʤ��\n");
                return;
            }
        }

        if (LeftNum2 == 10 && !LeftHandWin2) {
            LeftHandWin2 = true;
            android_print("ai�������ѻ�ʤ����������\n");
            if (RightHandWin2) {
                android_print("�����ˣ�\n");
                return;
            }
        }

        if (RightNum2 == 10 && !RightHandWin2) {
            RightHandWin2 = true;
            android_print("ai�������ѻ�ʤ����������\n");
            if (LeftHandWin2) {
                android_print("�����ˣ�\n");
                return;
            }
        }
    }
}

// JNI ����
extern "C" JNIEXPORT void JNICALL
Java_com_uniaball_project1_1android_GameActivity_startGame(
    JNIEnv* env,
    jobject /* this */) {
    // �ض������
    static AndroidStream androidStream;
    cout.rdbuf(&androidStream);

    // ������Ϸ�߳�
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
    // �����κεȴ�������߳�
    input_cv.notify_all();
}