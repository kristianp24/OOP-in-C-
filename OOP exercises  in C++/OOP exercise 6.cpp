#include<fstream>
#include <string>
#include<vector>
#include <set>
#include<map>
using namespace std;

class Medic {
private:
	const int codParafa;
	char* nume;
	string specializare;
	int tarifConsultatie;
	static int cod;
public:
	Medic():codParafa(++cod) {
		nume = new char[strlen("Anonim") + 1];
		strcpy_s(nume, strlen("Anonim") + 1, "Anonim");
		specializare = "generala";
		tarifConsultatie = 0;
	}
	Medic(int cpd_, const char* nume, string specializare, int tarif) :codParafa(cpd_) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
		this->specializare = specializare;
		this->tarifConsultatie = tarif;
	}
	Medic(const Medic& m):codParafa(m.codParafa) {
		if (m.nume != nullptr) {
			nume = new char[strlen(m.nume) + 1];
			strcpy_s(nume, strlen(m.nume) + 1, m.nume);
		}
		else nume = nullptr;
		specializare = m.specializare;
		tarifConsultatie = m.tarifConsultatie;
	}
	~Medic() {
		if (nume != nullptr) {
			delete[]nume;
			nume = nullptr;
		}
	}
	Medic& operator=(const Medic& m) {
		if (&m != this) {
			if (nume != nullptr) {
				delete[]nume;
				nume = nullptr;
			}
			if (m.nume != nullptr) {
				nume = new char[strlen(m.nume) + 1];
				strcpy_s(nume, strlen(m.nume) + 1, m.nume);
			}
			else nume = nullptr;
			specializare = m.specializare;
			tarifConsultatie = m.tarifConsultatie;

		}
		return *this;
	}
	int getTarif() {
		return tarifConsultatie;
	}

	//friend ostream& operator<< (ostream& out, Medic& m);
	friend ostream& operator<< (ostream& out,const Medic& m);
	friend istream& operator>> (istream& in, Medic& m);
};
ostream& operator<< (ostream& out, const Medic& m) {
	out << m.codParafa << endl;
	out << m.nume << endl;
	out << m.specializare << endl;
	out << m.tarifConsultatie << endl;
	return out;
}
//ostream& operator<< (ostream& out, Medic& m) {
//	out << m.codParafa << endl;
//	out << m.nume << endl;
//	out << m.specializare << endl;
//	out << m.tarifConsultatie << endl;
//	return out;
//}
istream& operator>> (istream& in, Medic& m) {
	char buffer[100];
	cout << "Nume:";
	in.getline(buffer, 100);
	cout << endl;
	if (m.nume != nullptr) {
		delete[]m.nume;
	}
	m.nume = new char[strlen(buffer) + 1];
	strcpy_s(m.nume, strlen(buffer) + 1, buffer);
	cout << "Specializare:";
	getline(in,m.specializare);
	cout << endl;
	cout << "Tarif:";
	in >> m.tarifConsultatie;

	return in;
}
int Medic::cod = -1;

class Spital {
private:
	Medic* medici;
	int nrMedici;
	string denumire;
	char tip;
public:
	Spital() {
		nrMedici = 0;
		medici = nullptr;
		denumire = "Spital 0";
		tip = 'S';
	}
	Spital(Medic* m, int medicii, string denumire, char tipul):Spital() {
		nrMedici = medicii;
		if (nrMedici > 0) {
			medici = new Medic[nrMedici];
			for (int i = 0; i < nrMedici; i++) {
				medici[i] = m[i];
			}
		}
		this->denumire = denumire;
		tip = tipul;
	}
	Spital(const Spital& s) {
		nrMedici = s.nrMedici;
		if (s.medici != nullptr) {
			medici = new Medic[nrMedici];
			for (int i = 0; i < nrMedici; i++) {
				medici[i] = s.medici[i];
			}
		}
		else medici = nullptr;
		denumire = s.denumire;
		tip = s.tip;
	}
	~Spital() {
		if (medici != nullptr) {
			delete[]medici;
			medici = nullptr;
		}
	}

	Spital& operator=(const Spital& s) {
		if (&s != this) {
        if (medici != nullptr) {
			delete[]medici;
			medici = nullptr;
		}
		nrMedici = s.nrMedici;
		if (s.medici != nullptr) {
			medici = new Medic[nrMedici];
			for (int i = 0; i < nrMedici; i++) {
				medici[i] = s.medici[i];
			}
		}
		else medici = nullptr;
		denumire = s.denumire;
		tip = s.tip;
       }
		return *this;
	}

	void operator+=(Medic m) {
		Medic* copy = new Medic[nrMedici + 1];
		for (int i = 0; i < nrMedici; i++) {
			copy[i] = medici[i];
		}
		copy[nrMedici] = m;
		delete[]medici;
		medici = copy;
	}

	/*bool operator> (Spital s) {
		return this->nrMedici > s.nrMedici;
	}
	bool operator<(Spital s) {
		return this->nrMedici < s.nrMedici;
	}
	bool operator==(Spital s) {
		return this->nrMedici = s.nrMedici;
	}*/

	explicit operator double() {
		double sum = 0;
		for (int i = 0; i < nrMedici; i++) {
			sum += medici[i].getTarif();
		}
		return sum / nrMedici;
	}

	void operator-= (Medic& m) {
		vector<Medic> v;
		for (int i = 0; i < nrMedici; i++) {
			if (&medici[i]!=&m) {
				v.push_back(medici[i]);
			}
		 }
	}

	friend ostream& operator<<(ostream& out, Spital& s);
};
ostream& operator<<(ostream& out, Spital& s) {
	cout << "Nr medici:"; out << s.nrMedici << endl;
	cout << "Medici:" << endl;
	for (int i = 0; i < s.nrMedici; i++) {
		operator<<(out, s.medici[i]);
	}
	cout << "Denumire spital:"; out << s.denumire << endl;
	cout << "Tip:"; out << s.tip << endl;
	return out;
}

int main() {
	Medic m1;
	Medic m2(123, "Gh Marinescu", "Medicina interna", 100);
	Medic m3 = m1;
	Medic m4; /*cin >> m4;*/
	m1 = m4;
	//cout << m1 << m2 << m3 << m4;

	Medic vect[4] = { m1,m2,m3,m4 };
	Spital s1;
	Spital s2(vect, 4, "Clinic de urgenta", 'S');
	Spital s3 = s2;
	s1 = s3;
	Medic m5(456, "Costel Popescu", "Oftamolog", 150);
	s1 += m5;
	/*cout << s1 << s2 << s3;*/

	/*if (s1 > s3) cout << "S1 > S3" << endl;
	else if (s1 < s3) cout << " S1<S3" << endl;
	else if (s1 == s3) cout << "S1=S3" << endl;*/
	//cout << (double)s2;

	s3 -= m2;

	set<Medic> setMedici;
	setMedici.insert(m1);
	setMedici.insert(m2);
	setMedici.insert(m3);
	setMedici.insert(m4);

	/*for (auto it = setMedici.begin(); it != setMedici.end(); it++) {
		cout << *it;
	}*/
	map<int, Medic> date;
	date.insert(make_pair(1, m1));
	date.insert(make_pair(2, m2));
	auto it = date.begin();
	for (it; it != date.end(); it++) {
		cout << it->first << " " << it->second;
	}
}