#pragma once
#include<fstream>

using namespace std;

const char logfile[] = "Logika_Svetofora.txt";

class Automat
{
public:

	void Power_On();       //Включить светофор
	void Power_Off();      //Выключить сфетофор
	void Night_time();     //Проверка на время суток (ночью работает мигающий желтый)
	void Blink_mode();     //Режим мигания

	void Green_timer();    //Таймер работы зеленого света
	void Blink_timer();    //Таймер мигания светофора
	void Red_timer();      //Таймер работы красного света

	bool broken;      //Аварийное состояние

	Automat();
	~Automat();

private:

	bool power;      
	bool brokenGreen;
	bool brokenYellow;
	bool brokenRed;

	bool nightTime;   //Ночное время
	

	ofstream log;
	int s;            //Состояние перед циклом

	void A(int);               //Функция управляющей логики

	//Сигналы на входе
	bool x1();              //Питание есть
//	bool x2();              //Включить
//	bool x3();              //Выключить
	bool x4();              //Режим мигания
	bool x5();              //Перегорел красный
	bool x6();              //Перегорел желтый
	bool x7();              //Перегорел зеленый
	bool x8();              //Аварийное состояние

	//Выходные состояния
	void v1();              //Аварийное состояние
	void v2();              //Запуск таймера зеленого света
	void v3();              //Запуск таймера мигания
	void v4();              //Запуск таймера красного света
	void v5();              //Включить зелёный
	void v6();              //Включить зелёный мигающий
	void v7();              //Включить жёлтый
	void v8();              //Включить красный
	void v9();              //Включить красный и жёлтый
	void v10();             //Включить жёлтый мигающий
	void v11();             //Погасить все огни

	//Методы лога
	void log_begin(int, int);              //Запись начала работы
	void log_end(int);                     //Запись конца работы
	void log_input(int, const char*, bool);      //Запись входных сигналов
	void log_output(int, const char*);           //Запись выходных параметров
	void log_error(int);                   //Запись ошибки
	void log_move(int, int);               //Запись перехода состояния
};