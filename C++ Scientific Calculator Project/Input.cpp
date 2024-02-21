#include <iostream>
#include <vector>
#include "Input.h"
using namespace std;

Input::Input() {
	this->userInput = nullptr;
}

Input::Input(const char* userInput) :Input()
{
	if (userInput != nullptr) {
		this->userInput = new char[sizeof(userInput) + 1];
		strcpy_s(this->userInput, sizeof(userInput) + 1, userInput);
	}
}

Input::~Input() {
	if (this->userInput != nullptr) {
		delete[] this->userInput;
		this->userInput = nullptr;
	}
}

Input::Input(const Input& i) :Input()
{
	if (i.userInput != nullptr) {
		this->userInput = new char[sizeof(i.userInput) + 1];
		strcpy_s(this->userInput, sizeof(i.userInput) + 1, i.userInput);
	}
}

Input& Input:: operator=(const Input& i) {
	if (this->userInput != nullptr) {
		delete[] this->userInput;
	}
	if (i.userInput != nullptr) {
		this->userInput = new char[sizeof(i.userInput) + 1];
		strcpy_s(this->userInput, sizeof(i.userInput) + 1, i.userInput);
	}
	else {
		this->userInput = nullptr;
	}
	return *this;

}

char* Input:: getUserInput() {
	if (this->userInput != nullptr) {
		char* copy = new char[strlen(this->userInput) + 1];
		strcpy_s(copy, strlen(this->userInput) + 1, this->userInput);
		return copy;
	}
	else return nullptr;
	
}

void Input:: setUserInput(char* input) {
	

	if (this->userInput != nullptr) {
		delete[]this->userInput;
		this->userInput = nullptr;
	}
	if (input != nullptr) {

       this->userInput = new char[strlen(input) + 1];
		strcpy_s(this->userInput, strlen(input) + 1, input);
	}

	else {
		this->userInput = nullptr;
	}
}

bool Input:: VerificareInputLitere() {
	int adevar = 0;
	if (this->userInput == nullptr) {
		cout << "Nimic de verificat,a continut simbole sau inputul este gol." << endl;
	}
	else {
		for (int i = 0; i < strlen(this->userInput); i++) {
			if ( (this->userInput[i] >= 'A' && this->userInput[i] <= 'Z') || (this->userInput[i] >= 'a' && this->userInput[i] <= 'z') ) {
				adevar++;
				delete[] this->userInput;
				this->userInput = nullptr;
				break;
			}
			
		}
		if (adevar != 0) {
			return true;
		}
		else return false;
	}

}

bool Input::VerificareInputSimbole() {
	int adevar = 0;
	if (this->userInput == nullptr) {
		cout << "Nimic de verificat, a continut litere sau inputul este gol." << endl;
	}
	else {
		for (int i = 0; i < sizeof(this->userInput); i++) {
			if (this->userInput[i] == '!' || this->userInput[i] == '"' || this->userInput[i] == '$' || this->userInput[i] == '%' ||
				this->userInput[i] == '&' || this->userInput[i] == ',' || this->userInput[i] == ':' || this->userInput[i] == ';' ||
				this->userInput[i] == '?' || this->userInput[i] == '@' || this->userInput[i] == '|' || this->userInput[i] == '\ ' ||
				this->userInput[i] == '~') {
				adevar++;
				delete[] this->userInput;
				this->userInput = nullptr;
				break;
			}
		}
		if (adevar != 0) {
			return true;
		}
		else return false;
	}
}

bool paranteze(char op) {
	if (op == '[' || op == ']' || op == '(' || op == ')') {
		return true;
	}
	else
		return false;
}

bool Input::VerificareParanteze() {
	int contor = 0;
	for (int i = 0; i < strlen(this->userInput)+1; i++) {
		if (paranteze(this->userInput[i])) {
			contor++;
		}
	}
	if (contor % 2 == 0)
		return false;
	else
		return true;
}

bool Input::VerificareOrdineParanteze() {
	int dreapta=0,stanga=0,verificare=0,j=-1,parantezaRotunda1=0,parantezaPatrata1=0,parantezaRotunda2=0,parantezaPatrata2=0;
	char* parantezele;
	for (int i = 0; i < strlen(this->userInput) + 1; ++i)
	{
		if (paranteze(this->userInput[i])) {
			verificare++;
		}
	}
	if (verificare > 0)
	{

		parantezele = new char[verificare];
		for (int i = 0; i < strlen(this->userInput) + 1; ++i) {
			if (paranteze(this->userInput[i])) {
				parantezele[++j] = this->userInput[i];
			}
		}

		for (int i = 0; i < verificare; i++) {
			if (parantezele[i] == '[' || parantezele[i] == '(') {
				stanga++;
			}
			else
				dreapta++;

			switch (parantezele[i]) {
			case'(':
				parantezaRotunda1++;
				break;
			case')':
				parantezaRotunda2++;
				break;
			case'[':
				parantezaPatrata1++;
				break;
			case']':
				parantezaPatrata2++;
				break;
			default:
				break;
			}

		}

		if ((dreapta == stanga) && ((parantezaRotunda1 == parantezaRotunda2)
			|| (parantezaPatrata1 = parantezaPatrata2)))
		{
			return false;
		}
		else return true;

		delete[]parantezele;
	}
	else return false;
	
}

bool number2(char aux) {
	if ((aux >= '0' && aux <= '9')) {
		return true;
	}
	else
		return false;
}
bool OperatoriVerificare(char op) {
	if (op == '+' || op == '-' || op == '/' || op == '*' || op == '^' || op == '#') {
		return true;
	}
	else
		return false;
}


bool Input::VerificareVirgula() {
	int i = 0, virgula = 0,operation=1,trueflag=0;
	while (i < strlen(this->userInput) + 1) {
		char charCurent = userInput[i];
		if (charCurent == '.' && number2(userInput[++i]) && number2(userInput[i - 2]))
		{
			virgula++;
			//i++;
		}
		if (OperatoriVerificare(charCurent)|| charCurent=='\0') {
			if (virgula > operation) {
				trueflag++;
				break;
			}
			else
				virgula = 0;
		}

		i++;

	}
	if (trueflag == 0)
		return false;
	else return true;
}


bool Input::VerificareOperatori2() {
	int operatori = 0, numbers = 0,contor=0;
	for (int i = 0; i < strlen(this->userInput) + 1; ++i) {
		char aux = this->userInput[i];
		if ((aux >= '0' && aux <= '9') || aux == '.')
		{
			while ( (aux >= '0' && aux <= '9') || aux == '.') {
			contor++;
			aux = this->userInput[++i];
		    }
		    --i;
         }
		
		if (contor == 1) {
			numbers += contor;
		}
		else if (contor > 1) {
			contor -= (contor - 1);
			numbers += contor;
		}
		contor = 0;
	}

	for (int i = 0; i < strlen(this->userInput)+1; ++i) {
		if (OperatoriVerificare(this->userInput[i])) {
			operatori++;
		}
	}

	if (operatori == (numbers - 1)) {
		return false;
	}
	else return true;
}

bool number(char aux) {
	if ((aux >= '0' && aux <= '9')||aux==']'||aux=='['||aux=='('||aux==')') {
		return true;
	}
	else
		return false;
	
}

bool Input::VerificareOperatori() {
	bool* array = new bool[strlen(this->userInput)+2];
	int j = 0,contor=0;
	for (int i = 0; i < strlen(this->userInput); i++) {
		if (number(this->userInput[i])) {
			array[++j] = true;
		}
		else
		{
			array[++j] = false;
		}
	}
	j = 0;
	for (int i = 0; i < strlen(this->userInput)+2; i++)
	{
		if (array[++j] == false)
		{
			if (array[--j] == true)
			{
				j = j + 2;
				if (array[j] != true) {
					contor++;
					break;
				}
				else {
					j = j - 1;
				}

			}
			else
			{
				contor++;
				break;
			}
		}
	}
	delete[]array;
	if (contor != 0) {
		return true;
	}
	else return false;
}

//istream& operator>> (istream& in, Input& i) {
//	cout << "Input:" << endl;
//	if (i.userInput != nullptr) {
//		delete[] i.userInput;
//	}
//	char aux[100];
//	in >> ws;
//	in.getline(aux,100);
//	i.userInput = new char[strlen(aux) + 1];
//	strcpy_s(i.userInput, strlen(aux)+1, aux);
//
//	return in;
//}

 /*ostream& operator<<(ostream& out, const Input& i) {
	out << "Input:" << i.userInput << endl;
	return out;
}*/

 char Input::operator[](int index) {
	 if (index <= strlen(this->userInput) && this->userInput!=nullptr) {
		 return this->userInput[index];
	 }
 }