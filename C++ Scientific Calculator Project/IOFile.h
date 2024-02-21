#pragma once
#include "Calcul.h"
#include "Input.h"
#include <string>
#include <iostream>
#include <fstream>


class Expression {
public:
	double result;
	string input;

	Expression();
	Expression(int res, string in);
	friend ofstream& operator<<(ofstream& write, Expression& e);
};


class InputFile : public Input {
private:
	char* input;
	double result=0.0;
	char fileOperation = '0';
	double numberFile;
public:
	InputFile();

	~InputFile();

	InputFile (const InputFile& f);

	InputFile& operator=(InputFile& f);

	void setResult(double result);

	void setnumberFile(double no);

	void setfileOperation(char op);

	char getfileOperation();

	double getResult();

	char* getUserInput() override;

	void setUserInput(char* input) override;

	void sortation();

	friend  ifstream& operator>> (ifstream& file, InputFile& f);

	void afisare();

    friend ofstream& operator<< (ofstream& write, InputFile& f);
};

class BinaryInterface {
	virtual void WriteRead() = 0;
	virtual double GetResult() = 0;
	virtual void setResult(double rez) = 0;
};

class BinaryWrite: public BinaryInterface{
private:
	double result;
	
public:
	void WriteRead() override;
	double GetResult() override;
	void setResult(double rez) override;

};

class BinaryRead :public BinaryInterface {
private :
	double result;

public:
	void WriteRead() override;
	double GetResult() override;
	void setResult(double rez) override;
	void deleteBinary();
	
};





