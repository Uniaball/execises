#include <iostream>
#include <Windows.h>
#include <random>
#include <conio.h>
#include "main.h"

using namespace std;
random_device rd;                                    //������õ���
mt19937 gen(rd());
uniform_int_distribution<int> dist(1, 3);


int main() {
	//��ʼ��Ϸ��⣨�˻����ԣ�
	string StartGame;
	cout << "����start��ʼ��Ϸ" << endl;
	cin >> StartGame;
	if (StartGame == "start") {
		cout << "������ȷ�ַ�����Ϸ��ʼ" << endl;
		Sleep(2000);
		system("cls");  

		GameSum();  //�ϻ���������

		Sleep(3000);
		system("cls");

		Start();  //ѡ��������
	}
	else {
		cout << "δ������ȷ�ַ������̽��Դ���1�˳�" << endl;
		return 1;
	}

	system("pause");
	return 0;
}






void GameSum() { //�ϻ�����
	cout << "����Ϸ����һ��ʯͷ��������,ͬʱ�������ҵĺ���ˮƽ" << endl;
	cout << "��Ķ�����Ȼ���Ǹ�����ai��" << endl;
}


short Start() {
	char s, j, b;
	cout << "��Ҫ��ʲô��ʯͷ����S������������J����������B������" << endl;                               //bzlͬ��������̺���
	switch (_getche()) {
	case 's': {
		cout << "\n";
		cout << "��ѡ����ʯͷ" << endl;
		cout << "�ȴ�aiѡ��" << endl;
		s = 's';
		j = 'N';
		b = 'N';
		Keyboard(s, j, b);  ///
		break;
	}
	case 'j': {
		cout << "\n";
		cout << "��ѡ���˼���" << endl;
		cout << "�ȴ�aiѡ��" << endl;
		s = 'N';
		j = 'j';
		b = 'N';
		Keyboard(s, j, b);  ///
		break;
	}
	case 'b': {
		cout << "\n";
		cout << "��ѡ���˲�" << endl;
		cout << "�ȴ�aiѡ��" << endl;
		s = 'N';
		j = 'N';
		b = 'b';
		Keyboard(s, j, b);  ///
		break;
	}
	default: {
		cout << "\n";
		cout << "��ţħ�İ�ɶ��" << endl;
		cout << "�������" << endl;
		return 1;
	}
	}
	
	//system("pause");
}


short Keyboard(char s, char j, char b) {    
	short AiRandomChoose = dist(gen);                      //�������Ӧ����ai�غϼ���Ϸʤ��
	if (s == 's') {   //���ѡ��ʯͷ
		switch (AiRandomChoose) {
		case 1: {          //ʯͷ
			Sleep(2000);
			cout << "aiѡ����ʯͷ" << endl;
			Sleep(500);
			cout << "����ƽ��" << endl;
			Sleep(500);
			cout << "������ѡ��" << endl;
			Start();       //����ִ��start����
			break;
		}
		case 2: {         //����
			Sleep(2000);
			cout << "aiѡ���˼���" << endl;
			Sleep(500);
			cout << "��Ӯ��" << endl;
			Sleep(500);
			cout << "����Ϸ���Դ���0�˳���" << endl;
			return 0;
			break;
		}
		case 3: {         //��
			Sleep(2000);
			cout << "aiѡ���˲�" << endl;
			Sleep(500);
			cout << "������" << endl;
			Sleep(500);
			cout << "��Ϸ���Դ���2�˳�" << endl;
			return 2;
			break;
		}
		}
	}
	else if (j == 'j') {        //���ѡ�����
		switch (AiRandomChoose) {
		case 1: {          //ʯͷ
			Sleep(2000);
			cout << "aiѡ����ʯͷ" << endl;
			Sleep(500);
			cout << "������" << endl;
			Sleep(500);
			cout << "��Ϸ���Դ���2�˳�" << endl;
			return 2;   
			break;
		}
		case 2: {         //����
			Sleep(2000);
			cout << "aiѡ���˼���" << endl;
			Sleep(500);
			cout << "����ƽ��" << endl;
			Sleep(500);
			cout << "������ѡ��" << endl;
			Start();          //����ִ��start����
			break;
		}
		case 3: {         //��
			Sleep(2000);
			cout << "aiѡ���˲�" << endl;
			Sleep(500);
			cout << "��Ӯ��" << endl;
			Sleep(500);
			cout << "��Ϸ���Դ���0�˳�" << endl;
			return 0;
			break;
		}
		}
	}
	else if (b == 'b') {        //���ѡ��
		switch (AiRandomChoose) {
		case 1: {          //ʯͷ
			Sleep(2000);
			cout << "aiѡ����ʯͷ" << endl;
			Sleep(500);
			cout << "��Ӯ��" << endl;
			Sleep(500);
			cout << "��Ϸ���Դ���0�˳�" << endl;
			return 0;
			break;
		}
		case 2: {         //����
			Sleep(2000);
			cout << "aiѡ���˼���" << endl;
			Sleep(500);
			cout << "������" << endl;
			Sleep(500);
			cout << "��Ϸ���Դ���2�˳�" << endl;
			return 2;
			break;
		}
		case 3: {         //��
			Sleep(2000);
			cout << "aiѡ���˲�" << endl;
			Sleep(500);
			cout << "����ƽ��" << endl;
			Sleep(500);
			cout << "������ѡ��" << endl;
			Start();          //����ִ��start����
			break;
		}
		}
	}
	//system("pause");
}