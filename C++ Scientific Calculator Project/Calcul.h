#pragma once
#include "Input.h"
#include <iostream>
#include <string>
#include <cstring>
class Calcul {
private:
	char* input;
	double rezultat;
	char fileOperation='0';
	double numberFile=0;
public:
	Calcul();

	Calcul(const char* input);

	~Calcul();

	Calcul(const Calcul& c);

	Calcul& operator=(Calcul& c);

	void InputPrelucrat();

	double getnumberFile();

    char* getInput();

	char getfileOperation();

	void setInput(char* input);

	double FileResult(double number);

	double getRezultat();

	static int Prioritate(char charCurent);

	void evaluareInput();

	double operator+(float number);

	double operator*(float number);

	double operator-(float number);

	double operator/(float number);

	double operator^ (float number);

	double radical(float number);

};