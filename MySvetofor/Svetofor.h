#pragma once
#include<fstream>

using namespace std;

const char logfile[] = "Logika_Svetofora.txt";

class Automat
{
public:

	void Power_On();       //�������� ��������
	void Power_Off();      //��������� ��������
	void Night_time();     //�������� �� ����� ����� (����� �������� �������� ������)
	void Blink_mode();     //����� �������

	void Green_timer();    //������ ������ �������� �����
	void Blink_timer();    //������ ������� ���������
	void Red_timer();      //������ ������ �������� �����

	bool broken;      //��������� ���������

	Automat();
	~Automat();

private:

	bool power;      
	bool brokenGreen;
	bool brokenYellow;
	bool brokenRed;

	bool nightTime;   //������ �����
	

	ofstream log;
	int s;            //��������� ����� ������

	void A(int);               //������� ����������� ������

	//������� �� �����
	bool x1();              //������� ����
//	bool x2();              //��������
//	bool x3();              //���������
	bool x4();              //����� �������
	bool x5();              //��������� �������
	bool x6();              //��������� ������
	bool x7();              //��������� �������
	bool x8();              //��������� ���������

	//�������� ���������
	void v1();              //��������� ���������
	void v2();              //������ ������� �������� �����
	void v3();              //������ ������� �������
	void v4();              //������ ������� �������� �����
	void v5();              //�������� ������
	void v6();              //�������� ������ ��������
	void v7();              //�������� �����
	void v8();              //�������� �������
	void v9();              //�������� ������� � �����
	void v10();             //�������� ����� ��������
	void v11();             //�������� ��� ����

	//������ ����
	void log_begin(int, int);              //������ ������ ������
	void log_end(int);                     //������ ����� ������
	void log_input(int, const char*, bool);      //������ ������� ��������
	void log_output(int, const char*);           //������ �������� ����������
	void log_error(int);                   //������ ������
	void log_move(int, int);               //������ �������� ���������
};