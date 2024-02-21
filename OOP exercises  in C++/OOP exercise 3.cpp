#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

class MyExcp :public exception {
public:
	MyExcp(const char* message) :exception(message) {

	}
};


class Tramvai {
private:
	const int nrTramvai;
	string numeVatman;
	int numarStatii;
	int* minuteStatie;
public:
	Tramvai():nrTramvai(1) {
		numeVatman = "Anonim";
		numarStatii = 2;
		minuteStatie = new int[numarStatii];
		minuteStatie[0] = 5; minuteStatie[1] = 2;
	}

	Tramvai(int nrTramvai, string nume) :nrTramvai(nrTramvai) {
		numeVatman = nume;
		numarStatii = 2;
		minuteStatie = new int[numarStatii];
		minuteStatie[0] = 5; minuteStatie[1] = 2;
	}

	Tramvai(const Tramvai& t):nrTramvai(t.nrTramvai) {
		numeVatman = t.numeVatman;
		numarStatii = t.numarStatii;
		if (t.minuteStatie != nullptr) {
			minuteStatie = new int[numarStatii];
			for (int i = 0; i < numarStatii; i++) {
				minuteStatie[i] = t.minuteStatie[i];
			}
		}
		else minuteStatie = nullptr;
	}

	~Tramvai() {
		if (minuteStatie != nullptr) {
			delete[]minuteStatie;
			minuteStatie = nullptr;
		}
	}

	Tramvai& operator= (const Tramvai& t) {
		if (&t != this) {
			if (minuteStatie != nullptr) {
				delete[]minuteStatie;
				minuteStatie = nullptr;
			}

			numeVatman = t.numeVatman;
			numarStatii = t.numarStatii;
			if (t.minuteStatie != nullptr) {
				minuteStatie = new int[numarStatii];
				for (int i = 0; i < numarStatii; i++) {
					minuteStatie[i] = t.minuteStatie[i];
				}
			}
			else minuteStatie = nullptr;

		}
		return *this;
	}

	int calculMinuteStationate(int indexStatieStart, int indexStatieEnd) {
		if (indexStatieStart >= 0 && indexStatieEnd >= 0) {
			int sum = 0;
			for (int i = indexStatieStart; i <= indexStatieEnd; i++) {
				sum += minuteStatie[i];
			}
			return sum;
		}
		else return 0;
		
	}

	virtual int totalMinuteStationate() {
		int sum = 0;
		for (int i = 0; i < numarStatii; i++) {
			sum += minuteStatie[i];
		}
		return sum;
	}

	void adaugaStatie(int nrMinute) {
		int* copy = new int[numarStatii + 1];
		for (int i = 0; i < numarStatii; i++) {
			copy[i] = minuteStatie[i];
		}
		copy[numarStatii] = nrMinute;
		delete[]minuteStatie;
		minuteStatie = copy;
		numarStatii++;
	}

	int& operator[](int index) {
		if (index >= 0) {
			return minuteStatie[index];
		}
		else
			throw MyExcp("Invalid");
	}

	friend ostream& operator<<(ostream& out, Tramvai& t);
	friend ofstream& operator<<(ofstream& file, Tramvai& t);
	friend ifstream& operator>> (ifstream& file, Tramvai& t);

};
ofstream& operator<<(ofstream& file, Tramvai& t) {
	file << t.nrTramvai << endl;
	file << t.numeVatman << endl;
	file << t.numarStatii << endl;
	for (int i = 0; i < t.numarStatii; i++) {
		file << t.minuteStatie[i] << endl;
	}
	return file;
}

ifstream& operator>> (ifstream& file, Tramvai& t) {
	file >> t.nrTramvai;
	file >> t.numeVatman;
	file >> t.numarStatii;
	int aux[100];
	for (int i = 0; i < t.numarStatii; i++) {
		file >> aux[i];
	}
	t.minuteStatie = new int[t.numarStatii];
	for (int i = 0; i < t.numarStatii; i++) {
		t.minuteStatie[i] = aux[i];
	}

	return file;
}

ostream& operator<<(ostream& out, Tramvai& t) {
	cout << "Nr tramvai:";
	out << t.nrTramvai;
	cout << endl;
	cout << "Nume";
	out << t.numeVatman;
	cout << endl;
	cout << "Numar Statii:";
	out << t.numarStatii;
	cout << endl;
	cout << "Minute:";
	for (int i = 0; i < t.numarStatii; i++) {
		out << t.minuteStatie[i] << " ";
	}
	return out;
}

class TramvaiHibrid :public Tramvai {
private:
	int capacitateBaterie;
	int timpIncarcare;
public:
	TramvaiHibrid() :Tramvai() {
		capacitateBaterie = 100;
		timpIncarcare = 2;
	}

	TramvaiHibrid(int nrTramvai, string nume, int capacitate, int timpIncaracre)
		:Tramvai(nrTramvai, nume) {
		capacitateBaterie = capacitate;
		this->timpIncarcare = timpIncaracre;
	}

	~TramvaiHibrid(){}

	TramvaiHibrid& operator= (const TramvaiHibrid& t) {
		if (&t != this) {
           Tramvai::operator=(t);
		capacitateBaterie = t.capacitateBaterie;
		timpIncarcare = t.timpIncarcare;

		}
		return *this;
	}

	void operator+ (int nr) {
		this->timpIncarcare += nr;
	}

	int totalMinuteStationate() override {
		return Tramvai::totalMinuteStationate() + timpIncarcare;
	}

	
};

bool comparatie (Tramvai* t1, Tramvai* t2) {
	return (t1->totalMinuteStationate() > t2->totalMinuteStationate());
}

int main() {


	Tramvai t1;
	Tramvai t2 = t1;
	TramvaiHibrid th;
	TramvaiHibrid th2 = th;
	Tramvai** p = new Tramvai*[3];
	p[0] =&t1; p[1] = &th; p[2] = &t2;
	for (int i = 0; i < 3; i++) {
       cout << p[i]->totalMinuteStationate() << endl;
	}

	vector<Tramvai*> t;
	t.push_back(&t1); t.push_back(&th); t.push_back(&t2);
	auto i = t.begin();
	auto j = t.end();

	sort(i, j, comparatie);
	
	for (i; i != j; i++) {
		Tramvai* aux = new Tramvai();
		aux = *i;
		cout << aux->totalMinuteStationate() << endl;
		delete[]aux;
	}

	
	

	/*ofstream f("File.txt");
	f << t1;
	f.close();

	ifstream g("File.txt");
	g >> t2;
	g.close();

	cout << t2;*/

	t1.adaugaStatie(2);
	//cout << t1;
	Tramvai t3;
	t3 = t1;
	//cout <<t3;

	cout << t1.calculMinuteStationate(0,1);
	
	try {
		Tramvai t4;
		t4[-2];
	}
	catch (MyExcp& m) {
		cerr << m.what();
	}

}