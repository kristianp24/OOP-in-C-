#include <iostream>  
#include <fstream>
#include <vector>
#include <list>
#include <map>
using namespace std;

class Art {
private:
	char* autor;
	char* denumire;
	int an;
	int nrVizitatori;
public:
	int getnrVizitatori() {
		return nrVizitatori;
	}

	int getAn() {
		return an;
	}
	Art() {

	}
	virtual double valoareDinVizionari() = 0;
	Art(int an) {
		this->an = an;
	}


};

class Tablou :public Art {
private:
	char* curentArtistic;
	int tipSuport;
	int tipVopsea;
	float pretBiletAcces;
public:

	char* getcurentArtistic() {
		char* copy = new char[strlen(curentArtistic) + 1];
		strcpy_s(copy, strlen(curentArtistic) + 1, curentArtistic);
		return copy;
	}

	int getTipSuport() {
		return tipSuport;
	}
	int getTipVopsea() {
		return tipVopsea;
	}
	float getPretBilet() {
		return pretBiletAcces;
	}

	Tablou() {
		curentArtistic = nullptr;
		tipSuport = 1;
		tipVopsea = 2;
		pretBiletAcces = 50.5;
	}

	Tablou(const char* artist,int suport,int vopsea,float bilet,int an):Art(an) {
		if (artist != nullptr) {
			curentArtistic = new char[strlen(artist) + 1];
			strcpy_s(curentArtistic, strlen(artist) + 1, artist);
		}
		tipSuport = suport;
		tipVopsea = vopsea;
		pretBiletAcces = bilet;
	}

	~Tablou() {
		if (curentArtistic != nullptr) {
			delete[]curentArtistic;
		}
	}

	Tablou(const Tablou& t) {
		if (t.curentArtistic != nullptr) {
			curentArtistic = new char[strlen(t.curentArtistic) + 1];
			strcpy_s(curentArtistic, strlen(t.curentArtistic) + 1, t.curentArtistic);

		}
		else curentArtistic = nullptr;
		tipSuport = t.tipSuport;
		tipVopsea = t.tipVopsea;
		pretBiletAcces = t.pretBiletAcces;
	}

	Tablou& operator= (const Tablou& t) {
		if (&t != this) {
			if (curentArtistic != nullptr) {
				delete[]curentArtistic;
			}
			if (t.curentArtistic != nullptr) {
				curentArtistic = new char[strlen(t.curentArtistic) + 1];
				strcpy_s(curentArtistic, strlen(t.curentArtistic) + 1, t.curentArtistic);

			}
			else curentArtistic = nullptr;
			tipSuport = t.tipSuport;
			tipVopsea = t.tipVopsea;
			pretBiletAcces = t.pretBiletAcces;

		}
		return *this;
	}

	double valoareDinVizionari() override {
        return pretBiletAcces * getnrVizitatori();
	}

	bool operator<= (Tablou& t) {
		return this->getAn() <= t.getAn();
	}
	bool operator> (Tablou& t) {
		return this->getAn() > t.getAn();
	}

	friend ofstream& operator<< (ofstream& out, Tablou& t);
	friend istream& operator>> (istream& in, Tablou& t);
};

class Muzeu {
private:
	list<Tablou> colectie;
public:
	void operator+= (Tablou t) {
		colectie.push_back(t);
	}
	void operator-= (Tablou& t) {
		for (list<Tablou>::iterator it = colectie.begin(); it != colectie.end();
			it++) {
			if (strcmp(it->getcurentArtistic(),t.getcurentArtistic())==0) {
				colectie.erase(it);
				break;
			}
		}
		
	}
	Tablou* getCurentArtistic(const char* curentArtistic){
		int contor = 0, j = -1;
		auto it = colectie.begin();
		for (it; it != colectie.end(); it++) {
			if (strcmp(it->getcurentArtistic(), curentArtistic) == 0) {
				contor++;
			}
		}
		Tablou* t = new Tablou[contor];
		it = colectie.begin();
		for (it; it != colectie.end(); it++) {
			if (strcmp(it->getcurentArtistic(), curentArtistic) == 0) {
				t[++j] = *it;
			}
		}

		return t;
	}

	friend ofstream& operator<<(ofstream& file, Muzeu& m);

};
ofstream& operator<<(ofstream& file, Muzeu& m) {
	auto it = m.colectie.begin();
	for (it; it != m.colectie.end(); it++) {
		file << *it;
	}
	return file;
}

//CasaSmart(string ceva, int a,int b,int c,int* etaje) :Casa(a,b,c,etaje) {
//
//}


istream& operator>> (istream& in, Tablou& t) {
	cout << "Artist";
	char buf[100];
	in >> buf;
	t.curentArtistic = new char[strlen(buf) + 1];
	strcpy_s(t.curentArtistic, strlen(buf) + 1, buf);
	cout << "Tip suport:";
	in >> t.tipSuport;
	cout << "Tip Vopsea:";
	in >> t.tipVopsea;
	cout << "Bilet pret:";
	in >> t.pretBiletAcces;

	return in;
}
ofstream& operator<< (ofstream& out, Tablou& t) {
	cout << "Artist:";
	out << t.curentArtistic;
	cout << "Tip suport:";
	out << t.tipSuport;
	cout << "Tip Vopsea:";
	out<< t.tipVopsea;
	cout << "Bilet pret:";
	out<< t.pretBiletAcces;

	return out;
}


int main() {
	Tablou t1("BNN",24,5,5.6,2015);
	Tablou t2("AAN", 1, 2, 25.5,2018);
	/*cout << t2;
	t1 = t2;
	cout << t1;*/

	Muzeu m1;
	m1 += t1;
	m1 += t2;
	/*m1 -= t1;*/
	//cout << *m1.getCurentArtistic("BNN");
	/*if (t1 <= t2) {
		cout << t1;
	}*/
	ofstream f("Muzeu.txt");
	f << m1;
	f.close();

	map<string, Tablou> m;
	m.insert(make_pair("Operan", t1));

}