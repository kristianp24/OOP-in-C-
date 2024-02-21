#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

enum functie {
	servant,selfFormatie,voluntar,sofer
};


class MyException :public exception {
public:
	MyException(const char* message):exception(message) {

	}
};

static int i = 0;
class Pompier {
public:
	const int idPompier;
	char* nume;
	functie f;
	int nrInterventii;
	int* durate;

public:
	Pompier() :idPompier(++i) {
		nume = new char[strlen("Nume") + 1];
		strcpy_s(nume, strlen("Nume") + 1, "Nume");

		nrInterventii = 2;
		durate = new int[nrInterventii];
		durate[0] = 5; durate[1] = 10;


	}

	

	Pompier(const char* nume, functie a):Pompier() {
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		f = a;
	}

	~Pompier() {
		if (nume != nullptr) {
			delete[]nume;
			nume = nullptr;
		}
		if (durate = nullptr) {
			delete[]durate;
			durate = nullptr;
		}
	}

	Pompier(const Pompier& p) :idPompier(++i) {
		if (p.nume != nullptr) {
         this->nume = new char[strlen(p.nume) + 1];
		strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);

		}

		f = p.f;
		nrInterventii = p.nrInterventii;
		if (p.durate != nullptr) {
			durate = new int[nrInterventii];
			for (int i = 0; i < nrInterventii; i++) {
				durate[i] = p.durate[i];
			}
		}
		else durate = nullptr;
		
	}

	Pompier& operator= (const Pompier& p) {
		if (&p != this) {
			if (nume != nullptr) {
				delete[]nume;
				nume = nullptr;
			}
			if (durate = nullptr) {
				delete[]durate;
				durate = nullptr;
			}

			if (p.nume != nullptr) {
				this->nume = new char[strlen(p.nume) + 1];
				strcpy_s(this->nume, strlen(nume) + 1, p.nume);

			}

			f = p.f;
			nrInterventii = p.nrInterventii;
			if (p.durate != nullptr) {
				durate = new int[nrInterventii];
				for (int i = 0; i < nrInterventii; i++) {
					durate[i] = p.durate[i];
				}
			}
		}
		return *this;
	}

	void adaugaInterventie(int durata) {
		int* copy = new int[nrInterventii + 1];
		for (int i = 0; i < nrInterventii; i++) {
			copy[i] = durate[i];
		}
		copy[nrInterventii] = durata;

		delete[]durate;
		durate = copy;
		nrInterventii++;
	}

	float durataMedie() {
		int sum = 0;
		for (int i = 0; i < nrInterventii; i++) {
			sum += durate[i];
		}

		return sum / nrInterventii;
	}

	int nrInterventi(int numar) {
		int contor = 0;
		for (int i = 0; i < nrInterventii; i++) {
			if (durate[i] = numar) {
				contor++;
			}
		}

		return contor;
	}

	int& operator[] (int index) {
		if (index <= this->nrInterventii && index >= 0) {
			return durate[index];
		}
		else
			throw MyException("Invalid");
	}

	friend ostream& operator<< (ostream& write, Pompier& p);
	friend ofstream& operator<< (ofstream& file, Pompier& p);
	friend ifstream& operator>> (ifstream& file,  Pompier& p);
};

ofstream& operator<< (ofstream& file, Pompier& p) {
	//ofstream f("File.bin", ios::binary);
	file.write((char*)&p.idPompier, sizeof(p.idPompier));
	int length = strlen(p.nume);
	file.write((char*)&length, sizeof(length));
	file.write(p.nume, length + 1);
	

	file.write((char*)&p.nrInterventii, sizeof(p.nrInterventii));
	
	for (int i = 0; i < p.nrInterventii; i++) {
		file.write((char*)&p.durate[i], sizeof(p.durate[i]));
	}

	return file;

}

ifstream& operator>> (ifstream& file, Pompier& p) {
	
	file.read((char*)&p.idPompier, sizeof(p.idPompier));
	int length = 0;
	file.read((char*)&length, sizeof(length));
	
	char* buffer = new char[length + 1];
	file.read(buffer, length + 1);
	p.nume = buffer;

	file.read((char*)&p.nrInterventii, sizeof(p.nrInterventii));
	delete[]p.durate;
	p.durate = new int[p.nrInterventii];
	for (int i = 0; i < p.nrInterventii; i++) {
		file.read((char*)&p.durate[i], sizeof(p.durate[i]));
	}

	return file;

}

ostream& operator<< (ostream& write, Pompier& p) {
	cout << "Id:";
	write << p.idPompier << endl;
	cout << "Nume:";
	write << p.nume;
	cout << "Functie";
	write << p.f;
	cout << "Nr Intervanti:";
	write << p.nrInterventii;
	cout << "Durate:";
	for (int i = 0; i < p.nrInterventii; i++) {
		write << p.durate[i] << " ";
	}
	cout << endl;

	return write;
}

class FormatieInterventie {
private:
	char idFormat[30];
	int nrPompieri;
	Pompier** pompieri;
public:
	FormatieInterventie() {
		char* buffer = new char[strlen("Echipa") + 1];
		strcpy_s(buffer, strlen("Echipa") + 1, "Echipa");
		strcpy_s(idFormat, strlen(buffer) + 1, buffer);

		nrPompieri = 2;
		Pompier* p5=new Pompier();
		Pompier* p7=new Pompier();
		Pompier* vp[] = { p5,p7 };
		pompieri = new Pompier*[2];
		pompieri[0] = vp[0];
		pompieri[1] = vp[1];

	}

	~FormatieInterventie() {
		if (pompieri != nullptr) {
			delete[]pompieri;
			pompieri = nullptr;
		}
	}

	FormatieInterventie(const FormatieInterventie& f) {
		if (f.idFormat != NULL) {
         strcpy_s(idFormat, strlen(f.idFormat)+1, f.idFormat);
		}
		
		nrPompieri = f.nrPompieri;
		if (f.pompieri != nullptr) {
			pompieri = new Pompier * [nrPompieri];
			for (int i = 0; i < nrPompieri; i++) {
				pompieri[i] = f.pompieri[i];
			}

		}
		else pompieri = nullptr;
	}

	FormatieInterventie& operator=(FormatieInterventie& f) {
		if (&f != this) {
			if (pompieri != nullptr) {
				delete[]pompieri;
				pompieri = nullptr;
			}
			if (f.idFormat != NULL) {
				strcpy_s(idFormat, strlen(f.idFormat) + 1, f.idFormat);
			}

			nrPompieri = f.nrPompieri;
			if (f.pompieri != nullptr) {
				pompieri = new Pompier * [nrPompieri];
				for (int i = 0; i < nrPompieri; i++) {
					pompieri[i] = f.pompieri[i];
				}

			}
			else pompieri = nullptr;
		}
	}
	friend ofstream& operator<<(ofstream& file, FormatieInterventie& f);
	friend ifstream& operator>> (ifstream& file, FormatieInterventie& f);
};

ofstream& operator<<(ofstream& file, FormatieInterventie& f) {
	int length = strlen(f.idFormat)+1;
	file.write((char*)&length, sizeof(length));
	file.write(f.idFormat, length);

	file.write((char*)&f.nrPompieri, sizeof(f.nrPompieri));
	for (int i = 0; i < f.nrPompieri; i++) {
		operator<<(file, *f.pompieri[i]);
	}
	return file;
}
 
ifstream& operator>> (ifstream& file, FormatieInterventie& f) {
	 int length = 0;
	 file.read((char*)&length, sizeof(length));
	 file.read(f.idFormat, length);

	 file.read((char*)&f.nrPompieri, sizeof(f.nrPompieri));
	 for (int i = 0; i < f.nrPompieri; i++) {
		 operator>>(file, *f.pompieri[i]);
	 }
	 return file;
}


int main()
{
     Pompier p("Anel",functie::sofer);
	/* Pompier p2 = p;
	 cout << p2;*/

	 ofstream f("File.bin", ios::binary);
	 f << p;
	 f.close();
	 ifstream g("File.bin", ios::binary);
	 Pompier p3;
	 g >> p3;
	// cout << p3;

	 Pompier p5;
	 //cout << p5;

	 FormatieInterventie fi;
	 ofstream f1 ("File2.bin", ios::binary);
	 f1 << fi;
	 f1.close();

	 FormatieInterventie f5;
	 ifstream f2("File2.bin", ios::binary);
	 f2 >> f5;
	 f2.close();
	

	 vector<Pompier> v1;
	 
	 v1.push_back(p3); v1.push_back(p); v1.push_back(p5);
	 Pompier* aux = new Pompier[v1.size()];
	 auto fillim = v1.begin();
	 auto mbarim = v1.end();
	 vector<int> s;
	 int suma=0,j=-1;

	 for (fillim; fillim != mbarim; fillim++) {
		 aux[++j] = *fillim;
		 for (int i = 0; i < aux[j].nrInterventii; i++) {
			 suma += aux[j].durate[i];
		 }
		 s.push_back(suma);
		 suma = 0;

	 }
	 //delete[] aux;

	 auto i = s.begin();  
	 auto k = s.end();
	 for (i; i != k; i++) {
		 cout << *i << endl;
	 }
	 

	/*try {
		Pompier p1;
		cout<<p1[-10];
	}
	catch(MyException& m){
		cerr << m.what() << endl;
	}
	catch (...) {
		cerr << "Orice" << endl;
	}*/
}