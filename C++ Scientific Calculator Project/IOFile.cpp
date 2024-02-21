#include "IOFile.h"
#include "Input.h"
#include "Calcul.h"
#include <vector>
#include <algorithm>
using namespace std;

InputFile::InputFile() :Input() {
	input = nullptr;
	result = 0.0;
}

InputFile::~InputFile() {
	if (input != nullptr) {
		delete[]input;
		input = nullptr;
	}
}

InputFile::InputFile(const InputFile& f) :Input(f) {
	input = new char[strlen(f.input) + 1];
	strcpy_s(input, strlen(f.input) + 1, f.input);
	result = f.result;

}

InputFile&  InputFile::operator=(InputFile& f) {
	if (&f != this) {
		Input::operator=(f);
		if (input != nullptr) {
			delete[]input;
			input = nullptr;
		}
		input = new char[strlen(f.input) + 1];
		strcpy_s(input, strlen(f.input) + 1, f.input);
		result = f.result;
	}
	return *this;
}

void InputFile::setResult(double result) {
	this->result = result;
}

double InputFile::getResult() { return this->result; }

char* InputFile:: getUserInput() {
	if (this->input != nullptr) {
		char* copie = new char[strlen(this->input) + 1];
		strcpy_s(copie, strlen(this->input) + 1, this->input);
		return copie;
	}
	else {
		return nullptr;
	}
}

void InputFile::setUserInput(char* input) {
	if (this->input != nullptr) {
		delete[]this->input;
		this->input = nullptr;
	}
	if (input != nullptr) {

		this->input = new char[strlen(input) + 1];
		strcpy_s(this->input, strlen(input) + 1, input);
	}
}

ifstream& operator>> (ifstream& file, InputFile& f)
{
	string inputFile;
	getline(file, inputFile);
	const char* aux = inputFile.c_str();
	f.input = _strdup(aux);
	return file;
}

bool comparation(Expression& a, Expression& b) {
	return a.result < b.result;
}

void InputFile::sortation() {
	vector<Expression> inputs;

	ifstream f("Saved_Calculations.txt");
	string line;
	while (getline(f, line))
	{
		int pos = line.find("Result:");
		string numb = line.substr(pos + 7);
		double rez = stod(numb);
		string rezult = line.substr(6, pos - 6);
		inputs.push_back(Expression(rez, rezult));
    }

	f.close();

	auto it = inputs.begin();
	auto inend = inputs.end();
    sort(it, inend, comparation);

	ofstream of("Saved_Calculations.txt");
	Expression e;
	for (it; it != inend; it++) {
		e = *it;
		operator<<(of, e);
	}
	of.close();
    
}

void InputFile:: afisare() {
	cout << "Input from file:" << this->input << endl;
}

char InputFile::getfileOperation() {
	return this->fileOperation;
}

void InputFile::setfileOperation(char op) {
	fileOperation = op;
}

ofstream& operator<< (ofstream& write, InputFile& f) {
	if (f.fileOperation == '0') {
    write << "Input:" << f.getUserInput()<<" ";
	write << "Result:" << f.getResult() << endl;
	}
	else
	{
		if (f.fileOperation == '*' || f.fileOperation == '/' || f.fileOperation == '^' || f.fileOperation == '#')
		{
			write << "Input:" <<"["<< f.getUserInput()<<"]" << f.fileOperation << f.numberFile << " ";
			write << "Result:" << f.getResult() << endl;
		}
		else {
        write << "Input:" << f.getUserInput() << f.fileOperation<<f.numberFile<<" ";
		write << "Result:" << f.getResult() << endl;
		}
		
	}
	
	return write;
}

void InputFile::setnumberFile(double no) {
	numberFile = no;
}


void BinaryWrite::WriteRead(){
	ofstream f("Results.bin", std::ios::binary);
	f.write((char*)&result, sizeof(result));
	f.close();
}

double BinaryWrite:: GetResult(){
	return this->result;
}

void BinaryWrite:: setResult(double rez){
	result = rez;
}

void BinaryRead:: WriteRead(){
	ifstream f("Results.bin", std::ios::binary);
	f.read((char*)&result, sizeof(result));
	f.close();
}

double BinaryRead ::GetResult() {
	return this->result;
}

void BinaryRead::setResult(double rez){
	result = rez;
}

void BinaryRead:: deleteBinary() {
	ofstream i("Results.bin", ios::binary);
	if (i.is_open()) {
		i.close();
	}
}

Expression::Expression(int res, string in) {
	input = in;
	result = res;
}

Expression::Expression() {};

ofstream& operator<<(ofstream& write, Expression& e) {
	write << "Input:" << e.input << " ";
	write <<"Result:"<< e.result<<endl;

	return write;
}