#include<fstream>
#include<Windows.h>
#include"Svetofor.h"

//Описание логики работы светофора записывается в Logika_Svetofora.txt

Automat::Automat()
{
     power = true;              //Наличие питания
	 brokenGreen = false;       //Перегорел зеленый
	 brokenYellow = false;      //Перегорел желтый
	 brokenRed = false;         //Перегорел красный
	 nightTime = false;         //Ночное время
	 broken = false;
	 
	 s = 0;

	 log.open(logfile);
}

Automat::~Automat()
{
	log.close();
}

//ОПИСАНИЕ КОНТРОЛИРУЮЩЕЙ ЛОГИКИ

void Automat::Power_On()
{
	A(1);
	//Sleep(40000);              //Таймер работы зелёного
}

void Automat::Power_Off()
{
	A(2);                      //Выключить светофор
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
	//Sleep(4000);              //Таймер работы зелёного мигающего
}

void Automat::Blink_timer()
{
	A(5);
	//Sleep(4000);              //Таймер работы жёлтого
}

void Automat::Red_timer()
{
	A(6);
	//Sleep(30000);              //Таймер работы красного
}

//ОПИСАНИЕ УПРАВЛЯЮЩЕЙ ЛОГИКИ

void Automat::A(int e)            
{
	int a = s;                  //переменная для switch

	log_begin(s, e);

	switch (s)
	{
	case 0:                     //Включение светофора, Зеленый
		if (x1() == false)                                                     { v11();  s = 0; }
		else if (e == 1)                                                       { s = 1; }
		else if (e == 3 && x4())                                               { s = 6; }
		if (x5() || x7())                                                      { s = 6; }
		else if (e == 2 || x6())                                               { v11();  s = 0; }
		break;

	case 1:                     //Зеленый мигающий
		if (e == 4)                                { s = 2; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 2:                     //Желтый
		if (e == 5)                                { s = 3; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 3:                     //Красный
		if (e == 5)                                { s = 4; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 4:                     //Красный и желтый
		if (e == 6)                                { s = 5; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 5:                     //Зеленый
		if (e == 5)                                { s = 1; }
		if (e == 2 || x6())                        { v1(), s = 0; }
		if (e == 3)                                { s = 6; }
		if (x5() || x7())                          { v10(), s = 6; }
		break;

	case 6:                     //Авария
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

//ВХОДНЫЕ ПАРАМЕТРЫ

bool Automat::x1()
{
	log_input(1, "Наличие питания", power);
	return power;
}

bool Automat::x4()
{
	log_input(4, "Режим мигания", nightTime);
	return nightTime;
}

bool Automat::x5()
{
	log_input(5, "Перегорел красный", brokenRed);
	return brokenRed;
}

bool Automat::x6()
{
	log_input(6, "Перегорел жёлтый", brokenYellow);
	return brokenYellow;
}

bool Automat::x7()
{
	log_input(7, "Перегорел зелёный", brokenGreen);
	return brokenGreen;
}

bool Automat::x8()
{
	log_input(8, "Аварийное состояние", broken);
	return broken;
}

//ВЫХОДНЫЕ СОСТОЯНИЯ

void Automat::v1()
{
	log_output(1, "Аварийное состояние");
	broken = true;
}

void Automat::v2()
{
	log_output(2, "Установить таймер зелёного света");
}

void Automat::v3()
{
	log_output(3, "Установить таймер мигания");
}

void Automat::v4()
{
	log_output(4, "Установить таймер красного света");
}

void Automat::v5()
{
	log_output(5, "Включить зеленый");
}

void Automat::v6()
{
	log_output(6, "Включить зеленый мигающий");
}

void Automat::v7()
{
	log_output(7, "Включить жёлтый");
}

void Automat::v8()
{
	log_output(8, "Включить красный");
}

void Automat::v9()
{
	log_output(9, "Включить красный и жёлтый");
}

void Automat::v10()
{
	log_output(10, "Включить жёлтый мигающий");
	broken = true;
}

void Automat::v11()
{
	log_output(11, "Погасить все огни");
	broken = true;
}

//МЕТОДЫ ЛОГА

void Automat::log_begin(int state, int event)
{
	log << "{ Светофор начал свою работу в состоянии " << state << " с событием е" << event << endl;
}

void Automat::log_end(int state)
{
	log << "Светофор закончил свою работу в состоянии " << state << " }" << endl;
}

void Automat::log_error(int state)
{
	log << "Аварийное состояние " << state << endl;
}

void Automat::log_move(int from, int to)
{
	log << "Светофор перешел из состояния " << from << " в состояние " << to << endl;
}
void Automat::log_input(int state, const char* comm, bool result)
{
	const char* res;
	res = result ? "ДА" : "НЕТ";

	log << "    Входное условие ";
	log << "x" << state << ": " << comm << "? - " << res << endl;
}

void Automat::log_output(int state, const char* comm)
{
	log << "    Выходное состояние v" << state << ": " << comm << endl;
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