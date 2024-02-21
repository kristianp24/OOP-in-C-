#pragma once
#include <iostream>
#include "Input.h"
#include "Calcul.h"
#include "IOFile.h"
using namespace std;

class UserInterface {
private:
	
	char choice;
	int menu = 1;
	char* inputFaraSpatii;
	char* inputCuSpatii;
	Input i;
	Calcul c;
	InputFile i2;
	BinaryWrite* br;
	BinaryRead* b;
	string input;
	static string name;
	static int nrUsed;
public:
	UserInterface();

	UserInterface(int choice);

	UserInterface(const UserInterface& u);

	~UserInterface();

	UserInterface& operator=(UserInterface& u);

	void ReadFromBinary();

	void setChoice(int i);

    string getInput();

	void setInput(string input);

	static string getName();

	static void setName(string _name);
	
	static int getnrUsed();

	static void setnrUsed(int _nrUsed);

	char getChoice();

	void PreluareInput();

	void StergereSpatiiInput(char* inputCuSpatii);

	void Menu();

	void Exit();
    
	bool operator! ();

};


