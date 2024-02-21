#include "Calcul.h"
#include <string>
#include <cstring>

using namespace std;

char operands[100];
char numbers[100];
string floatpoint[100];

double Calcul::getRezultat() {
	return this->rezultat;
}

int Calcul::Prioritate(char charCurent) {
	int k = 0;
	if (charCurent == '+' || charCurent == '-') {
		return 1; 
	}
		
	if (charCurent == '*' || charCurent == '/') {
		return 2; 
	}
		
	if (charCurent == '^'||charCurent=='#') {
		return 3; 
	}
	return 0;
		

}

char* Calcul::getInput() {
	if (this->input != nullptr) {
		char* copie = new char[strlen(this->input) + 1];
		strcpy_s(copie, strlen(this->input) + 1, this->input);
		return copie;
	}
	else {
		return nullptr;
	}
}

Calcul::Calcul() {
    input = nullptr;
	rezultat = 0;
}

Calcul::Calcul(const Calcul& c) {
	if (c.input != nullptr) {
		this->input = new char[strlen(c.input) + 1];
		strcpy_s(this->input, strlen(c.input) + 1, c.input);
	}
}

Calcul::~Calcul() {
	if (this->input != nullptr) {
		delete[]this->input;
		this->input = nullptr;
	}
}

Calcul& Calcul::operator=(Calcul& c) {
	if (this != &c) {
		if (this->input != nullptr) {
			delete[]this->input;
			this->input = nullptr;
		}
		if (c.input != nullptr) {
			this->input = new char[strlen(c.input) + 1];
			strcpy_s(this->input, strlen(c.input) + 1, c.input);
		}
	}
	return *this;
}

Calcul::Calcul(const char* input) {
	if (input != nullptr) {
		this->input = new char[strlen(input) + 1];
		strcpy_s(this->input, strlen(input)+1, input);
	}
}

void Calcul::InputPrelucrat() {
	int stack = -1,prelucrare=0,i=0,k=0;

	while (i < strlen(this->input) + 1) {
		char charCur = this->input[i];

		if ((charCur >= '0' && charCur <= '9')||charCur=='.')
		{
			while ((charCur >= '0' && charCur <= '9')||charCur=='.') {
				k++;
				numbers[prelucrare] = charCur;
				prelucrare++;
				charCur = this->input[++i];
			}
			--i;
		}
		charCur = this->input[i];

		if (k >= 1) {
			numbers[prelucrare] = ' ';
			prelucrare++;
			k = 0;
		}

		else if (charCur=='[' || charCur == '(') {
			operands[++stack] = charCur;
		}

		else if (charCur == ']') {
			while (!(stack == -1) && operands[stack] != '[') {
				numbers[prelucrare] = operands[stack];
				prelucrare++; --stack;
			}
			--stack;
		}

		else if (charCur == ')') {
			while (operands[stack] != '(') {
				numbers[prelucrare] = operands[stack];
				prelucrare++; stack--;
			}
			--stack;
		}

		else {
			if (!(charCur >= '0' && charCur <= '9')) {
			      while (!(stack == -1) && Prioritate(operands[stack]) >= Prioritate(charCur)&&operands[stack]!='(') {
					  numbers[prelucrare] = operands[stack];
					  prelucrare++; stack--;
				  }
				  operands[++stack] = charCur;
			}
		}
		i++;
	}

	while (!(stack == -1)) {
		numbers[prelucrare++] = operands[stack--];
	}
	numbers[prelucrare] = '\0';


}


void Calcul::evaluareInput() 
{
	int i = 0, stack = -1, j = 0, k = -1, a = 0,contor=0,virgula=0;
    double intregi[100],rez = 0,op;
	string s;

	while (i < strlen(numbers) + 1)
	{
		char charCur = numbers[i];
		if ((charCur >= '0' && charCur <= '9') || charCur=='.')
		{
			while ((charCur >= '0' && charCur <= '9') || charCur=='.')
			{
				floatpoint[j] = charCur;
				charCur = numbers[++i];
				j++;
				
			}
			--i;

			while (a < j) {
				s += floatpoint[++k];
				a++;
			}

			op = stod(s);
			s = " ";

			intregi[++stack] = op;
			op = 0;
		}

		if (charCur != ' ') 
		{
			double a = intregi[--stack];
			double b = intregi[++stack];
			switch (charCur)
			{
			case '+':
				rez = a + b;
				intregi[--stack] = rez;
				break;
			case '-':
				rez = a - b;
				intregi[--stack] = rez;
				break;
			case'*':
				if (a == 0 || b == 0) {
					rez = 0;
				}
				else
				rez = a * b;
				
				intregi[--stack] = rez;
				break;
			case'/':
				if (b == 0) {
					cout << "Error. Division by 0" << endl;
					contor++;
				}
				else {
                  rez = a / b;
				intregi[--stack] = rez;
				}
				break;
			case'^':
				rez = pow(a, b);
				intregi[--stack] = rez;
				break;
			case'#':
				
				rez = pow(a, 1.0 / b);
				intregi[--stack] = rez;
				break;
			default:
				break;
			}
		}
		i++;
	}
	
	if (contor == 0) {
    this->rezultat = intregi[stack];
	cout << "Result: " << this->rezultat << endl;
	}
	
	
}

void Calcul::setInput(char* input) {
	

	if (this->input != nullptr) {
		delete[]this->input;
		this->input = nullptr;
	}
	if (input != nullptr) {

		this->input = new char[strlen(input) + 1];
		strcpy_s(this->input, strlen(input) + 1, input);
	}

	else {
		this->input = nullptr;
	}
}

double Calcul:: operator+(float number) {
  return this->rezultat = this->rezultat + number;
}

double Calcul:: operator*(float number) {
	return this->rezultat *= number;
	
}

double Calcul::operator-(float number) {
	return this->rezultat -= number;
}

double Calcul::operator/(float number) {
	if (number == 0) {
		cout << "Error.Division by 0"<<endl;
		return 0;
	}

	else return this->rezultat /= number;
}

double Calcul::operator^(float number) {
	return pow(this->rezultat, number);
}

double Calcul::radical(float number) {
	return pow(this->rezultat, 1.0 / number);
}

double Calcul::FileResult(double number) {
	int contor = 0,j=0,nrused=0;
	double newval=0;
	cout << endl<<"Enter 1 to add the saved value:" << endl << "Enter 2 to multiply with the saved value:" << endl << "Enter 3 to divide with the saved value: " << endl << "Enter 4 to subtrac with the saved value:" << endl;
	cout << "Enter 5 to raise in power with the saved value." << endl << "Enter 6 for radical." << endl;
	cout << "Your choice here:";
	cin >> contor;

	this->numberFile = number;
	switch (contor) {
	case 1:
		 newval= operator+(number);
		nrused++;
		fileOperation = '+';
		break;
	case 2:
		newval=operator*(number);
		nrused++;
		fileOperation = '*';
		break;
	case 3:
		newval=operator/(number);
	   nrused++;
	   fileOperation = '/';
		break;
	case 4:
		newval=operator-(number);
		nrused++;
		fileOperation = '-';
		break;
	case 5:
		newval = operator^(number);
		nrused++;
		fileOperation = '^';
		break;
	case 6:
		if (number > 0) {
         newval = radical(number);
		nrused++;
		fileOperation = '#';
		break;
		}
		else {
			number = 0 - number;
			newval = 1 / radical(number);
			fileOperation = '#';
             break;
		}
		
		
	default:
		break;
	}
	
	this->rezultat = newval;
	
	return newval;
}

char Calcul::getfileOperation() {
	return this->fileOperation;
}

double Calcul::getnumberFile() {
	return this->numberFile;
}

