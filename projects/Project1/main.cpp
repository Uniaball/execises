#include <iostream>
#include <string>
#include <random>
#include <windows.h>

using namespace std;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 2);

int main()
{
    //ȫ�ֱ�����ʼ����
    //bool Game = 0;
    bool LeftHandWin = 0;
    bool RightHandWin = 0;
    bool LeftHandWin2 = 0;
    bool RightHandWin2 = 0;
    //��Ϸ��ʼ

    string GameStart;
    cout << "����start��ʼ��Ϸ" << endl;
    cin >> GameStart;

    if (GameStart != "start") {
        cout << "δ������ȷ�ַ������̽���" << endl;
        return 1;
    }
    else if (GameStart == "start") {
        cout << "��Ϸ��ʼ" << endl;
    }
    //��ʼ��������
    //for (;;) {  //��Ϸ��ѭ��

        short LeftNum = 1, RightNum = 1;
        cout << "������������֣������ִ�ʱ����1" << endl;
        cout << "��" << LeftNum << " �ң�" << RightNum << endl;

        short LeftNum2 = 1, RightNum2 = 1;
        cout << "������Ķ��֣�����ai����������" << endl;
        cout << "��" << LeftNum2 << " �ң�" << RightNum2 << endl;

        //ѡ���Լ�������
        for (;;) {

            cout << "ѡ�����һֻ�֣�����L��R��" << endl;
            bool ChooseLeftHand = 0, ChooseRightHand = 0;
            char Choice;
            cin >> Choice;
            switch (Choice) {
            case 'L': {
                if (LeftHandWin != 1) {  // ������ֻ����Ƿ��ʤ���������ֵ
                    ChooseLeftHand = 1;
                    cout << "��ѡ�������֣�" << LeftNum << ")" << endl;
                }
                else {
                    cout << "��ֻ���Ѿ�Ӯ���󣬰���ѡ������" << endl;
                    ChooseRightHand = 1;
                    Sleep(500);
                    cout << "��ѡ�������֣�" << RightNum << "��" << endl;
                }
                break;
            }
            case 'R': {
                if (RightHandWin != 1) {  // ������ֻ����Ƿ��ʤ���������ֵ
                    ChooseRightHand = 1;
                    cout << "��ѡ�������֣�" << RightNum << "��" << endl;
                }
                else {
                    cout << "��ֻ���Ѿ�Ӯ���󣬰���ѡ������" << endl;
                    ChooseLeftHand = 1;
                    Sleep(500);
                    cout << "��ѡ�������֣�" << LeftNum << "��" << endl;
                }
                break;
            }
            default: {
                cout << "δ������ȷ�ַ������̽���" << endl;
                return 1;
            }
            }
            //��ai��ֻ��
            char ChooseHand;
            cout << "��Ҫ��ai����ֻ�֣�����L��R��";
            cin >> ChooseHand;
            switch (ChooseHand) {
            case 'L': {
                if (LeftHandWin2 != 1) {  // ���������AI�����Ƿ��ʤ
                    if (ChooseLeftHand == 1) {
                        cout << "��ѡ����ai�����֣�" << LeftNum2 << ")" << endl;
                        LeftNum += LeftNum2;
                        if (LeftNum > 10) {
                            LeftNum -= 10;
                        }
                        cout << "������ϣ���ʱ��������ǣ�" << LeftNum << endl;
                    }
                    else if (ChooseRightHand == 1) {
                        cout << "��ѡ����ai�����֣�" << LeftNum2 << ")" << endl;
                        RightNum += LeftNum2;
                        if (RightNum > 10) {
                            RightNum -= 10;
                        }
                        cout << "������ϣ���ʱ��������ǣ�" << RightNum << endl;
                    }
                }
                else {
                    cout << "AI�������Ѿ���ʤ������ѡ��" << endl;
                }
                break;
            }

            case 'R': {
                if (RightHandWin2 != 1) {  // ���������AI�����Ƿ��ʤ
                    if (ChooseLeftHand == 1) {
                        cout << "��ѡ����ai�����֣�" << RightNum2 << ")" << endl;
                        LeftNum += RightNum2;
                        if (LeftNum > 10) {
                            LeftNum -= 10;
                        }
                        cout << "������ϣ���ʱ��������ǣ�" << LeftNum << endl;
                    }
                    else if (ChooseRightHand == 1) {
                        cout << "��ѡ����ai�����֣�" << RightNum2 << ")" << endl;
                        RightNum += RightNum2;
                        if (RightNum > 10) {
                            RightNum -= 10;
                        }
                        cout << "������ϣ���ʱ��������ǣ�" << RightNum << endl;
                    }
                }
                else {
                    cout << "AI�������Ѿ���ʤ������ѡ��" << endl;
                }
                break;
            }

            default: {
                cout << "δ������ȷ�ַ������̽���" << endl;
                return 1;
            }
            }

            //��ʾ������
            cout << "�������������" << endl;
            cout << "��" << LeftNum << " �ң�" << RightNum << endl;

            cout << "����ai��������" << endl;
            cout << "��" << LeftNum2 << " �ң�" << RightNum2 << endl;

            ///////////////////////////////////////////////////////////////////////////////////////ai�غ�
            short RandomSelfHandChoice = dist(gen);
            short RandomHandChoice = dist(gen);
            cout << "ai�غ�" << endl;
            Sleep(2000);

            // �ع�AI�غ��߼�
            bool aiActionTaken = false;

            // AIѡ���Լ�����
            if (RandomSelfHandChoice == 1 && LeftHandWin2 != 1) {
                cout << "aiʹ�������֣�" << LeftNum2 << "��" << endl;
                Sleep(2000);

                // AIѡ����ҵ���
                if (RandomHandChoice == 1 && LeftHandWin != 1) {
                    cout << "aiѡ����������֣�" << LeftNum << "��" << endl;
                    LeftNum2 += LeftNum;
                    if (LeftNum2 > 10) {
                        LeftNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai��ʱ���ֵ�����" << LeftNum2 << endl;
                    aiActionTaken = true;
                }
                else if (RightHandWin != 1) {
                    cout << "aiѡ����������֣�" << RightNum << "��" << endl;
                    LeftNum2 += RightNum;
                    if (LeftNum2 > 10) {
                        LeftNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai��ʱ���ֵ�����" << LeftNum2 << endl;
                    aiActionTaken = true;
                }
            }
            else if (RandomSelfHandChoice == 2 && RightHandWin2 != 1) {
                cout << "aiʹ�������֣�" << RightNum2 << "��" << endl;
                Sleep(2000);

                // AIѡ����ҵ���
                if (RandomHandChoice == 1 && LeftHandWin != 1) {
                    cout << "aiѡ����������֣�" << LeftNum << "��" << endl;
                    RightNum2 += LeftNum;
                    if (RightNum2 > 10) {
                        RightNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai��ʱ���ֵ�����" << RightNum2 << endl;
                    aiActionTaken = true;
                }
                else if (RightHandWin != 1) {
                    cout << "aiѡ����������֣�" << RightNum << "��" << endl;
                    RightNum2 += RightNum;
                    if (RightNum2 > 10) {
                        RightNum2 -= 10;
                    }
                    Sleep(2000);
                    cout << "ai��ʱ���ֵ�����" << RightNum2 << endl;
                    aiActionTaken = true;
                }
            }

            // ���AIû��ִ�ж�������Ϊѡ����ֲ����ã���������һֻ��
            if (!aiActionTaken) {
                if (RandomSelfHandChoice == 1 && RightHandWin2 != 1) {
                    cout << "ai���������֣�" << RightNum2 << "��" << endl;
                    Sleep(2000);

                    if (RandomHandChoice == 1 && LeftHandWin != 1) {
                        cout << "aiѡ����������֣�" << LeftNum << "��" << endl;
                        RightNum2 += LeftNum;
                        if (RightNum2 > 10) {
                            RightNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai��ʱ���ֵ�����" << RightNum2 << endl;
                    }
                    else if (RightHandWin != 1) {
                        cout << "aiѡ����������֣�" << RightNum << "��" << endl;
                        RightNum2 += RightNum;
                        if (RightNum2 > 10) {
                            RightNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai��ʱ���ֵ�����" << RightNum2 << endl;
                    }
                }
                else if (RandomSelfHandChoice == 2 && LeftHandWin2 != 1) {
                    cout << "ai���������֣�" << LeftNum2 << "��" << endl;
                    Sleep(2000);

                    if (RandomHandChoice == 1 && LeftHandWin != 1) {
                        cout << "aiѡ����������֣�" << LeftNum << "��" << endl;
                        LeftNum2 += LeftNum;
                        if (LeftNum2 > 10) {
                            LeftNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai��ʱ���ֵ�����" << LeftNum2 << endl;
                    }
                    else if (RightHandWin != 1) {
                        cout << "aiѡ����������֣�" << RightNum << "��" << endl;
                        LeftNum2 += RightNum;
                        if (LeftNum2 > 10) {
                            LeftNum2 -= 10;
                        }
                        Sleep(2000);
                        cout << "ai��ʱ���ֵ�����" << LeftNum2 << endl;
                    }
                }
            }

            // ���AI��Ȼû��ִ�ж�����˵������ѡ�񶼲�����
            if (!aiActionTaken) {
                cout << "ai�޷��ж��������غ�" << endl;
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////��ʾ������
            cout << "�������������" << endl;
            cout << "��" << LeftNum << " �ң�" << RightNum << endl;

            cout << "����ai��������" << endl;
            cout << "��" << LeftNum2 << " �ң�" << RightNum2 << endl;

            //��ʤ����������
            if (LeftNum == 10 && !LeftHandWin) {
                LeftHandWin = 1;
                cout << "��������ѻ�ʤ����������" << endl;
                if (RightHandWin == 1) {
                    cout << "���ѻ�ʤ�����̽��Դ���0�˳�" << endl;
                    return 0;
                }
            }

            if (RightNum == 10 && !RightHandWin) {
                RightHandWin = 1;
                cout << "��������ѻ�ʤ����������" << endl;
                if (LeftHandWin == 1) {
                    cout << "���ѻ�ʤ�����̽��Դ���0�˳�" << endl;
                    return 0;
                }
            }

            if (LeftNum2 == 10 && !LeftHandWin2) {
                LeftHandWin2 = 1;
                cout << "ai�������ѻ�ʤ����������" << endl;
                if (RightHandWin2 == 1) {
                    cout << "�����ˣ����̽��Դ���2�˳�" << endl;
                    return 2;
                }
            }

            if (RightNum2 == 10 && !RightHandWin2) {
                RightHandWin2 = 1;
                cout << "ai�������ѻ�ʤ����������" << endl;
                if (LeftHandWin2 == 1) {
                    cout << "�����ˣ����̽��Դ���2�˳�" << endl;
                    return 2;
                }
            }

        }

        //Game = 1;
    //}//����Χfor������

    system("pause");
    return 0;
}