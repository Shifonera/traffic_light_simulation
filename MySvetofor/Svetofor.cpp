#include<fstream>
#include<Windows.h>
#include"Svetofor.h"

//�������� ������ ������ ��������� ������������ � Logika_Svetofora.txt

Automat::Automat()
{
     power = true;              //������� �������
	 brokenGreen = false;       //��������� �������
	 brokenYellow = false;      //��������� ������
	 brokenRed = false;         //��������� �������
	 nightTime = false;         //������ �����
	 broken = false;
	 
	 s = 0;

	 log.open(logfile);
}

Automat::~Automat()
{
	log.close();
}

//�������� �������������� ������

void Automat::Power_On()
{
	A(1);
	//Sleep(40000);              //������ ������ �������
}

void Automat::Power_Off()
{
	A(2);                      //��������� ��������
}

void Automat::Night_time()
{
	if (nightTime)
	{
		A(3);
	}
}

void Automat::Blink_mode()
{
	if (brokenGreen || brokenRed)
	{
		A(3);
	}
}

void Automat::Green_timer()
{
	A(4);
	//Sleep(4000);              //������ ������ ������� ���������
}

void Automat::Blink_timer()
{
	A(5);
	//Sleep(4000);              //������ ������ ������
}

void Automat::Red_timer()
{
	A(6);
	//Sleep(30000);              //������ ������ ��������
}

//�������� ����������� ������

void Automat::A(int e)            
{
	int a = s;                  //���������� ��� switch

	log_begin(s, e);

	switch (s)
	{
	case 0:                     //��������� ���������, �������
		if (x1() == false)                                                     { v11();  s = 0; }
		else if (e == 1)                                                       { s = 1; }
		else if (e == 3 && x4())                                               { s = 6; }
		if (x5() || x7())                                                      { s = 6; }
		else if (e == 2 || x6())                                               { v11();  s = 0; }
		break;

	case 1:                     //������� ��������
		if (e == 4)                                { s = 2; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 2:                     //������
		if (e == 5)                                { s = 3; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 3:                     //�������
		if (e == 5)                                { s = 4; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 4:                     //������� � ������
		if (e == 6)                                { s = 5; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 5:                     //�������
		if (e == 5)                                { s = 1; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 6:                     //������
		if (e == 2 || x6())                        { v1(), s = 0; }
		break;

	default:
		log_error(s);
	}

	if (s != a)
	{
		log_move(a, s);

		switch (s)
		{
		case 0:
			{v11(); }
			break;

		case 1:    
			{v2(); v5(); }
			break;

		case 2:                   
			{v3(); v6(); }
			break;

		case 3:                   
			{v3(); v7(); }
			break;

		case 4:                    
			{v4(); v8(); }
			break;

		case 5:                    
			{v3(); v9(); }
			break;
		case 6:                    
			{v10(); }
			break;

		default:
			log_error(s);
		}
	}

	log_end(s);

}

//������� ���������

bool Automat::x1()
{
	log_input(1, "������� �������", power);
	return power;
}

bool Automat::x4()
{
	log_input(4, "����� �������", nightTime);
	return nightTime;
}

bool Automat::x5()
{
	log_input(5, "��������� �������", brokenRed);
	return brokenRed;
}

bool Automat::x6()
{
	log_input(6, "��������� �����", brokenYellow);
	return brokenYellow;
}

bool Automat::x7()
{
	log_input(7, "��������� ������", brokenGreen);
	return brokenGreen;
}

bool Automat::x8()
{
	log_input(8, "��������� ���������", broken);
	return broken;
}

//�������� ���������

void Automat::v1()
{
	log_output(1, "��������� ���������");
	broken = true;
}

void Automat::v2()
{
	log_output(2, "���������� ������ ������� �����");
}

void Automat::v3()
{
	log_output(3, "���������� ������ �������");
}

void Automat::v4()
{
	log_output(4, "���������� ������ �������� �����");
}

void Automat::v5()
{
	log_output(5, "�������� �������");
}

void Automat::v6()
{
	log_output(6, "�������� ������� ��������");
}

void Automat::v7()
{
	log_output(7, "�������� �����");
}

void Automat::v8()
{
	log_output(8, "�������� �������");
}

void Automat::v9()
{
	log_output(9, "�������� ������� � �����");
}

void Automat::v10()
{
	log_output(10, "�������� ����� ��������");
	broken = true;
}

void Automat::v11()
{
	log_output(11, "�������� ��� ����");
	broken = true;
}

//������ ����

void Automat::log_begin(int state, int event)
{
	log << "{ �������� ����� ���� ������ � ��������� " << state << " � �������� �" << event << endl;
}

void Automat::log_end(int state)
{
	log << "�������� �������� ���� ������ � ��������� " << state << " }" << endl;
}

void Automat::log_error(int state)
{
	log << "��������� ��������� " << state << endl;
}

void Automat::log_move(int from, int to)
{
	log << "�������� ������� �� ��������� " << from << " � ��������� " << to << endl;
}
void Automat::log_input(int state, const char* comm, bool result)
{
	const char* res;
	res = result ? "��" : "���";

	log << "    ������� ������� ";
	log << "x" << state << ": " << comm << "? - " << res << endl;
}

void Automat::log_output(int state, const char* comm)
{
	log << "    �������� ��������� v" << state << ": " << comm << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");

	Automat Svetofor;


		Svetofor.Power_On();

		if (Svetofor.broken == false)
	{
		Svetofor.Blink_mode();
		Svetofor.Night_time();
		Svetofor.Green_timer();
		Svetofor.Blink_timer();
		Svetofor.Blink_timer();
		Svetofor.Red_timer();
    }
	return 0;
}