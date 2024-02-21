#pragma once
#include <iostream>
using namespace std;

class Input {
private:
	char* userInput=nullptr;
public:
	    Input();

		Input(const char* userInput);

		~Input();

		Input(const Input& i);

		Input& operator=(const Input& i);

		virtual char* getUserInput();

		virtual void setUserInput(char* input);

		bool VerificareInputLitere();

		bool VerificareInputSimbole();

		bool VerificareParanteze();

		bool VerificareOperatori();

		bool VerificareOrdineParanteze();

		bool VerificareOperatori2();

		bool VerificareVirgula();

		//friend istream& operator>> (istream& in, Input& i);

		//friend ostream& operator<<(ostream& out, const Input& i);

		char operator[](int index);

};