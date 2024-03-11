#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Autobuz {
private:
	int nrLinie;
	static double pretBilet;
	char* marcaAutobuz;
	int numarCurseZilnice;
	int numarLocuri;

public:
	Autobuz() {
		nrLinie = 0;
		marcaAutobuz = nullptr;
		numarCurseZilnice = 5;
		numarLocuri = 15;
	}

	Autobuz(int linia, const char* marca):Autobuz() {
		nrLinie = linia;
		if (marca != nullptr) {
         marcaAutobuz = new char[strlen(marca) + 1];
		 strcpy_s(marcaAutobuz, strlen(marca) + 1, marca);
		}
		
	}

	Autobuz(const Autobuz& a) {
		nrLinie = a.nrLinie;
		if (a.marcaAutobuz) {
         marcaAutobuz = new char[strlen(a.marcaAutobuz) + 1];
		strcpy_s(marcaAutobuz, strlen(a.marcaAutobuz) + 1, a.marcaAutobuz);

		}
		numarCurseZilnice = a.numarCurseZilnice;
		numarLocuri = a.numarLocuri;
	}

	//~Autobuz() {
	//	if (marcaAutobuz != nullptr) {
	//		delete[]marcaAutobuz;
	//	}
	//}

	Autobuz& operator=(Autobuz& a) {
		if (&a != this) {
        if (marcaAutobuz != nullptr) {
			delete[]marcaAutobuz;
		}
		nrLinie = a.nrLinie;
		if (a.marcaAutobuz!=nullptr) {
			marcaAutobuz = new char[strlen(a.marcaAutobuz) + 1];
			strcpy_s(marcaAutobuz, strlen(a.marcaAutobuz) +1, a.marcaAutobuz);

		}
		numarCurseZilnice = a.numarCurseZilnice;
		numarLocuri = a.numarLocuri;

		}
		
		return *this;
     }

	int venitMaxim() {
		return pretBilet * numarLocuri * numarCurseZilnice;
	}

	bool poateRealizaCursa(int nrLocuri) {
		int dif = this->numarLocuri - nrLocuri;
		if (dif >= 0)
		{
			return true;
		}
		else return false;
	}
	friend ostream& operator<<(ostream& out, Autobuz& a);

	int getnrcurse() {
		return this->numarCurseZilnice;
	}

	void setnrCurse(int nr) {
		this->numarCurseZilnice += nr;
	}

	Autobuz& operator+ (int nr) {
		Autobuz copy;
		copy.numarCurseZilnice = this->numarCurseZilnice + nr;
		
		return copy;
	}
	friend Autobuz& operator+ (int nr, Autobuz a);

	void scriereBinar() {
		ofstream f("File.bin", ios::binary);
		f.write((char*)&nrLinie, sizeof(nrLinie));
		f.write((char*)&pretBilet, sizeof(pretBilet));
		int length = strlen(marcaAutobuz);
		f.write((char*)&length, sizeof(length));
		f.write(marcaAutobuz, strlen(marcaAutobuz) + 1);
		f.write((char*)&numarCurseZilnice, sizeof(numarCurseZilnice));
		f.write((char*)&numarLocuri, sizeof(numarLocuri));
		f.close();
    }

	void citireBinar() {
		ifstream g("File.bin", ios::binary);
		g.read((char*)&nrLinie, sizeof(nrLinie));
		g.read((char*)&pretBilet, sizeof(pretBilet));
		int length = 0;
		char buffer[100];
		g.read((char*)&length, sizeof(length));
		g.read(buffer, length+1);
		marcaAutobuz = new char[length+1];
		strcpy_s(marcaAutobuz, length + 1, buffer);
		g.read((char*)&numarCurseZilnice, sizeof(numarCurseZilnice));
		g.read((char*)&numarLocuri, sizeof(numarLocuri));
		g.close();
	}

	const char* getMarca() {
		char* copy = new char[strlen(marcaAutobuz) + 1];
		strcpy_s(copy, strlen(marcaAutobuz) + 1, marcaAutobuz);
		return copy;
	}

	int operator() () {
		return this->nrLinie;
	}

};

Autobuz& operator+ (int nr,Autobuz a) {
	Autobuz copie;
	copie.numarCurseZilnice = a.numarCurseZilnice + nr;
	return copie;
	
}

double Autobuz::pretBilet = 5.5;

class Autobaza {
private:
	int nrAutobuze;
	Autobuz** a;
public:
	Autobaza(int nr, Autobuz** b) {
		if (nr > 0 && b != nullptr) {
        nrAutobuze = nr;
		a = new Autobuz * [nr];
		for (int i = 0; i < nr; i++) {
			a[i] = b[i];
		}
		}
		else {
			nr = 0;
			a = nullptr;
		}
	}

	Autobaza(const Autobaza& b) {
		nrAutobuze = b.nrAutobuze;
		if (b.a != nullptr) {
		a = new Autobuz * [b.nrAutobuze];
		for (int i = 0; i < nrAutobuze; i++) {
			a[i] = b.a[i];
		}
	}
	}

	//~Autobaza() {
	//	if (a != nullptr) {
	//		delete[]a;
	//	}
	//}

	Autobaza& operator= (Autobaza& b) {
		if (&b != this) {
			if (a != nullptr) {
				delete[]a;
			}

			nrAutobuze = b.nrAutobuze;
			if (b.a != nullptr) {
				a = new Autobuz * [b.nrAutobuze];
				for (int i = 0; i < nrAutobuze; i++) {
					a[i] = b.a[i];
				}
				
			}

		}
		return *this;
	}

	int numarDeAutobuzeprodusde(const char* marca)
	{
		int conto = 0;
		for (int j = 0; j < nrAutobuze; j++)
		{
			Autobuz* z=new Autobuz[2];
			z[j]=*a[j];

			if (strcmp(marca,z[j].getMarca())==0) {
				conto++;
			}
		}
		return conto;
	}

	void adaugaAutobuz(Autobuz& bus) {
		Autobuz** copie = new Autobuz * [nrAutobuze + 1];
		for (int i = 0; i < nrAutobuze; i++) {
			copie[i] = a[i];
		}
		copie[nrAutobuze] = &bus;
		delete[]a;
		a = copie;
		nrAutobuze++;
	}


};

ostream& operator<<(ostream& out, Autobuz& a) {
	cout << "Nr linie:";
	out << a.nrLinie;
	cout << endl;
	cout << "Pret bilet:";
	out << a.pretBilet;
	cout << endl;
	cout << "Marca";
	out << a.marcaAutobuz;
	cout << endl;
	cout << "Nr cursuri zilnice:";
	out << a.numarCurseZilnice;
	cout << endl;
	cout << "Nr locuri:";
	out << a.numarLocuri;

	return out;
}

template<typename T>
T produs(T a, T b) {
	return a * b;
}

class Myexcp :public exception {
public:
	Myexcp(const char* message) :exception(message) {

	}
};

template<typename T,int n = 1>
class AutobazaTemplate {
private:
	T mijloace[n];
public:
	AutobazaTemplate() {

	}
	T& operator[] (int index) {
		if (index >= 0 && index <= n) {
			return mijloace[index];
		}
		else throw Myexcp("Invalid number");
	 }
};

int main() {

	
	Autobuz a(7,"Benz");
	Autobuz nou(2,"Audi");
	Autobuz d(5,"Benz");
	/*float c = 5, b = 2;
	cout << produs<float>(c, b) << endl;*/
	//cout<< a + 5;
	/*nou = 5 + a;
	d = 5 + a;*/
	/*d.scriereBinar();
	a.citireBinar();*/
	//cout << a;
	Autobuz** k = new Autobuz * [2];
	k[0] = &a; k[1] = &d;
	Autobaza ab(2, k);
	//cout<<ab.numarDeAutobuzeprodusde("Benz");
	ab.adaugaAutobuz(nou);
    AutobazaTemplate<Autobuz, 2> at;
	at[0] = d;
	try {
		cout << at[-1];
	}
	catch (Myexcp m) {
		cout << m.what() << endl;
	}

	//vector<AutobazaTemplate<Autobuz,3>> v1;
	map<int, Autobuz> m1;
	m1.insert(make_pair(1, a));
	m1.insert(make_pair(2, d));
	auto it = m1.begin();
	for (it; it != m1.end(); it++) {
		cout << it->first << " " << it->second;
		cout << endl;
	}
	cout << endl;
	cout << a();


}