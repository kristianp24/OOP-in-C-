#include <iostream>
#include <fstream>
using namespace std;

class MyExcp :public exception {
public:
	MyExcp(const char* message) :exception(message) {

	}
};
enum clasa {
	I,II,Cuseta
};

class VagonPasageri {
protected:
	string codVagon;
	clasa tip;
	int nrLocuri;
	int* locuriOcupate;
	bool esteOcupat;
	static int NR_MAXIM_LOCURI;
public:
	VagonPasageri() {
		codVagon = "";
		tip = II;
		nrLocuri = 0;
		locuriOcupate = nullptr;
		esteOcupat = false;
	}

	clasa getTip() {
		return tip;
	}

	int getNrLocuri() {
		return nrLocuri;
	}

	int* getlocuriOcupate() {
		int* copy = new int[nrLocuri];
		for (int i = 0; i < nrLocuri; i++) {
			copy[i] = locuriOcupate[i];
		}
		return copy;
	}

	VagonPasageri(string cod, clasa t, int locuri, int* ocupate):VagonPasageri() {
		codVagon = cod;
		tip = t;
		if (locuri <= 250) {
			nrLocuri = locuri;
		}
		if (ocupate != nullptr) {
			locuriOcupate = new int[locuri];
			for (int i = 0; i < nrLocuri; i++) {
				locuriOcupate[i] = ocupate[i];
			}
		}
	
	}

	VagonPasageri(const VagonPasageri& v) {
		codVagon = v.codVagon+"_duplicat";
		tip = v.tip;
		nrLocuri = v.nrLocuri;
		esteOcupat = v.esteOcupat;
		if (v.locuriOcupate != nullptr) {
			for (int i = 0; i < nrLocuri; i++) {
				locuriOcupate[i] = v.locuriOcupate[i];
			}
		}
		else locuriOcupate = nullptr;
	}

	~VagonPasageri() {
		if (locuriOcupate != nullptr) {
			delete[]locuriOcupate;
			locuriOcupate = nullptr;
		}
	}

	VagonPasageri& operator= (const VagonPasageri& v) {
		if (&v != this) {
          if (locuriOcupate != nullptr) {
			delete[]locuriOcupate;
			locuriOcupate = nullptr;
		  }
		  codVagon = v.codVagon+"_duplicat";
		  
		  tip = v.tip;
		  nrLocuri = v.nrLocuri;
		  esteOcupat = v.esteOcupat;
		  if (v.locuriOcupate != nullptr) {
			  locuriOcupate = new int[v.nrLocuri];
			  for (int i = 0; i < nrLocuri; i++) {
				  locuriOcupate[i] = v.locuriOcupate[i];
			  }
		  }
		  else locuriOcupate = nullptr;
      	}
		return *this;
	}

    explicit operator float() {
		return (float)nrLocuri;
	}

	bool operator[](int index) {
		if (index >= 0 && index <= nrLocuri) {
			if (locuriOcupate[index] == 0) {
				return true;
			}
			else return false;
		}
		else {
			throw MyExcp("Invalid");
		}
	}

	void Raport() {
		int j=0, k=0;
		ofstream f("File.txt");
		for (int i = 0; i < nrLocuri; i++) {
			if (locuriOcupate[i] == 0) {
				k++;
			}
			else j++;
		}
		int* locurilibere = new int[k];
		int* locuriocup = new int[j];
		f << "Locuri libere:";
		for (int i = 0; i < nrLocuri; i++) {
			if (locuriOcupate[i] != 0) {
				locurilibere[i] = locuriOcupate[i];
				f << i<<",";
			}
		}
		f << endl;
		f << "locuri ocupate:";
		for (int i = 0; i < nrLocuri; i++) {
			if (locuriOcupate[i] == 0) {
             f << i << ",";
			}
			
		}

		f.close();

	}

	friend ostream& operator<< (ostream& out, VagonPasageri& v);
};

class GarnituraTren {
private:
	string numeTren;
	int nrVagoane;
	VagonPasageri* vg;
public:
	GarnituraTren(string nume,int vagoane,VagonPasageri* v) {
		numeTren = nume;
		nrVagoane = vagoane;
		if (vagoane >= 0) {
			vg = new VagonPasageri[vagoane];
			for (int i = 0; i < nrVagoane; i++) {
				vg[i] = v[i];
			}
		}
		else vg = nullptr;
	}

	GarnituraTren(const GarnituraTren& g) {
		numeTren = g.numeTren;
		nrVagoane = g.nrVagoane;
		
			vg = new VagonPasageri[g.nrVagoane];
			for (int i = 0; i < g.nrVagoane; i++) {
				vg[i] = g.vg[i];
			}
		
	}

	~GarnituraTren() {
		if (vg != nullptr) {
			delete[]vg;
			vg = nullptr;
		}
	}

	GarnituraTren& operator=(const GarnituraTren& g) {
		if (&g != this) {
			if (vg != nullptr) {
				delete[]vg;
				vg = nullptr;
			}
			numeTren = g.numeTren;
			nrVagoane = g.nrVagoane;

			vg = new VagonPasageri[g.nrVagoane];
			for (int i = 0; i < g.nrVagoane; i++) {
				vg[i] = g.vg[i];
			}
		}
		return *this;
	}

	void operator+= (VagonPasageri t) {
		VagonPasageri* copie = new VagonPasageri[nrVagoane + 1];
		for (int i = 0; i < nrVagoane; i++) {
			copie[i] = vg[i];
		}
		copie[nrVagoane] = t;
		delete[]vg;
		vg = copie;
	}

	float totalINcasari(float pretBazaBilet) {
		float sum = 0;
		//VagonPasageri* v = new VagonPasageri();
		for (int j = 0; j < nrVagoane; j++) {
		int nrLocuri = vg[j].getNrLocuri();
		int* locuri = new int[nrLocuri];
		locuri = vg[j].getlocuriOcupate();
		
			for (int i = 0; i < nrLocuri; i++) {
				if (locuri[i] != 0) {
					switch (vg[j].getTip()) {
					case 0:
						sum = sum + pretBazaBilet;
						break;
					case 1:
						sum = sum + pretBazaBilet * 1.5;
						break;
					case 2:
						sum = sum + pretBazaBilet * 2;
						break;
					}
				}
			}
		}
		return sum;
	}
};

ostream& operator<< (ostream& out, VagonPasageri& v) {
	cout << "Cod:";
	out << v.codVagon << endl;
	cout << "tip:";
	out << v.tip << endl;
	cout << "Nr locuri:";
	out << v.nrLocuri << endl;

	for (int i = 0; i < v.nrLocuri; i++) {
		out << v.locuriOcupate[i] << endl;
	}

	cout << "Este Ocupat? ";
	out << v.esteOcupat << endl;
	
	return out;

}

int VagonPasageri::NR_MAXIM_LOCURI = 250;

int main() {
	clasa v = I;
	
	int* arry = new int[3];
	arry[0] = 1; arry[1] = 0; arry[2] = 1;
	VagonPasageri v1("Tren2",v,3,arry);
	clasa t = II;
	VagonPasageri v2("Tren", t, 3, arry);
	
	VagonPasageri* arr = new VagonPasageri[2];
	arr[0] = v1; arr[1] = v2;
	GarnituraTren gt("Express",2,arr);

	cout << gt.totalINcasari(50.2) << endl;
	v1.Raport();


   /* cout << (float)v1 << endl;
	cout << v1[0] << endl;*/

    
}