#pragma once
#include "UserInterface.h"
#include<string.h>
#include<string>
#include <iostream>
#include <fstream>
using namespace std;

int UserInterface::nrUsed = 0;

string UserInterface::name = "The Calculator";

UserInterface::UserInterface():menu(1)
{
	choice = 0;
	inputFaraSpatii = nullptr;
}

UserInterface::UserInterface(int choice):UserInterface()
{
	this->choice = choice;
}

UserInterface::UserInterface(const UserInterface& u):menu(u.menu)
{
	if (u.inputFaraSpatii != nullptr) {
		this->inputFaraSpatii = new char[strlen(u.inputFaraSpatii) + 1];
		strcpy_s(this->inputFaraSpatii,strlen (u.inputFaraSpatii) + 1, u.inputFaraSpatii);
	}
}

UserInterface::~UserInterface() {
	if (this->inputFaraSpatii != nullptr) {
		delete[] this->inputFaraSpatii;
		this->inputFaraSpatii = nullptr;
	}
}

UserInterface& UserInterface::operator=(UserInterface& u) {
	if (this != &u) {
		if (this->inputFaraSpatii != nullptr) {
			delete[] this->inputFaraSpatii;
			this->inputFaraSpatii = nullptr;
		}
		if (u.inputFaraSpatii != nullptr) {
			this->inputFaraSpatii = new char[strlen(u.inputFaraSpatii) + 1];
			strcpy_s(this->inputFaraSpatii, strlen(u.inputFaraSpatii) + 1, u.inputFaraSpatii);
		}
	}
	return *this;
}


string UserInterface::getInput() {
	return this->input;
}

void UserInterface::setInput(string input) {
	this->input = input;
}

void UserInterface::setnrUsed(int _nrUsed) {
	nrUsed += _nrUsed;
}

int UserInterface::getnrUsed() {
	return nrUsed;
}

string UserInterface::getName() {
	return name;
}

void UserInterface::setName(string _name) {
	name = _name;
}

void UserInterface:: setChoice(int i) {
	choice = i;
}

char UserInterface:: getChoice() {
	return choice;
}

void UserInterface::StergereSpatiiInput(char* inputCuSpatii) {
	int j = -1,k=0;
	if (this->inputFaraSpatii != nullptr) {
		delete[] this->inputFaraSpatii;
		this->inputFaraSpatii = nullptr;
	}

	for (int i = 0; i < strlen(inputCuSpatii) + 1; i++) {
		if (inputCuSpatii[i] != ' ') {
			k++;
		}
	}

    	this->inputFaraSpatii = new char[k];
		for (int i = 0; i < strlen(inputCuSpatii) + 1; i++) {
			if (inputCuSpatii[i] != ' ') {
                this->inputFaraSpatii[++j] = inputCuSpatii[i];
			}
		}
		
}

void UserInterface:: PreluareInput() {

	if (choice == '1') {
    cout << "Enter input: " << endl;
	cin >> ws;
	getline(cin,input);
	 const char*  input2 = input.c_str();
      char* input3 = _strdup(input2);
      StergereSpatiiInput(input3);
	}
	
	if (choice == '2') {
		this->inputCuSpatii = new char[strlen(i2.getUserInput()) + 1];
		strcpy_s(this->inputCuSpatii, strlen(i2.getUserInput()) + 1, i2.getUserInput());
		StergereSpatiiInput(this->inputCuSpatii);
	}
 
	int a;
  i.setUserInput(this->inputFaraSpatii);
	if (i.VerificareInputLitere() == true || i.VerificareInputSimbole() == true||i.VerificareParanteze()==true ||i.VerificareOperatori()==true
		||i.VerificareOrdineParanteze()==true||i.VerificareOperatori2()==true||i.VerificareVirgula()==true)
	{
		cout << "Invalid Input." << endl;
	}
	else {
		c.setInput(this->inputFaraSpatii);
		c.InputPrelucrat();
		c.evaluareInput();
		ReadFromBinary();
		cout << "Press 3 if you want to save the latest result for latest calculation,0 if you do not want:";
		cin >> a;
		if (a == 3) {
			br = new BinaryWrite();
			br->setResult(c.getRezultat());
			br->WriteRead();
			delete br;
			cout << "Saved to Results.bin." << endl;
        }
		cout << "Press 1 if you want to save the calculations into a text file,any number if you do not want:";
		cin >> a;
		if (a == 1) {
			i2.setUserInput(this->inputFaraSpatii);
			i2.setResult(c.getRezultat());
			ofstream write("Saved_Calculations.txt", std::ios::out | std::ios::app);
			i2.setfileOperation(c.getfileOperation());
			i2.setResult(c.getRezultat());
			i2.setnumberFile(c.getnumberFile());
			operator<<(write, i2);
			write.close();
			cout << endl;
			i2.sortation();
			cout << "Calculations saved and sorted in file Calculations.txt." << endl;
		}

		nrUsed++;
	}
	
}

void UserInterface::ReadFromBinary() {
	int j=0;
	
	ifstream i("Results.bin", ios::binary);
	if (i.is_open()) {
		char aux;
		if (i.read(&aux, 1)) {
			cout << "Press 1 if you want to use the saved result,any number if you do not want:";
			cin >> j;
		}
	}
	if (j == 1) {
		int a = 0;
		b = new BinaryRead();
		b->WriteRead();
		b->setResult(c.FileResult(b->GetResult()));

		cout << "Your new result is:" << b->GetResult() << endl;
	
		b->deleteBinary();
		nrUsed++;
	}
	i.close();
}

void UserInterface:: Menu() {
	cout << "Welcome to " << name << endl;
	while (menu == 1) {
		cout << endl;
		cout << "1-To include an input." << endl << "2-To take an input from a file." << endl;
		cout << "0-To exit from the calculator." << endl;
		cout << "Your choice:";
		cin >> choice;
		if (choice != '1' && choice != '0' && choice != '2' && choice != '3') {
			cout << endl;
			cout << "Please enter 1 or 0."<<endl;
			continue;
		}
		int a;
		switch (choice) {
		case '0':
			Exit();
			menu = 0;
			break;
		case '1':
			PreluareInput();
			break;
		case '2':
			//citire din file
			
		{ifstream in("Input.txt");
		operator>>(in, i2);
		in.close();
		i2.afisare();
		PreluareInput();
		i2.setResult(c.getRezultat()); }

		{ofstream out("Input.txt");
		out << " ";
		out.close(); }


		
            break;
		}

    }
}

void UserInterface:: Exit() {
	if (nrUsed > 0) {
		
		int contor = 0;
		cout << endl;
		cout << "You choose to exit, in case you want a last calculation:" << endl;
		cout << "Enter 1 to add a new value:" << endl << "Enter 2 to multiply with a new value:" << endl << "Enter 3 to divide with a new value: " << endl << "Enter 4 to subtrac with a new value:" << endl;
		cout << "Enter any other number if you dont want to do anything:";
		cin >> contor;
		int numb = 0;
		double newVal = 0;
		switch (contor) {
		case 1:
			cout << "Enter number:";
			cin >> numb;
			newVal = c.operator+(numb);
			cout << "Your new result:" << newVal << endl;
			nrUsed++;
			break;
		case 2:
			cout << "Enter number:";
			cin >> numb;
			newVal = c.operator*(numb);
			cout << "Your new result:" << newVal << endl;
			nrUsed++;
			break;
		case 3:
			cout << "Enter number:";
			cin >> numb;
			newVal = c.operator/(numb);
			cout << "Your new result:" << newVal << endl;
			nrUsed++;
			break;
		case 4:
			cout << "Enter number:";
			cin >> numb;
			newVal = c.operator-(numb);
			cout << "Your new result:" << newVal << endl;
			nrUsed++;
			break;
		default:
			
			break;
		}


	}
	cout << endl;
	cout << "You made " << nrUsed << " calculations." << endl;
	cout << endl;
	cout << "Done.";

}


bool UserInterface:: operator! () {
	if (choice == 1) {
		return true;
	}
	if (choice == 0) {
		return false;
	}
}

