#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <direct.h>
using namespace std;

class Exceptie {
	string mesajExceptie;
public:
	Exceptie(string mesaj) {
		this->mesajExceptie = mesaj;
	}
	string getMesajExceptie() {
		return this->mesajExceptie;
	}
};

unsigned nrComenziSelect = 0;
unsigned nrComenziDisplay = 0;
string upper(const string&);
//Coduri:
//0 - nu s-a introdus nicio comanda
//1 - CREATE TABLE
//2 - DROP TABLE
//3 - DISPLAY TABLE
//4 - INSERT INTO
//5 - SELECT
//6 - UPDATE
//7 - DELETE FROM
//8 - IMPORT
int tipComanda(string comanda) {
	string cuvinte[2];
	char* copie_comanda = new char[comanda.length() + 1];
	strcpy_s(copie_comanda, comanda.length() + 1, comanda.c_str());
	cuvinte[0] = strtok(copie_comanda, " ");
	cuvinte[1] = strtok(NULL, " ");
	if (upper(cuvinte[0]) == "CREATE") {
		if (upper(cuvinte[1]) == "TABLE") {
			return 1;
		}
	}
	if (upper(cuvinte[0]) == "DROP") {
		if (upper(cuvinte[1]) == "TABLE") {
			return 2;
		}
	}
	if (upper(cuvinte[0]) == "DISPLAY") {
		if (upper(cuvinte[1]) == "TABLE") {
			return 3;
		}
	}
	if (upper(cuvinte[0]) == "INSERT") {
		if (upper(cuvinte[1]) == "INTO") {
			return 4;
		}
	}
	if (upper(cuvinte[0]) == "SELECT") {
		return 5;
	}
	if (upper(cuvinte[0]) == "UPDATE") {
		return 6;
	}
	if (upper(cuvinte[0]) == "DELETE") {
		if (upper(cuvinte[1]) == "FROM") {
			return 7;
		}
	}
	if (upper(cuvinte[0]) == "IMPORT") {
		return 8;
	}
	return 0;
}
string* impartireInCuvinte(string comandaIntreaga) {
	char* comandaIntreagaChar = new char[comandaIntreaga.length() + 1];
	for (int i = 0; i < comandaIntreaga.length() + 1; i++) {
		comandaIntreagaChar[i] = comandaIntreaga.c_str()[i];
	}
	char* copieComandaIntreaga = new char[comandaIntreaga.length() + 1];
	for (int i = 0; i < comandaIntreaga.length() + 1; i++) {
		copieComandaIntreaga[i] = comandaIntreagaChar[i];
	}
	char* aux;
	int k = 0;
	aux = strtok(copieComandaIntreaga, " ");
	while (aux != NULL) {
		k++;
		aux = strtok(NULL, " ");
	}
	string* vector_cuvinte = new string[k];
	vector_cuvinte[0] = strtok(comandaIntreagaChar, " ");
	for (int i = 1; i < k; i++) {
		vector_cuvinte[i] = strtok(NULL, " ");
	}
	return vector_cuvinte;
}
string* impartireInCuvinteDupaVirgula(string comandaIntreaga) {
	char* comandaIntreagaChar = new char[comandaIntreaga.length() + 1];
	for (int i = 0; i < comandaIntreaga.length() + 1; i++) {
		comandaIntreagaChar[i] = comandaIntreaga.c_str()[i];
	}
	char* copieComandaIntreaga = new char[comandaIntreaga.length() + 1];
	for (int i = 0; i < comandaIntreaga.length() + 1; i++) {
		copieComandaIntreaga[i] = comandaIntreagaChar[i];
	}
	char* aux;
	int k = 0;
	aux = strtok(copieComandaIntreaga, ",");
	while (aux != NULL) {
		k++;
		aux = strtok(NULL, " ");
	}
	string* vector_cuvinte = new string[k];
	vector_cuvinte[0] = strtok(comandaIntreagaChar, ",");
	for (int i = 1; i < k; i++) {
		vector_cuvinte[i] = strtok(NULL, " ");
	}
	return vector_cuvinte;
}
int nrCuvinteComanda(string comandaIntreaga) {
	char* comandaIntreagaChar = new char[comandaIntreaga.length() + 1];
	strcpy_s(comandaIntreagaChar, comandaIntreaga.length() + 1, comandaIntreaga.c_str());
	char* auxiliar;
	int nrCuvinte = 0;
	auxiliar = strtok(comandaIntreagaChar, " ");
	while (auxiliar != NULL) {
		nrCuvinte++;
		auxiliar = strtok(NULL, " ");
	}
	return nrCuvinte;
}
int nrCuvinteComandaVirgula(string comandaIntreaga) {
	char* comandaIntreagaChar = new char[comandaIntreaga.length() + 1];
	strcpy_s(comandaIntreagaChar, comandaIntreaga.length() + 1, comandaIntreaga.c_str());
	char* auxiliar;
	int nrCuvinte = 0;
	auxiliar = strtok(comandaIntreagaChar, ",");
	while (auxiliar != NULL) {
		nrCuvinte++;
		auxiliar = strtok(NULL, ",");
	}
	return nrCuvinte;
}
bool esteInteger(const string& sir) {
	if (sir.empty() || ((!isdigit(sir[0])) && (sir[0] != '-') && (sir[0] != '+'))) {
		return false;
	}
	for (int i = 1; i < sir.length(); i++) {
		if (!isdigit(sir[i])) {
			return false;
		}
	}
	return true;
}
bool esteFloat(const string& sir) {
	string::const_iterator it = sir.begin();
	bool areZecimala = false;
	int dimMin = 0;
	if (sir.size() > 0 && (sir[0] == '-' || sir[0] == '+')) {
		it++;
		dimMin++;
	}
	while (it != sir.end()) {
		if (*it == '.') {
			if (!areZecimala) {
				areZecimala = true;
			}
			else {
				break;
			}
		}
		else {
			if ((!isdigit(*it)) && ((*it != 'f') || (it + 1 != sir.end()) || (!areZecimala))) {
				break;
			}
		}
		it++;
	}
	if ((sir.size() > dimMin) && (it == sir.end())) {
		return true;
	}
	else {
		return false;
	}
}
string upper(const string& sir) {
	int i = 0;
	string sirMajuscule = "";
	while (sir[i]) {
		sirMajuscule += toupper(sir[i++]);
	}
	return sirMajuscule;
}
string elimina_0_uri(string& sir) {
	while (sir[sir.length() - 1] == '0') {
		sir.erase(sir.end() - 1, sir.end());
	}
	return sir;
}
void print(ofstream& f, const string str, const int latime) {
	if (f.is_open()) {
		f << fixed << left;
		f.fill(' ');
		f.width(latime);
		f << str << " | ";
	}
	else {
		throw Exceptie("Eroare la deschiderea fisierului.");
	}
}
void printCenter(ofstream& f, const string str, const int latime) {
	if (f.is_open()) {
		int padding = latime - str.size();
		int i = 0;
		for (; i < padding / 2; i++) {
			f << " ";
		}
		f << str;
		for (i = 0; i < padding / 2; i++) {
			f << " ";
		}
		if (padding > 0 && padding % 2 != 0) {
			f << " ";
		}
		f << " | ";
	}
	else {
		throw Exceptie("Eroare la deschiderea fisierului.");
	}
}
void modificaNumarInregistrariFisierDate(string numeTabel, int nrColoane, int nrInregistrari)
{
	numeTabel += "_date.txt";
	ifstream in(numeTabel);
	string buffer = "";
	unsigned i = 0;
	for (; i < nrColoane + 1; i++)
	{
		getline(in, buffer);
	}
	streampos pos = in.tellg();
	getline(in, buffer);
	fstream io(numeTabel, ios::in | ios::out);
	io.seekp(pos);
	io << nrInregistrari;
	for (i = 0; i < nrInregistrari; i++)
	{
		getline(in, buffer);
		io << endl << buffer;
	}
	io.close();
	in.close();
}

template <class T>
T** transpusa(T** matrice, unsigned nrLinii, unsigned nrColoane)
{
	T** copie = new T * [nrColoane];
	for (unsigned i = 0; i < nrColoane; i++)
	{
		copie[i] = new T[nrLinii];
	}
	for (unsigned i = 0; i < nrColoane; ++i)
	{
		for (unsigned j = 0; j < nrLinii; ++j)
		{
			copie[i][j] = matrice[j][i];
		}
	}
	return copie;
}

enum TipDataColoana
{
	Text, Integer, Float
};

class Coloana {
private:
	string numeColoana;
	TipDataColoana tip;
	float dimensiune;
	string valoareImplicita;
	int nrInregistrari;
	string* dateColoana;
public:
	Coloana() {
		this->numeColoana = "";
		this->tip = Text;
		this->dimensiune = 0;
		this->valoareImplicita = "";
		this->nrInregistrari = 0;
		this->dateColoana = nullptr;
	}
	Coloana(string numeColoana, TipDataColoana tip, float dimensiune, string valoareImplicita, int nrInregistrari, string* dateColoana) {
		if (numeColoana.length() > 0) {
			this->numeColoana = numeColoana;
		}
		else {
			throw Exceptie("Nume coloana invalid");
		}
		this->tip = tip;
		if (dimensiune > 0.0) {
			this->dimensiune = dimensiune;
		}
		else {
			throw Exceptie("Dimensiune invalida");
		}
		if (valoareImplicita.length() > 0) {
			this->valoareImplicita = valoareImplicita;
		}
		else {
			throw Exceptie("Valoare implicita invalida");
		}
		if (nrInregistrari > 0) {
			this->nrInregistrari = nrInregistrari;
			if (dateColoana != nullptr) {
				this->dateColoana = new string[nrInregistrari];
				for (int i = 0; i < nrInregistrari; i++) {
					if (dateColoana[i] != "") {
						this->dateColoana[i] = dateColoana[i];
					}
					else {
						this->dateColoana[i] = this->valoareImplicita;
					}
				}
			}
			else {
				throw Exceptie("Date coloane invalide");
			}
		}
		else {
			throw Exceptie("Numar inregistrari invalid");
		}
	}
	Coloana(string numeColoana, TipDataColoana tip, float dimensiune, string valoareImplicita) {
		if (numeColoana.length() > 0) {
			this->numeColoana = numeColoana;
		}
		else {
			throw Exceptie("Nume coloana invalid");
		}
		this->tip = tip;
		if (dimensiune > 0.0) {
			this->dimensiune = dimensiune;
		}
		else {
			throw Exceptie("Dimensiune invalida");
		}
		if (valoareImplicita.length() > 0) {
			this->valoareImplicita = valoareImplicita;
		}
		else {
			throw Exceptie("Valoare implicita invalida");
		}
		this->nrInregistrari = 0;
		this->dateColoana = nullptr;
	}
	~Coloana() {
		if (this->dateColoana != nullptr) {
			delete[]this->dateColoana;
			this->dateColoana = nullptr;
		}
	}
	Coloana(const Coloana& coloana) {
		this->numeColoana = coloana.numeColoana;
		this->tip = coloana.tip;
		this->dimensiune = coloana.dimensiune;
		this->valoareImplicita = coloana.valoareImplicita;
		this->nrInregistrari = coloana.nrInregistrari;
		if (coloana.dateColoana != nullptr) {
			this->dateColoana = new string[coloana.nrInregistrari];
			for (int i = 0; i < coloana.nrInregistrari; i++) {
				this->dateColoana[i] = coloana.dateColoana[i];
			}
		}
		else {
			this->dateColoana = nullptr;
		}
	}
	const Coloana& operator=(const Coloana& coloana) {
		this->numeColoana = coloana.numeColoana;
		this->tip = coloana.tip;
		this->dimensiune = coloana.dimensiune;
		this->valoareImplicita = coloana.valoareImplicita;
		this->nrInregistrari = coloana.nrInregistrari;
		if (this->dateColoana != nullptr) {
			delete[]this->dateColoana;
		}
		if (coloana.dateColoana != nullptr) {
			if (this->dateColoana != nullptr) {
				delete[]this->dateColoana;
			}
			this->dateColoana = new string[coloana.nrInregistrari];
			for (int i = 0; i < coloana.nrInregistrari; i++) {
				this->dateColoana[i] = coloana.dateColoana[i];
			}
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Coloana& coloana) {
		out << coloana.numeColoana << " ";
		out << coloana.tip << " ";
		out << coloana.dimensiune << " ";
		out << coloana.valoareImplicita << " ";
		out << coloana.nrInregistrari << " ";
		for (int i = 0; i < coloana.nrInregistrari; i++) {
			out << coloana.dateColoana[i] << " ";
		}
		out << endl;
		return out;
	}
	friend istream& operator>>(istream&, Coloana&);
	string& operator[](int index) const {
		if (index >= 0 && index < this->nrInregistrari) {
			return this->dateColoana[index];
		}
		else {
			throw Exceptie("Index invalid");
		}
	}
	friend float operator+(const Coloana& c1, const Coloana& c2) {
		float dimensiune = 0.0;
		dimensiune += (c1.dimensiune + c2.dimensiune);
		return dimensiune;
	}
	Coloana operator++() {
		this->dimensiune++;
		return *this;
	}
	Coloana operator++(int i) {
		Coloana copie = *this;
		this->dimensiune++;
		return copie;
	}
	explicit operator int() {
		return this->nrInregistrari;
	}
	void afisareColoana() {
		cout << this->numeColoana << endl;
		for (int i = 0; i < this->nrInregistrari; i++) {
			cout << this->dateColoana[i] << " ";
		}
		cout << endl;
	}
	string getNumeColoana() {
		return this->numeColoana;
	}
	TipDataColoana getTip() {
		return this->tip;
	}
	float getDimensiune() {
		return this->dimensiune;
	}
	string getValoareImplicita() {
		return this->valoareImplicita;
	}
	int getNrInregistrari() {
		return this->nrInregistrari;
	}
	string* getDateColoana() {
		return this->dateColoana;
	}
	string getDataColoana(int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrInregistrari) {
			return this->dateColoana[pozitie];
		}
	}
	void setNumeColoana(string numeColoana) {
		if (numeColoana.length() > 0) {
			this->numeColoana = numeColoana;
		}
		else {
			throw Exceptie("Nume coloana invalid");
		}
	}
	void setTip(TipDataColoana tip)
	{
		this->tip = tip;
	}
	void setDimensiune(float dimensiune) {
		if (dimensiune > 0) {
			this->dimensiune = dimensiune;
		}
		else {
			throw Exceptie("Dimensiune invalida");
		}
	}
	void setValoareImplicita(string valoareImplicita) {
		if (valoareImplicita.length() > 0) {
			this->valoareImplicita = valoareImplicita;
		}
		else {
			throw Exceptie("Valoare implicita invalida");
		}
	}
	void setDateColoana(int nrInregistrari, string* dateColoana) {
		if (nrInregistrari >= 0) {
			this->nrInregistrari = nrInregistrari;
			if (this->dateColoana != nullptr) {
				delete[]this->dateColoana;
			}
			this->dateColoana = new string[nrInregistrari];
			for (int i = 0; i < nrInregistrari; i++) {
				if (dateColoana[i] != "") {
					this->dateColoana[i] = dateColoana[i];
				}
				else {
					this->dateColoana[i] = this->valoareImplicita;
				}
			}
		}
		else {
			this->nrInregistrari = 0;
			this->dateColoana = nullptr;
			throw Exceptie("Numar inregistrari invalid");
		}
	}
};
istream& operator>>(istream& in, Coloana& c) {
	getline(in, c.numeColoana);
	if (c.numeColoana.length() == 0) {
		throw Exceptie("Nume coloana invalid");
	}
	int cod = 0;
	in >> cod;
	switch (cod)
	{
	case 0: c.tip = Text; break;
	case 1: c.tip = Integer; break;
	case 2: c.tip = Float; break;
	default:
		break;
	}
	in >> c.dimensiune;
	if (c.dimensiune <= 0) {
		throw Exceptie("Dimensiune invalida");
	}
	in >> ws;
	getline(in, c.valoareImplicita);
	if (c.tip == Text) {
		if (c.valoareImplicita.length() == 0 || (c.valoareImplicita.length() > (int)c.dimensiune)) {
			throw Exceptie("Dimensiune valoare implicita invalida");
		}
	}
	if (c.tip == Integer) {
		if (!esteInteger(c.valoareImplicita)) {
			throw Exceptie("Valoare implicita invalida");
		}
		else {
			int dim = floor(c.dimensiune);
			int length = c.valoareImplicita.length();
			if (length > dim) {
				throw Exceptie("Dimensiune valoare implicita depasita");
			}
		}
	}
	if (c.tip == Float) {
		if (!esteFloat(c.valoareImplicita)) {
			throw Exceptie("Valoare implicita invalida");
		}
		else {
			int nrCifre = floor(c.dimensiune);
			string copieDimensiune = to_string(c.dimensiune);
			int n = copieDimensiune.find(".");
			copieDimensiune.erase(copieDimensiune.begin(), copieDimensiune.begin() + n + 1);
			while (copieDimensiune[copieDimensiune.length() - 1] == '0') {
				copieDimensiune.erase(copieDimensiune.end() - 1, copieDimensiune.end());
			}
			int nrZecimale = stoi(copieDimensiune);
			if (nrCifre <= nrZecimale) {
				throw Exceptie("Dimensiune valoare implicita depasita");
			}
			if (c.valoareImplicita.find(".") != -1) {
				if (c.valoareImplicita.length() > nrCifre + 1) {
					throw Exceptie("Dimensiune valoare implicita depasita");
				}
				string copieValoareImplicita(c.valoareImplicita);
				n = copieValoareImplicita.find(".");
				copieValoareImplicita.erase(copieValoareImplicita.begin(), copieValoareImplicita.begin() + n + 1);
				if (copieValoareImplicita.length() > nrZecimale) {
					throw Exceptie("Dimensiune valoare implicita depasita");
				}
			}
			else {
				if (c.valoareImplicita.length() > nrCifre) {
					throw Exceptie("Dimensiune valoare implicita depasita");
				}
			}
		}
	}
	in >> c.nrInregistrari;
	if (c.nrInregistrari < 0) {
		throw Exceptie("Numar inregistrari invalid");
	}
	else {
		if (c.dateColoana != nullptr) {
			delete[]c.dateColoana;
		}
		if (c.nrInregistrari == 0) {
			c.dateColoana = nullptr;
		}
		else {
			c.dateColoana = new string[c.nrInregistrari];
			for (int i = 0; i < c.nrInregistrari; i++) {
				in >> c.dateColoana[i];
				if (c.dateColoana[i].length() == 0) {
					throw Exceptie("Data coloana invalida");
				}
			}
		}
	}
	return in;
}

class Tabel {
private:
	string denumireTabel;
	int nrColoane;
	Coloana* coloaneTabel;
	static int nrTabele;
	static string numeTabele[100];
	friend class Comanda;
public:
	Tabel() {
		this->denumireTabel = "";
		this->nrColoane = 0;
		this->coloaneTabel = nullptr;
		nrTabele++;
		numeTabele[nrTabele - 1] = "";
	}
	Tabel(string denumireTabel, int nrColoane, const Coloana* coloaneTabel) {
		if (denumireTabel.length() > 0) {
			this->denumireTabel = denumireTabel;
		}
		else {
			throw Exceptie("Denumire tabel invalida");
		}
		if (nrColoane > 0) {
			this->nrColoane = nrColoane;
			if (coloaneTabel != nullptr) {
				this->coloaneTabel = new Coloana[nrColoane];
				for (int i = 0; i < nrColoane; i++) {
					this->coloaneTabel[i] = coloaneTabel[i];
				}
			}
			else {
				throw Exceptie("Coloane invalide");
			}
		}
		else {
			throw Exceptie("Numar coloane invalid");
		}
		nrTabele++;
		numeTabele[nrTabele - 1] = this->denumireTabel;
	}
	~Tabel() {
		if (this->coloaneTabel != nullptr) {
			delete[]this->coloaneTabel;
			this->coloaneTabel = nullptr;
		}
		nrTabele--;
	}
	Tabel(const Tabel& tabel) {
		this->denumireTabel = tabel.denumireTabel;
		this->nrColoane = tabel.nrColoane;
		if (tabel.nrColoane > 0) {
			this->coloaneTabel = new Coloana[tabel.nrColoane];
			for (int i = 0; i < tabel.nrColoane; i++) {
				this->coloaneTabel[i] = tabel.coloaneTabel[i];
			}
		}
		else {
			this->coloaneTabel = nullptr;
		}
		nrTabele++;
		numeTabele[nrTabele - 1] = tabel.denumireTabel;
	}
	const Tabel& operator=(const Tabel& tabel) {
		this->denumireTabel = tabel.denumireTabel;
		this->nrColoane = tabel.nrColoane;
		if (this->coloaneTabel != nullptr) {
			delete[]this->coloaneTabel;
		}
		if (tabel.nrColoane > 0) {
			this->coloaneTabel = new Coloana[tabel.nrColoane];
			for (int i = 0; i < tabel.nrColoane; i++) {
				this->coloaneTabel[i] = tabel.coloaneTabel[i];
			}
		}
		else {
			this->coloaneTabel = nullptr;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Tabel& tabel) {
		out << tabel.denumireTabel << " ";
		out << tabel.nrColoane << endl;
		for (int i = 0; i < tabel.nrColoane; i++) {
			out << tabel.coloaneTabel[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Tabel& t) {
		in >> t.denumireTabel;
		if (t.denumireTabel.length() == 0) {
			throw Exceptie("Denumire tabel invalida");
		}
		in >> t.nrColoane;
		if (t.nrColoane <= 0) {
			throw Exceptie("Numar coloane invalid");
		}
		else {
			if (t.coloaneTabel != nullptr) {
				delete[]t.coloaneTabel;
			}
			t.coloaneTabel = new Coloana[t.nrColoane];
			for (int i = 0; i < t.nrColoane; i++) {
				in >> ws;
				in >> t.coloaneTabel[i];
			}
		}
		return in;
	}
	Coloana& operator[](int index) const {
		if (index >= 0 && index < this->nrColoane) {
			return this->coloaneTabel[index];
		}
		else {
			throw Exceptie("Index invalid");
		}
	}
	operator int() {
		return this->nrColoane;
	}
	friend bool operator<=(const Tabel& t1, const Tabel& t2) {
		return t1.nrColoane <= t2.nrColoane;
	}
	void afisareNumeTabele() {
		for (int i = 0; i < nrTabele; i++) {
			cout << numeTabele[i] << " ";
		}
	}
	string getDenumireTabel() {
		return this->denumireTabel;
	}
	int getNrColoane() {
		return this->nrColoane;
	}
	const Coloana* getColoaneTabel() {
		return this->coloaneTabel;
	}
	Coloana getColoanaTabel(int index) {
		if (index >= 0 || index < this->nrColoane) {
			return this->coloaneTabel[index];
		}
		else {
			throw Exceptie("Index coloana invalid");
		}
	}
	int getNrTabele() {
		return nrTabele;
	}
	string* getNumeTabele() {
		return numeTabele;
	}
	string getNumeTabel(int index) {
		if (index >= 0 || index < nrTabele) {
			return numeTabele[index];
		}
		else {
			throw Exceptie("Index coloana invalid");
		}
	}
	void setDenumireTabel(string denumireTabel) {
		if (denumireTabel.length() > 0) {
			this->denumireTabel = denumireTabel;
		}
		else {
			throw Exceptie("Denumire tabel invalida");
		}
	}
	void setColoaneTabel(int nrColoane, Coloana* coloaneTabel) {
		if (nrColoane >= 0) {
			this->nrColoane = nrColoane;
			if (this->coloaneTabel != nullptr) {
				delete[]this->coloaneTabel;
			}
			this->coloaneTabel = new Coloana[nrColoane];
			for (int i = 0; i < nrColoane; i++) {
				this->coloaneTabel[i] = coloaneTabel[i];
			}
		}
		else {
			this->nrColoane = 0;
			this->coloaneTabel = nullptr;
			throw Exceptie("Numar coloane invalid");
		}
	}
	void DISPLAY_TABLE() {
		cout << this->denumireTabel << endl;
		cout << this->nrColoane << endl;
		for (int i = 0; i < this->nrColoane; i++) {
			cout << this->coloaneTabel[i];
		}
		cout << endl;
	}
};
int Tabel::nrTabele = 0;
string Tabel::numeTabele[] = {};

class Comanda {
private:
	string comandaIntreaga;
	bool esteValidata = false;
	static string istoricComenzi[1000];
	static int nrComanda;
	//friend class Tabel;
public:
	Comanda() {
		this->comandaIntreaga = "";
		istoricComenzi[nrComanda] = "";
		nrComanda++;
	}
	Comanda(string comandaIntreaga) {
		if (comandaIntreaga.length() <= 0) {
			throw Exceptie("Comanda invalida");
		}
		else {
			this->comandaIntreaga = comandaIntreaga;
			istoricComenzi[nrComanda] = comandaIntreaga;
			nrComanda++;
		}
	}
	~Comanda() {

	}
	Comanda(const Comanda& c) {
		this->comandaIntreaga = c.comandaIntreaga;
		istoricComenzi[nrComanda] = c.comandaIntreaga;
		nrComanda++;
	}
	const Comanda& operator=(const Comanda& c) {
		this->comandaIntreaga = c.comandaIntreaga;
	}
	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << c.comandaIntreaga << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Comanda& c) {
		getline(in, c.comandaIntreaga);
		if (c.comandaIntreaga.length() == 0) {
			throw Exceptie("Comanda invalida");
		}
		return in;
	}
	bool operator!() {
		return !(esteValidata);
	}
	bool operator==(const Comanda& comanda) {
		return this->comandaIntreaga == comanda.comandaIntreaga;
	}
	string getComandaIntreaga() {
		return this->comandaIntreaga;
	}
	bool getEsteValidata() {
		return this->esteValidata;
	}
	void setComandaIntreaga(string comanda) {
		if (comanda.length() > 0) {
			this->comandaIntreaga = comanda;
		}
		else {
			throw Exceptie("Comanda invalida");
		}
	}
	void setEsteValidata(bool stare) {
		this->esteValidata = stare;
	}
	bool validareDisplayTable() {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(comandaIntreaga);
		if (nrCuvinte != 3) {
			throw Exceptie("Format invalid");
		}
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "DISPLAY" || upper(cuvinteComanda[1]) != "TABLE" || cuvinteComanda[2] == "") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[2] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		return true;
	}
	bool validareDropTable() {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(comandaIntreaga);
		if (nrCuvinte != 3) {
			throw Exceptie("Format invalid");
		}
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "DROP" || upper(cuvinteComanda[1]) != "TABLE" || cuvinteComanda[2] == "") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[2] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		return true;
	}
	bool validareCreateTable() {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(this->comandaIntreaga);
		if (nrCuvinte != 4) {
			throw Exceptie("Format invalid");
		}
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(this->comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "CREATE" || upper(cuvinteComanda[1]) != "TABLE" || cuvinteComanda[2] == "" || cuvinteComanda[3] == "") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[2] + ".txt").c_str());
		if (ifile)
		{
			ifile.close();
			throw Exceptie("Tabel existent");
		}
		int nrParantezeDeschise = 0;
		int nrParantezeInchise = 0;
		for (int i = 0; i < cuvinteComanda[3].length(); i++) {
			if (cuvinteComanda[3][i] == '(') {
				nrParantezeDeschise++;
			}
			if (cuvinteComanda[3][i] == ')') {
				nrParantezeInchise++;
			}
		}
		if (nrParantezeDeschise != nrParantezeInchise) {
			throw Exceptie("Format invalid");
		}
		if (cuvinteComanda[3][0] != '(' || cuvinteComanda[3][cuvinteComanda[3].length() - 1] != ')') {
			throw Exceptie("Format invalid");
		}
		for (int i = 1; i < cuvinteComanda[3].length() - 2; i++) {
			if (cuvinteComanda[3][i] == ')') {
				if (cuvinteComanda[3][i + 1] != ',' && cuvinteComanda[3][i + 2] != '(' && i != cuvinteComanda[3].length() - 3) {
					throw Exceptie("Format invalid");
				}
			}
		}
		string input(cuvinteComanda[3]);
		string delimitator = "),(";
		input.erase(input.begin(), input.begin() + 2);
		input.erase(input.end() - 2, input.end());
		int n = input.find(delimitator);
		string numeColoane[10] = {};
		int nrColoane = 0;
		while (n != -1) {
			string coloana(input);
			coloana.erase(coloana.begin() + n, coloana.end());
			if (nrCuvinteComandaVirgula(coloana) != 4) {
				throw Exceptie("Format invalid");
			}
			char* coloanaChar = new char[coloana.length() + 1];
			strcpy_s(coloanaChar, coloana.length() + 1, coloana.c_str());
			string campColoana[4];
			campColoana[0] = strtok(coloanaChar, ",");
			numeColoane[nrColoane++] = campColoana[0];
			campColoana[1] = strtok(NULL, ",");
			campColoana[2] = strtok(NULL, ",");
			campColoana[3] = strtok(NULL, ",");
			if (campColoana[0].length() == 0) {
				throw Exceptie("Nume coloana invalid");
			}
			if (campColoana[1] != "Text" && campColoana[1] != "Integer" && campColoana[1] != "Float") {
				throw Exceptie("Tip data invalid");
			}
			if (!esteFloat(campColoana[2])) {
				throw Exceptie("Dimensiune invalida");
			}
			else {
				if (stof(campColoana[2]) <= 0) {
					throw Exceptie("Dimensiune invalida");
				}
			}
			if (campColoana[1] == "Text") {
				if (campColoana[3].length() == 0 || (campColoana[3].length() > stoi(campColoana[2]))) {
					throw Exceptie("Dimensiune valoare implicita invalida");
				}
			}
			if (campColoana[1] == "Integer") {
				if (!esteInteger(campColoana[3])) {
					throw Exceptie("Valoare implicita invalida");
				}
				else {
					int dim = floor(stof(campColoana[2]));
					int length = campColoana[3].length();
					if (length > dim) {
						throw Exceptie("Dimensiune valoare implicita depasita");
					}
				}
			}
			if (campColoana[1] == "Float") {
				if (!esteFloat(campColoana[3])) {
					throw Exceptie("Valoare implicita invalida");
				}
				else {
					string copieDimensiune = campColoana[2];
					int nrCifre = floor(stof(copieDimensiune));
					int n = copieDimensiune.find(".");
					copieDimensiune.erase(copieDimensiune.begin(), copieDimensiune.begin() + n + 1);
					int nrZecimale = stoi(copieDimensiune);
					if (nrCifre <= nrZecimale) {
						throw Exceptie("Dimensiune valoare implicita depasita");
					}
					if (campColoana[3].find(".") != -1) {
						if (campColoana[3].length() > nrCifre + 1) {
							throw Exceptie("Dimensiune valoare implicita depasita");
						}
						string copieValoareImplicita(campColoana[3]);
						n = copieValoareImplicita.find(".");
						copieValoareImplicita.erase(copieValoareImplicita.begin(), copieValoareImplicita.begin() + n + 1);
						if (copieValoareImplicita.length() > nrZecimale) {
							throw Exceptie("Dimensiune valoare implicita depasita");
						}
					}
					else {
						if (campColoana[3].length() > nrCifre) {
							throw Exceptie("Dimensiune valoare implicita depasita");
						}
					}
				}
			}
			input.erase(input.begin(), input.begin() + n + delimitator.length());
			n = input.find(delimitator);
		}
		if (nrCuvinteComandaVirgula(input) != 4) {
			throw Exceptie("Format invalid");
		}
		char* coloanaChar = new char[input.length() + 1];
		strcpy_s(coloanaChar, input.length() + 1, input.c_str());
		string campColoana[4];
		campColoana[0] = strtok(coloanaChar, ",");
		numeColoane[nrColoane++] = campColoana[0];
		campColoana[1] = strtok(NULL, ",");
		campColoana[2] = strtok(NULL, ",");
		campColoana[3] = strtok(NULL, ",");
		if (campColoana[0].length() == 0) {
			throw Exceptie("Nume coloana invalid");
		}
		if (campColoana[1] != "Text" && campColoana[1] != "Integer" && campColoana[1] != "Float") {
			throw Exceptie("Tip data invalid");
		}
		if (!esteFloat(campColoana[2])) {
			throw Exceptie("Dimensiune invalida");
		}
		else {
			if (stof(campColoana[2]) <= 0) {
				throw Exceptie("Dimensiune invalida");
			}
		}
		if (campColoana[1] == "Text") {
			if (campColoana[3].length() == 0 || (campColoana[3].length() > (int)stof(campColoana[2]))) {
				throw Exceptie("Dimensiune valoare implicita invalida");
			}
		}
		if (campColoana[1] == "Integer") {
			if (!esteInteger(campColoana[3])) {
				throw Exceptie("Valoare implicita invalida");
			}
			else {
				int dim = floor(stof(campColoana[2]));
				int length = campColoana[3].length();
				if (length > dim) {
					throw Exceptie("Dimensiune valoare implicita depasita");
				}
			}
		}
		if (campColoana[1] == "Float") {
			if (!esteFloat(campColoana[3])) {
				throw Exceptie("Valoare implicita invalida");
			}
			else {
				string copieDimensiune = campColoana[2];
				int nrCifre = floor(stof(copieDimensiune));
				int n = copieDimensiune.find(".");
				copieDimensiune.erase(copieDimensiune.begin(), copieDimensiune.begin() + n + 1);
				int nrZecimale = stoi(copieDimensiune);
				if (nrCifre <= nrZecimale) {
					throw Exceptie("Dimensiune valoare implicita depasita");
				}
				if (campColoana[3].find(".") != -1) {
					if (campColoana[3].length() > nrCifre + 1) {
						throw Exceptie("Dimensiune valoare implicita depasita");
					}
					string copieValoareImplicita(campColoana[3]);
					n = copieValoareImplicita.find(".");
					copieValoareImplicita.erase(copieValoareImplicita.begin(), copieValoareImplicita.begin() + n + 1);
					if (copieValoareImplicita.length() > nrZecimale) {
						throw Exceptie("Dimensiune valoare implicita depasita");
					}
				}
				else {
					if (campColoana[3].length() > nrCifre) {
						throw Exceptie("Dimensiune valoare implicita depasita");
					}
				}
			}
		}
		for (int i = 0; i < nrColoane - 1; i++) {
			for (int j = i + 1; j < nrColoane; j++) {
				if (numeColoane[i] == numeColoane[j]) {
					throw Exceptie("Nu se permit denumiri identice de coloana");
				}
			}
		}
		return true;
	}
	bool validareDeleteFrom(Tabel t) {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(comandaIntreaga);
		if (nrCuvinte != 7) {
			throw Exceptie("Format invalid");
		}
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "DELETE" || upper(cuvinteComanda[1]) != "FROM" || cuvinteComanda[2] == "" || upper(cuvinteComanda[3]) != "WHERE" || cuvinteComanda[4] == "" || cuvinteComanda[5] != "=" || cuvinteComanda[6] == "") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[2] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		bool esteValid = false;
		for (int i = 0; i < t.nrColoane && esteValid == false; i++) {
			if (cuvinteComanda[4] == t.coloaneTabel[i].getNumeColoana()) {
				esteValid = true;
			}
		}
		if (!esteValid) {
			throw Exceptie("Coloana inexistenta");
		}
		if (cuvinteComanda[6].length() <= 0) {
			throw Exceptie("Valoare invalida");
		}
		int nrInregistrari = 0;
		int index = 0;
		for (; index < t.nrColoane; index++) {
			if (cuvinteComanda[4] == t.coloaneTabel[index].getNumeColoana()) {
				nrInregistrari = t.coloaneTabel[index].getNrInregistrari();
				break;
			}
		}
		string* dateColoana = new string[nrInregistrari];
		for (int i = 0; i < nrInregistrari; i++) {
			dateColoana[i] = t.coloaneTabel[index].getDateColoana()[i];
		}
		esteValid = false;
		for (int i = 0; i < nrInregistrari && esteValid == false; i++) {
			if (dateColoana[i] == cuvinteComanda[6]) {
				esteValid = true;
			}
		}
		if (!esteValid) {
			throw Exceptie("Valoare inexistenta");
		}
		return true;
	}
	bool validareUpdate(Tabel t) {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(this->comandaIntreaga);
		if (nrCuvinte != 10) {
			throw Exceptie("Format invalid");
		}
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(this->comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "UPDATE" || cuvinteComanda[1] == "" || upper(cuvinteComanda[2]) != "SET" || cuvinteComanda[3] == "" || cuvinteComanda[4] != "=" || cuvinteComanda[5] == "" || upper(cuvinteComanda[6]) != "WHERE" || cuvinteComanda[7] == "" || cuvinteComanda[8] != "=" || cuvinteComanda[9] == "") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[1] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		bool esteValid = false;
		for (int i = 0; i < t.nrColoane && !esteValid; i++) {
			if (cuvinteComanda[3] == t.coloaneTabel[i].getNumeColoana()) {
				esteValid = true;
			}
		}
		if (!esteValid) {
			throw Exceptie("Coloana inexistenta");
		}
		if (cuvinteComanda[5].length() <= 0) {
			throw Exceptie("Dimensiune invalida");
		}
		int nrInregistrari = 0;
		int index = 0;
		for (; index < t.nrColoane; index++) {
			if (cuvinteComanda[3] == t.coloaneTabel[index].getNumeColoana()) {
				nrInregistrari = t.coloaneTabel[index].getNrInregistrari();
				break;
			}
		}
		esteValid = false;
		if (t.coloaneTabel[index].getTip() == Integer && esteInteger(cuvinteComanda[5]) && cuvinteComanda[5].length() <= (int)t.coloaneTabel[index].getDimensiune()) {
			esteValid = true;
		}
		if (t.coloaneTabel[index].getTip() == Float && esteFloat(cuvinteComanda[5])) {
			esteValid = true;
			float dimensiune = t.coloaneTabel[index].getDimensiune();
			int nrCifre = (int)dimensiune;
			float parteFractionara = dimensiune - nrCifre;
			string stringParteFractionara = to_string(parteFractionara);
			stringParteFractionara.erase(stringParteFractionara.begin(), stringParteFractionara.begin() + 2);
			int nrZecimale = stoi(stringParteFractionara);
			if (nrZecimale != 0) {
				while (nrZecimale % 10 == 0) {
					nrZecimale /= 10;
				}
			}
			string valoare = cuvinteComanda[5];
			int nrCifreValoare = 0;
			if (valoare.find(".") != -1) {
				nrCifreValoare = valoare.length() - 1;
			}
			else {
				nrCifreValoare = valoare.length();
			}
			int nrZecimaleValoare = 0;
			int n = valoare.find(".");
			if (n != -1) {
				valoare.erase(valoare.begin(), valoare.begin() + n + 1);
				nrZecimaleValoare = valoare.length();
			}
			if ((nrCifre < nrCifreValoare) || (nrZecimale < nrZecimaleValoare)) {
				esteValid = false;
			}
		}
		if (t.coloaneTabel[index].getTip() == Text && cuvinteComanda[5].length() <= (int)t.coloaneTabel[index].getDimensiune()) {
			esteValid = true;
		}
		if (!esteValid) {
			throw Exceptie("Dimensiune invalida");
		}
		esteValid = false;
		for (int i = 0; i < t.nrColoane && esteValid == false; i++) {
			if (cuvinteComanda[7] == t.coloaneTabel[i].getNumeColoana()) {
				esteValid = true;
			}
		}
		if (!esteValid) {
			throw Exceptie("Coloana inexistenta");
		}
		if (cuvinteComanda[9].length() <= 0) {
			throw Exceptie("Format invalid");
		}
		nrInregistrari = 0;
		index = 0;
		for (; index < t.nrColoane; index++) {
			if (cuvinteComanda[7] == t.coloaneTabel[index].getNumeColoana()) {
				nrInregistrari = t.coloaneTabel[index].getNrInregistrari();
				break;
			}
		}
		string* dateColoana = new string[nrInregistrari];
		for (int i = 0; i < nrInregistrari; i++) {
			dateColoana[i] = t.coloaneTabel[index].getDateColoana()[i];
		}
		esteValid = false;
		for (int i = 0; i < nrInregistrari && esteValid == false; i++) {
			if (dateColoana[i] == cuvinteComanda[9]) {
				esteValid = true;
			}
		}
		if (!esteValid) {
			throw Exceptie("Valoare inexistenta");
		}
		return true;
	}
	bool validareInsert(Tabel t) {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(comandaIntreaga);
		if (nrCuvinte != 5) {
			throw Exceptie("Format invalid");
		}
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "INSERT" || upper(cuvinteComanda[1]) != "INTO" || cuvinteComanda[2] == "" || upper(cuvinteComanda[3]) != "VALUES" || cuvinteComanda[4] == "") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[2] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		string valori = cuvinteComanda[4];
		int nrParantezeDeschise = 0;
		int nrParantezeInchise = 0;
		for (int i = 0; i < valori.length(); i++) {
			if (valori[i] == '(') {
				nrParantezeDeschise++;
			}
			if (valori[i] == ')') {
				nrParantezeInchise++;
			}
		}
		if (nrParantezeDeschise != nrParantezeInchise) {
			throw Exceptie("Format invalid");
		}
		if (valori[0] != '(' || valori[1] == '(' || valori[valori.length() - 2] == ')' || valori[valori.length() - 1] != ')') {
			throw Exceptie("Format invalid");
		}
		valori.erase(valori.begin(), valori.begin() + 1);
		valori.erase(valori.end() - 1, valori.end());
		int nrValoriPermise = t.getNrColoane();
		int nrValoriIntroduse = nrCuvinteComandaVirgula(valori);
		if (nrValoriIntroduse != nrValoriPermise) {
			throw Exceptie("Format invalid");
		}
		char* valoriChar = new char[valori.length() + 1];
		strcpy_s(valoriChar, valori.length() + 1, valori.c_str());
		string* vectorValori = new string[nrValoriIntroduse];
		vectorValori[0] = strtok(valoriChar, ",");
		for (int i = 1; i < nrValoriIntroduse; i++) {
			vectorValori[i] = strtok(NULL, ",");
		}
		for (int i = 0; i < nrValoriIntroduse; i++) {
			switch (t.coloaneTabel[i].getTip())
			{
			case 0: {
				if (vectorValori[i].length() == 0 || vectorValori[i].length() > (int)t.coloaneTabel[i].getDimensiune()) {
					throw Exceptie("Dimensiune invalida");
				}
			}
				  break;
			case 1: {
				if (!esteInteger(vectorValori[i])) {
					throw Exceptie("Tip necorespunzator");
				}
				else {
					if (vectorValori[i].length() > (int)t.coloaneTabel[i].getDimensiune()) {
						throw Exceptie("Dimensiune invalida");
					}
				}
			}
				  break;
			case 2: {
				if (!esteFloat(vectorValori[i])) {
					throw Exceptie("Tip necorespunzator");
				}
				else {
					float dimensiune = t.coloaneTabel[i].getDimensiune();
					int nrCifre = (int)dimensiune;
					float parteFractionara = dimensiune - nrCifre;
					string stringParteFractionara = to_string(parteFractionara);
					stringParteFractionara.erase(stringParteFractionara.begin(), stringParteFractionara.begin() + 2);
					int nrZecimale = stoi(stringParteFractionara);
					if (nrZecimale != 0) {
						while (nrZecimale % 10 == 0) {
							nrZecimale /= 10;
						}
					}
					string valoare = vectorValori[i];
					int nrCifreValoare = 0;
					if (valoare.find(".") != -1) {
						nrCifreValoare = valoare.length() - 1;
					}
					else {
						nrCifreValoare = valoare.length();
					}
					int nrZecimaleValoare = 0;
					int n = valoare.find(".");
					if (n != -1) {
						valoare.erase(valoare.begin(), valoare.begin() + n + 1);
						nrZecimaleValoare = valoare.length();
					}
					if ((nrCifre < nrCifreValoare) || (nrZecimale < nrZecimaleValoare)) {
						throw Exceptie("Dimensiune invalida");
					}
				}
			}
				  break;
			default:
				throw Exceptie("Valoare invalida");
				break;
			}
		}
		return true;
	}
	bool validareSelect(Tabel t) {
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		int nrCuvinte = nrCuvinteComanda(comandaIntreaga);
		string* cuvinteComanda = new string[nrCuvinte];
		cuvinteComanda = impartireInCuvinte(comandaIntreaga);
		if (upper(cuvinteComanda[0]) != "SELECT") {
			throw Exceptie("Format invalid");
		}
		string coloaneSelectate = cuvinteComanda[1];
		if (coloaneSelectate[0] != '(' || coloaneSelectate[coloaneSelectate.length() - 1] != ')') {
			if (upper(coloaneSelectate) != "ALL") {
				throw Exceptie("Format invalid");
			}
		}
		else {
			coloaneSelectate.erase(coloaneSelectate.end() - 1, coloaneSelectate.end());
			coloaneSelectate.erase(coloaneSelectate.begin(), coloaneSelectate.begin() + 1);
			int nrColoaneSelectate = nrCuvinteComandaVirgula(coloaneSelectate);
			if (nrColoaneSelectate < 1) {
				throw Exceptie("Format invalid");
			}
			if (nrColoaneSelectate > t.getNrColoane()) {
				throw Exceptie("Format invalid");
			}
			char* numeColoaneChar = new char[coloaneSelectate.length() + 1];
			strcpy_s(numeColoaneChar, coloaneSelectate.length() + 1, coloaneSelectate.c_str());
			string* vectorColoane = new string[nrColoaneSelectate];
			vectorColoane[0] = strtok(numeColoaneChar, ",");
			for (int i = 1; i < nrColoaneSelectate; i++) {
				vectorColoane[i] = strtok(NULL, ",");
			}
			bool esteValid = false;
			for (int i = 0; i < nrColoaneSelectate && !esteValid; i++) {
				for (int j = 0; j < t.getNrColoane() && !esteValid; j++) {
					if (vectorColoane[i] == t.coloaneTabel[j].getNumeColoana()) {
						esteValid = true;
					}
				}
			}
			if (!esteValid) {
				throw Exceptie("Coloana inexistenta");
			}
		}
		if (upper(cuvinteComanda[2]) != "FROM") {
			throw Exceptie("Format invalid");
		}
		ifstream ifile;
		ifile.open((cuvinteComanda[3] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		if (nrCuvinte > 4) {
			if (upper(cuvinteComanda[4]) == "[WHERE") {
				int n = comandaIntreaga.find("[");
				comandaIntreaga.erase(comandaIntreaga.begin(), comandaIntreaga.begin() + n + sizeof("[WHERE"));
				if (comandaIntreaga[comandaIntreaga.length() - 1] != ']') {
					throw Exceptie("Format invalid");
				}
				else
				{
					comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
				}
				nrCuvinte = nrCuvinteComanda(comandaIntreaga);
				if (nrCuvinte != 3) {
					throw Exceptie("Format invalid");
				}
				if (cuvinteComanda != nullptr) {
					delete[]cuvinteComanda;
				}
				cuvinteComanda = new string[nrCuvinte];
				cuvinteComanda = impartireInCuvinte(comandaIntreaga);
				if (cuvinteComanda[0] == "" || cuvinteComanda[1] != "=" || cuvinteComanda[2] == "") {
					throw Exceptie("Format invalid");
				}
				int nrInregistrari = 0;
				int index = 0;
				for (; index < t.nrColoane && nrInregistrari == 0; index++) {
					if (cuvinteComanda[0] == t.coloaneTabel[index].getNumeColoana()) {
						nrInregistrari = t.coloaneTabel[index].getNrInregistrari();
					}
				}
				index--;
				string* dateColoana = new string[nrInregistrari];
				for (int i = 0; i < nrInregistrari; i++) {
					dateColoana[i] = t.coloaneTabel[index].getDateColoana()[i];
				}
				bool esteValid = false;
				for (int i = 0; i < nrInregistrari && esteValid == false; i++) {
					if (dateColoana[i] == cuvinteComanda[2]) {
						esteValid = true;
					}
				}
				if (!esteValid) {
					throw Exceptie("Valoare inexistenta");
				}
			}
		}
		return true;
	}
	bool validareImport(Tabel t)
	{
		if (comandaIntreaga[comandaIntreaga.length() - 1] != ';') {
			throw Exceptie("Comanda trebuie sa se termine cu ;");
		}
		while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
			comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
		}
		if (nrCuvinteComanda(this->comandaIntreaga) != 3) {
			throw Exceptie("Comanda invalida.");
		}
		string* cuvinteComanda = new string[nrCuvinteComanda(this->comandaIntreaga)];
		cuvinteComanda = impartireInCuvinte(this->comandaIntreaga);
		ifstream ifile;
		ifile.open((cuvinteComanda[1] + ".txt").c_str());
		if (!ifile)
		{
			throw Exceptie("Tabel inexistent");
		}
		string numeFisierCSV = cuvinteComanda[2];
		string extensieFisier = numeFisierCSV.substr(numeFisierCSV.length() - 4, numeFisierCSV.length() - 1);
		if (upper(extensieFisier) != ".CSV")
		{
			throw Exceptie("Format invalid.");
		}
		ifstream f(numeFisierCSV, ios::in);
		int nrInregistrari = 0;
		f >> nrInregistrari;
		f.get();
		if (nrInregistrari < 0)
		{
			throw Exceptie("Numar inregistrari invalid.");
		}
		int nrColoane = t.getNrColoane();
		string** dateFisierCSV = new string * [nrColoane];
		for (unsigned i = 0; i < nrColoane; i++)
		{
			dateFisierCSV[i] = new string[nrInregistrari];
		}

		for (unsigned i = 0; i < nrColoane; i++)
		{
			for (int j = 0; j < nrInregistrari; j++)
			{
				getline(f, dateFisierCSV[i][j], ';');
				if (f.fail())
				{
					throw Exceptie("Separator incorect.");
				}
			}
			f.get();
		}

		for (unsigned i = 0; i < nrColoane; i++)
		{
			TipDataColoana tip = t.coloaneTabel[i].getTip();
			switch (tip)
			{
			case Text: {
				for (int j = 0; j < nrInregistrari; j++) {
					if (dateFisierCSV[i][j].length() == 0 || dateFisierCSV[i][j].length() > (int)t.coloaneTabel[i].getDimensiune())
					{
						throw Exceptie("Data invalida.");
					}
				}
			}
					 break;
			case Integer: {
				for (int j = 0; j < nrInregistrari; j++) {
					if (!esteInteger(dateFisierCSV[i][j])) {
						throw Exceptie("Data invalida.");
					}
					else {
						if (dateFisierCSV[i][j].length() > (int)t.coloaneTabel[i].getDimensiune()) {
							throw Exceptie("Data invalida.");
						}
					}
				}
			}
						break;
			case Float: {
				for (int j = 0; j < nrInregistrari; j++) {
					if (!esteFloat(dateFisierCSV[i][j])) {
						throw Exceptie("Data invalida.");
					}
					else {
						float dimensiune = t.coloaneTabel[i].getDimensiune();
						int nrCifre = (int)dimensiune;
						float parteFractionara = dimensiune - nrCifre;
						string stringParteFractionara = to_string(parteFractionara);
						stringParteFractionara.erase(stringParteFractionara.begin(), stringParteFractionara.begin() + 2);
						int nrZecimale = stoi(stringParteFractionara);
						if (nrZecimale != 0) {
							while (nrZecimale % 10 == 0) {
								nrZecimale /= 10;
							}
						}
						string valoare = dateFisierCSV[i][j];
						int nrCifreValoare = 0;
						if (valoare.find(".") != -1) {
							nrCifreValoare = valoare.length() - 1;
						}
						else {
							nrCifreValoare = valoare.length();
						}
						int nrZecimaleValoare = 0;
						int n = valoare.find(".");
						if (n != -1) {
							valoare.erase(valoare.begin(), valoare.begin() + n + 1);
							nrZecimaleValoare = valoare.length();
						}
						if ((nrCifre < nrCifreValoare) || (nrZecimale < nrZecimaleValoare)) {
							throw Exceptie("Data invalida.");
						}
					}
				}
			}
					  break;
			default:
				break;
			}
		}

		f.close();
		return true;
	}
};
string Comanda::istoricComenzi[] = {};
int Comanda::nrComanda = 0;

Tabel creareTabelDinFisier(string numeTabel)
{
	ifstream f((char*)(numeTabel + "_date.txt").c_str());
	string denumireTabel = "";
	int nrColoane = 0;
	Coloana* coloaneTabel = nullptr;
	string* numeColoane = nullptr;
	TipDataColoana* tipuri = nullptr;
	float* dimensiuni = nullptr;
	string* valoriImplicite = nullptr;
	int nrInregistrari = 0;
	string** dateColoane = nullptr;

	f >> denumireTabel;
	f >> nrColoane;
	f.get();
	coloaneTabel = new Coloana[nrColoane];
	numeColoane = new string[nrColoane];
	tipuri = new TipDataColoana[nrColoane];
	dimensiuni = new float[nrColoane];
	valoriImplicite = new string[nrColoane];

	unsigned cod = 0;
	for (unsigned i = 0; i < nrColoane; i++)
	{
		f >> numeColoane[i];
		f >> cod;
		switch (cod)
		{
		case 0: tipuri[i] = Text; break;
		case 1: tipuri[i] = Integer; break;
		case 2: tipuri[i] = Float; break;
		default:
			break;
		}
		f >> dimensiuni[i];
		f >> valoriImplicite[i];
		f.get();
	}
	f >> nrInregistrari;
	f.get();
	if (nrInregistrari > 0)
	{
		dateColoane = new string * [nrColoane];
		for (unsigned i = 0; i < nrColoane; i++)
		{
			dateColoane[i] = new string[nrInregistrari];
		}
		for (unsigned i = 0; i < nrInregistrari; i++)
		{
			for (unsigned j = 0; j < nrColoane; j++)
			{
				f >> dateColoane[j][i];
			}
			f.get();
		}

		for (unsigned i = 0; i < nrColoane; i++)
		{
			coloaneTabel[i] = *new Coloana(numeColoane[i], tipuri[i], dimensiuni[i], valoriImplicite[i], nrInregistrari, dateColoane[i]);
		}
	}
	else
	{
		for (unsigned i = 0; i < nrColoane; i++)
		{
			coloaneTabel[i] = *new Coloana(numeColoane[i], tipuri[i], dimensiuni[i], valoriImplicite[i]);
		}
	}

	Tabel tabel(denumireTabel, nrColoane, coloaneTabel);

	if (dateColoane != nullptr)
	{
		for (unsigned i = 0; i < nrColoane; i++)
		{
			if (dateColoane[i] != nullptr)
			{
				delete[] dateColoane[i];
			}
		}
		delete[] dateColoane;
	}
	if (valoriImplicite != nullptr)
	{
		delete[] valoriImplicite;
	}
	if (dimensiuni != nullptr)
	{
		delete[] dimensiuni;
	}
	if (tipuri != nullptr)
	{
		delete[] tipuri;
	}
	if (numeColoane != nullptr)
	{
		delete[] numeColoane;
	}
	if (coloaneTabel != nullptr)
	{
		delete[] coloaneTabel;
	}
	return tabel;
}

void createTable(string);
void dropTable(string);
void insertInto(Tabel, string);
void deleteFrom(Tabel, string);
void update(Tabel, string);
void select(Tabel, string);
void displayTable(string);

class Fisier
{
public:
	Fisier() {}
	Fisier(string numeFisier)
	{
		this->numeFisier = numeFisier;
	}
	string getNumeFisier()
	{
		return this->numeFisier;
	}
	void setNumeFisier(string numeFisier)
	{
		if (numeFisier.length() > 0)
		{
			this->numeFisier = numeFisier;
		}
		else
		{
			throw Exceptie("Nume fisier invalid.");
		}
	}
	Fisier(const Fisier& fisier)
	{
		this->numeFisier = fisier.numeFisier;
	}
	const Fisier& operator=(const Fisier& fisier)
	{
		this->numeFisier = fisier.numeFisier;
		return *this;
	}
	virtual ~Fisier() = default;
private:
	string numeFisier = "";
};

class FisierText :public Fisier
{
public:
	void scriereTabelInFisier(Tabel t)
	{
		string numeFisier = t.getDenumireTabel();
		numeFisier += ".txt";
		ofstream f(numeFisier, ios::trunc);
		f << "| ";
		int latime = 0;
		int latimeTotala = 1;
		for (int i = 0; i < t.getNrColoane(); i++)
		{
			Coloana coloana(t.getColoanaTabel(i));
			latime = (coloana.getDimensiune() > coloana.getNumeColoana().length() ? coloana.getDimensiune() : coloana.getNumeColoana().length());
			latimeTotala += (latime + 3);
			printCenter(f, coloana.getNumeColoana(), latime);
		}
		f << endl;
		f << string(latimeTotala, '-');
		f << endl;
		f.close();
	}
	void scriereDateTabelInFisier(Tabel t)
	{
		string numeFisier = t.getDenumireTabel();
		numeFisier += "_date.txt";
		ofstream f(numeFisier, ios::trunc);
		f << t.getDenumireTabel() << " ";
		f << t.getNrColoane() << endl;
		for (int i = 0; i < t.getNrColoane(); i++) {
			f << t.getColoanaTabel(i).getNumeColoana() << " ";
			f << t.getColoanaTabel(i).getTip() << " ";
			f << t.getColoanaTabel(i).getDimensiune() << " ";
			f << t.getColoanaTabel(i).getValoareImplicita() << " ";
			f << endl;
		}
		f << t.getColoanaTabel(0).getNrInregistrari() << endl;
		f.close();
	}
	bool stergereFisierTabel()
	{
		if (remove((Fisier::getNumeFisier() + ".txt").c_str()) != 0)
		{
			throw Exceptie("Eroare la stergerea fisierului.");
		}
		else
		{
			return true;
		}
	}
	void insertRow(string numeFisier, int nrColoane, string* dateDeInserat, int* latimi)
	{
		numeFisier += ".txt";
		ofstream f(numeFisier, ios::app);
		f << "| ";
		for (int i = 0; i < nrColoane; i++)
		{
			print(f, dateDeInserat[i], latimi[i]);
		}
		f << endl;
		f.close();
	}
	void insertRowFisierDate(string numeFisier, int nrColoane, string* dateDeInserat)
	{
		ifstream in(numeFisier + "_date.txt");
		ofstream out(numeFisier + "_date_auxiliar.txt", ios::trunc);
		string buffer = "";
		unsigned i = 0;
		for (; i < nrColoane + 1; i++)
		{
			getline(in, buffer);
			out << buffer << endl;
		}
		int nrInregistrari = 0;
		in >> nrInregistrari;
		out << nrInregistrari + 1 << endl;
		in.get();
		for (i = 0; i < nrInregistrari; i++)
		{
			getline(in, buffer);
			out << buffer << endl;
		}
		for (i = 0; i < nrColoane; i++)
		{
			out << dateDeInserat[i] << " ";
		}
		out << endl;
		out.close();
		in.close();
		ifstream f(numeFisier + "_date_auxiliar.txt");
		ofstream g(numeFisier + "_date.txt", ios::trunc);
		for (i = 0; i < nrColoane + 2; i++)
		{
			getline(f, buffer);
			g << buffer << endl;
		}
		for (i = 0; i < nrInregistrari + 1; i++)
		{
			getline(f, buffer);
			g << buffer << endl;
		}
		g.close();
		f.close();
		remove((numeFisier + "_date_auxiliar.txt").c_str());
	}
	void genereazaRaportSelect(unsigned nrColoane, unsigned nrInregistrari, string** dateSelectate, int latime)
	{
		string numeFisier = "SELECT_" + to_string(nrComenziSelect) + ".txt";
		ofstream f(numeFisier, ios::app);
		for (unsigned i = 0; i < nrInregistrari; i++)
		{
			f << "| ";
			for (unsigned j = 0; j < nrColoane; j++)
			{
				print(f, dateSelectate[i][j], latime);
			}
			f << endl;
		}
		f.close();
	}
};

class FisierBinar :public Fisier
{
public:
	void scriereDateTabelInFisierBinar(Tabel t)
	{
		string numeFisier = t.getDenumireTabel();
		numeFisier += "_date.bin";
		ofstream f(numeFisier, ios::binary | ios::trunc);
		unsigned lungime = t.getDenumireTabel().length();
		f.write((char*)&lungime, sizeof(lungime));
		f.write(t.getDenumireTabel().c_str(), lungime);
		int nrColoane = t.getNrColoane();
		f.write((char*)&nrColoane, sizeof(nrColoane));
		TipDataColoana tip{};
		float dimensiune = 0.0f;
		for (int i = 0; i < nrColoane; i++) {
			lungime = t.getColoanaTabel(i).getNumeColoana().length();
			f.write((char*)&lungime, sizeof(lungime));
			f.write(t.getColoanaTabel(i).getNumeColoana().c_str(), lungime);
			tip = t.getColoanaTabel(i).getTip();
			f.write((char*)&tip, sizeof(tip));
			dimensiune = t.getColoanaTabel(i).getDimensiune();
			f.write((char*)&dimensiune, sizeof(dimensiune));
			lungime = t.getColoanaTabel(i).getValoareImplicita().length();
			f.write((char*)&lungime, sizeof(lungime));
			f.write(t.getColoanaTabel(i).getValoareImplicita().c_str(), lungime);
		}
		int nrInregistrari = t.getColoanaTabel(0).getNrInregistrari();
		f.write((char*)&nrInregistrari, sizeof(nrInregistrari));
		f.close();
	}
	void insertRowDateFisierBinar(string numeFisier, string* dateDeInserat)
	{
		ifstream in(numeFisier + "_date.bin", ios::binary);
		ofstream out(numeFisier + "_date_auxiliar.bin", ios::binary | ios::trunc);
		string buffer = "";
		unsigned lungime = 0;
		in.read((char*)&lungime, sizeof(lungime));
		buffer.resize(lungime);
		in.read((char*)buffer.c_str(), lungime);
		out.write((char*)&lungime, sizeof(lungime));
		out.write(buffer.c_str(), lungime);
		int nrColoane = 0;
		in.read((char*)&nrColoane, sizeof(nrColoane));
		out.write((char*)&nrColoane, sizeof(nrColoane));
		TipDataColoana tip{};
		TipDataColoana* tipuriColoane = new TipDataColoana[nrColoane];
		float dimensiune = 0.0f;
		unsigned i = 0;
		for (; i < nrColoane; i++)
		{
			lungime = 0;
			in.read((char*)&lungime, sizeof(lungime));
			buffer.resize(lungime);
			in.read((char*)buffer.c_str(), lungime);
			out.write((char*)&lungime, sizeof(lungime));
			out.write(buffer.c_str(), lungime);
			tip = Text;
			in.read((char*)&tip, sizeof(tip));
			tipuriColoane[i] = tip;
			out.write((char*)&tip, sizeof(tip));
			dimensiune = 0.0f;
			in.read((char*)&dimensiune, sizeof(dimensiune));
			out.write((char*)&dimensiune, sizeof(dimensiune));
			lungime = 0;
			in.read((char*)&lungime, sizeof(lungime));
			buffer.resize(lungime);
			in.read((char*)buffer.c_str(), lungime);
			out.write((char*)&lungime, sizeof(lungime));
			out.write(buffer.c_str(), lungime);
		}
		int nrInregistrari = 0;
		in.read((char*)&nrInregistrari, sizeof(nrInregistrari));
		nrInregistrari++;
		out.write((char*)&nrInregistrari, sizeof(nrInregistrari));
		int auxiliar = 0;
		float auxiliarFloat = 0.0f;
		for (i = 0; i < nrInregistrari - 1; i++)
		{
			for (unsigned j = 0; j < nrColoane; j++)
			{
				switch (tipuriColoane[j])
				{
				case Text: {
					buffer = "";
					in.read((char*)&lungime, sizeof(lungime));
					buffer.resize(lungime);
					in.read((char*)buffer.c_str(), lungime);
					out.write((char*)&lungime, sizeof(lungime));
					out.write(buffer.c_str(), lungime);
				}
						 break;
				case Integer: {
					auxiliar = 0;
					in.read((char*)&auxiliar, sizeof(auxiliar));
					out.write((char*)&auxiliar, sizeof(auxiliar));
				}
							break;
				case Float: {
					auxiliarFloat = 0.0f;
					in.read((char*)&auxiliarFloat, sizeof(auxiliarFloat));
					out.write((char*)&auxiliarFloat, sizeof(auxiliarFloat));
				}
						  break;
				default:
					break;
				}
			}
		}
		for (i = 0; i < nrColoane; i++)
		{
			switch (tipuriColoane[i])
			{
			case Text: {
				buffer = dateDeInserat[i];
				lungime = buffer.length();
				out.write((char*)&lungime, sizeof(lungime));
				out.write(buffer.c_str(), lungime);
			}
					 break;
			case Integer: {
				auxiliar = stoi(dateDeInserat[i]);
				out.write((char*)&auxiliar, sizeof(auxiliar));
			}
						break;
			case Float: {
				auxiliarFloat = stof(dateDeInserat[i]);
				out.write((char*)&auxiliarFloat, sizeof(auxiliarFloat));
			}
					  break;
			default:
				break;
			}
		}
		out.close();
		in.close();
		remove((numeFisier + "_date.bin").c_str());
		rename((numeFisier + "_date_auxiliar.bin").c_str(), (numeFisier + "_date.bin").c_str());
	}
	bool stergereFisierBinarDate()
	{
		if (remove((Fisier::getNumeFisier() + ".bin").c_str()) != 0)
		{
			throw Exceptie("Eroare la stergerea fisierului.");
		}
		else
		{
			return true;
		}
	}
};

class FisierCsv : public Fisier
{
public:
	void importFromCSV(Tabel t) {
		ifstream f(Fisier::getNumeFisier(), ios::in);
		int nrInregistrari = 0;
		f >> nrInregistrari;
		f.get();
		int nrColoane = t.getNrColoane();
		string** dateFisierCSV = new string * [nrColoane];
		unsigned i = 0;
		unsigned j = 0;
		for (; i < nrColoane; i++)
		{
			dateFisierCSV[i] = new string[nrInregistrari];
		}
		for (i = 0; i < nrColoane; i++)
		{
			for (j = 0; j < nrInregistrari; j++)
			{
				getline(f, dateFisierCSV[i][j], ';');
			}
			f.get();
		}
		string** dateDeInserat = transpusa<string>(dateFisierCSV, nrInregistrari, nrColoane);
		ofstream g(t.getDenumireTabel() + ".txt", ios::app);
		ofstream h(t.getDenumireTabel() + "_date.txt", ios::app);
		ofstream outBin((t.getDenumireTabel() + "_date.bin").c_str(), ios::binary | ios::app);
		int* latimi = new int[nrColoane];
		for (i = 0; i < nrColoane; i++) {
			Coloana coloana(t.getColoanaTabel(i));
			latimi[i] = (coloana.getDimensiune() > coloana.getNumeColoana().length() ? coloana.getDimensiune() : coloana.getNumeColoana().length());
		}
		for (i = 0; i < nrInregistrari; i++)
		{
			g << "| ";
			for (j = 0; j < nrColoane; j++)
			{
				print(g, dateDeInserat[i][j], latimi[j]);
			}
			g << endl;
		}
		TipDataColoana* tipuriColoane = new TipDataColoana[nrColoane];
		string buffer = "";
		int lungime = 0;
		int auxiliar = 0;
		float auxiliarFloat = 0.0f;
		for (unsigned i = 0; i < nrColoane; i++)
		{
			tipuriColoane[i] = t.getColoanaTabel(i).getTip();
		}
		for (unsigned i = 0; i < nrInregistrari; i++)
		{
			for (int j = 0; j < nrColoane; j++)
			{
				h << dateDeInserat[i][j] << " ";
				switch (tipuriColoane[j])
				{
				case Text: {
					buffer = t.getColoanaTabel(j).getDataColoana(i);
					lungime = buffer.length();
					outBin.write((char*)&lungime, sizeof(lungime));
					outBin.write(buffer.c_str(), lungime);
				}
						 break;
				case Integer: {
					auxiliar = stoi(t.getColoanaTabel(j).getDataColoana(i));
					outBin.write((char*)&auxiliar, sizeof(auxiliar));
				}
							break;
				case Float: {
					auxiliarFloat = stof(t.getColoanaTabel(j).getDataColoana(i));
					outBin.write((char*)&auxiliar, sizeof(auxiliar));
				}
						  break;
				default:
					break;
				}
			}
			h << endl;
		}
		outBin.close();
		h.close();
		g.close();
		f.close();
		modificaNumarInregistrariFisierDate(t.getDenumireTabel(), nrColoane, t.getColoanaTabel(0).getNrInregistrari() + nrInregistrari);
	}
};

class ModulFisiereDeIntrare {
private:
	int nrFisiere;
	FisierText* vectorFisiere;
public:
	ModulFisiereDeIntrare()
	{
		this->nrFisiere = 0;
		this->vectorFisiere = nullptr;
	}
	ModulFisiereDeIntrare(int nrFisiere, FisierText* vectorFisiere)
	{
		if (nrFisiere >= 0)
		{
			this->nrFisiere = nrFisiere;
			if (nrFisiere > 0)
			{
				this->vectorFisiere = new FisierText[nrFisiere];
				for (unsigned i = 0; i < nrFisiere; i++)
				{
					this->vectorFisiere[i] = vectorFisiere[i];
				}
			}
			else
			{
				this->vectorFisiere = nullptr;
			}
		}
		else
		{
			throw Exceptie("Numar Fisiere invalid.");
		}
	}
	~ModulFisiereDeIntrare()
	{
		if (this->vectorFisiere)
		{
			delete[]this->vectorFisiere;
			this->vectorFisiere = nullptr;
		}
	}
	void prelucrareFisiereMain()
	{
		for (unsigned i = 0; i < this->nrFisiere; i++)
		{
			ifstream f(this->vectorFisiere[i].getNumeFisier().c_str());
			if (!f.is_open())
			{
				cout << "Imposibil de deschis fisierul <" << this->vectorFisiere[i].getNumeFisier() << ">" << endl;
			}
			else
			{
				string comanda = "";
				while (!f.eof())
				{
					getline(f, comanda, ';');
					comanda += ';';
					if (comanda[0] == '\n')
					{
						comanda.erase(comanda.begin(), comanda.begin() + 1);
					}
					if (comanda != ";")
					{
						switch (tipComanda(comanda))
						{
						case 1: {
							Comanda cmd(comanda);
							if (cmd.validareCreateTable()) {
								createTable(comanda);
								cout << "Tabel creat cu succes." << endl;
							}
						}
							  break;
						case 2: {
							Comanda cmd(comanda);
							if (cmd.validareDropTable()) {
								dropTable(comanda);
							}
						}
							  break;
						case 3: {
							Comanda cmd(comanda);
							if (cmd.validareDisplayTable()) {
								cout << "Structura tabelului " << "<"
									<< impartireInCuvinte(comanda)[2].substr(0, impartireInCuvinte(comanda)[2].length() - 1) << "> este:" << endl;
								displayTable(comanda);
							}
						}
							  break;
						case 4: {
							Comanda cmd(comanda);
							string numeTabel = impartireInCuvinte(comanda)[2];
							Tabel tabel = creareTabelDinFisier(numeTabel);
							if (cmd.validareInsert(tabel)) {
								insertInto(tabel, comanda);
								cout << "Date inserate cu succes." << endl;
							}
						}
							  break;
						case 5: {
							Comanda cmd(comanda);
							string numeTabel = impartireInCuvinte(comanda)[3];
							if (numeTabel[numeTabel.length() - 1] == ';')
							{
								numeTabel.erase(numeTabel.end() - 1, numeTabel.end());
							}
							Tabel tabel = creareTabelDinFisier(numeTabel);
							if (cmd.validareSelect(tabel)) {
								select(tabel, comanda);
							}
						}
							  break;
						case 6: {
							Comanda cmd(comanda);
							string numeTabel = impartireInCuvinte(comanda)[1];
							Tabel tabel = creareTabelDinFisier(numeTabel);
							if (cmd.validareUpdate(tabel)) {
								update(tabel, comanda);
								cout << "Modificari realizate cu succes." << endl;
							}
						}
							  break;
						case 7: {
							Comanda cmd(comanda);
							string numeTabel = impartireInCuvinte(comanda)[2];
							Tabel tabel = creareTabelDinFisier(numeTabel);
							if (cmd.validareDeleteFrom(tabel)) {
								deleteFrom(tabel, comanda);
							}
						}
							  break;
						case 8: {
							Comanda cmd(comanda);
							while (comanda[comanda.length() - 1] == ';') {
								comanda.erase(comanda.end() - 1, comanda.end());
							}
							string numeTabel = impartireInCuvinte(comanda)[1];
							Tabel tabel = creareTabelDinFisier(numeTabel);
							if (cmd.validareImport(tabel)) {
								string numeFisier = impartireInCuvinte(comanda)[2];
								FisierCsv* fisierCSV = new FisierCsv();
								fisierCSV->setNumeFisier(numeFisier);
								fisierCSV->importFromCSV(tabel);
								cout << "Date importate cu succes." << endl;
							}
						}
							  break;
						default:
							break;
						}
					}
				}
				f.close();
			}
		}
	}
};

void createTable(string comandaIntreaga)
{
	string* cuvinteComanda = new string[4];
	while (comandaIntreaga[comandaIntreaga.length() - 1] == ';')
	{
		comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
	}
	cuvinteComanda = impartireInCuvinte(comandaIntreaga);
	string numeTabel = cuvinteComanda[2];
	cuvinteComanda[3].erase(cuvinteComanda[3].begin(), cuvinteComanda[3].begin() + 2);
	cuvinteComanda[3].erase(cuvinteComanda[3].end() - 2, cuvinteComanda[3].end());
	string delimitator = "),(";
	int n = cuvinteComanda[3].find(delimitator);
	int nrColoane = 0;
	string nume[10];
	TipDataColoana tipuri[10]{};
	float dimensiuni[10]{};
	string valoriImplicite[10];
	while (n != -1) {
		string coloana(cuvinteComanda[3]);
		coloana.erase(coloana.begin() + n, coloana.end());
		char* coloanaChar = new char[coloana.length() + 1];
		strcpy_s(coloanaChar, coloana.length() + 1, coloana.c_str());
		nume[nrColoane] = strtok(coloanaChar, ",");
		string tip = strtok(NULL, ",");
		if (upper(tip) == "TEXT")
		{
			tipuri[nrColoane] = Text;
		}
		if (upper(tip) == "INTEGER")
		{
			tipuri[nrColoane] = Integer;
		}
		if (upper(tip) == "FLOAT")
		{
			tipuri[nrColoane] = Float;
		}
		dimensiuni[nrColoane] = stof(strtok(NULL, ","));
		valoriImplicite[nrColoane] = strtok(NULL, ",");
		nrColoane++;
		cuvinteComanda[3].erase(cuvinteComanda[3].begin(), cuvinteComanda[3].begin() + n + delimitator.length());
		n = cuvinteComanda[3].find(delimitator);
	}
	char* coloanaChar = new char[cuvinteComanda[3].length() + 1];
	strcpy_s(coloanaChar, cuvinteComanda[3].length() + 1, cuvinteComanda[3].c_str());
	nume[nrColoane] = strtok(coloanaChar, ",");
	string tip = strtok(NULL, ",");
	if (upper(tip) == "TEXT")
	{
		tipuri[nrColoane] = Text;
	}
	if (upper(tip) == "INTEGER")
	{
		tipuri[nrColoane] = Integer;
	}
	if (upper(tip) == "FLOAT")
	{
		tipuri[nrColoane] = Float;
	}
	dimensiuni[nrColoane] = stof(strtok(NULL, ","));
	valoriImplicite[nrColoane] = strtok(NULL, ",");
	nrColoane++;
	Coloana* vector = new Coloana[nrColoane];
	for (int i = 0; i < nrColoane; i++)
	{
		vector[i] = Coloana(nume[i], tipuri[i], dimensiuni[i], valoriImplicite[i]);
	}
	Tabel tabel(numeTabel, nrColoane, vector);
	FisierText f;
	f.scriereTabelInFisier(tabel);
	f.scriereDateTabelInFisier(tabel);
	FisierBinar fisierBinar;
	fisierBinar.scriereDateTabelInFisierBinar(tabel);
}
void dropTable(string comandaIntreaga)
{
	while (comandaIntreaga[comandaIntreaga.length() - 1] == ';') {
		comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
	}
	string* cuvinteComanda = new string[nrCuvinteComanda(comandaIntreaga)];
	cuvinteComanda = impartireInCuvinte(comandaIntreaga);
	FisierText* f = new FisierText();
	FisierText* fisierDate = new FisierText();
	f->setNumeFisier(cuvinteComanda[2]);
	fisierDate->setNumeFisier(cuvinteComanda[2] + "_date");
	FisierBinar* fisierBinar = new FisierBinar();
	fisierBinar->setNumeFisier(cuvinteComanda[2] + "_date");
	if (f->stergereFisierTabel() && fisierDate->stergereFisierTabel() && fisierBinar->stergereFisierBinarDate())
	{
		cout << "Stergere efectuata." << endl;
	}
}
void insertInto(Tabel t, string comandaIntreaga)
{
	string* cuvinteComanda = new string[5];
	while (comandaIntreaga[comandaIntreaga.length() - 1] == ';')
	{
		comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
	}
	cuvinteComanda = impartireInCuvinte(comandaIntreaga);
	string numeTabel = cuvinteComanda[2];
	int nrColoane = t.getNrColoane();
	string* dateDeInserat = new string[nrColoane];
	cuvinteComanda[4].erase(cuvinteComanda[4].begin(), cuvinteComanda[4].begin() + 1);
	cuvinteComanda[4].erase(cuvinteComanda[4].end() - 1, cuvinteComanda[4].end());
	dateDeInserat[0] = strtok((char*)cuvinteComanda[4].c_str(), ",");
	int i = 1;
	for (; i < nrColoane; i++) {
		dateDeInserat[i] = strtok(NULL, ",");
	}
	int* latimi = new int[nrColoane];
	for (i = 0; i < nrColoane; i++) {
		Coloana coloana(t.getColoanaTabel(i));
		latimi[i] = (coloana.getDimensiune() > coloana.getNumeColoana().length() ? coloana.getDimensiune() : coloana.getNumeColoana().length());
	}
	FisierText f;
	f.insertRow(t.getDenumireTabel(), nrColoane, dateDeInserat, latimi);
	f.insertRowFisierDate(t.getDenumireTabel(), nrColoane, dateDeInserat);
	FisierBinar fisierBinar;
	fisierBinar.insertRowDateFisierBinar(t.getDenumireTabel(), dateDeInserat);
}
void deleteFrom(Tabel t, string comandaIntreaga)
{
	comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
	string numeColoanaCautata = impartireInCuvinte(comandaIntreaga)[4];
	string valoareCautata = impartireInCuvinte(comandaIntreaga)[6];
	FisierText f;
	f.scriereTabelInFisier(t);
	f.scriereDateTabelInFisier(t);
	FisierBinar fisierBinar;
	fisierBinar.scriereDateTabelInFisierBinar(t);
	ofstream out((t.getDenumireTabel() + "_date.txt").c_str(), ios::app);
	ofstream outBin((t.getDenumireTabel() + "_date.bin").c_str(), ios::binary | ios::app);
	int nrColoane = t.getNrColoane();
	int index = -1;
	for (unsigned i = 0; i < nrColoane && index == -1; i++)
	{
		if (t.getColoanaTabel(i).getNumeColoana() == numeColoanaCautata)
		{
			index = i;
		}
	}
	string* dateRand = new string[nrColoane];
	int nrRanduri = t.getColoanaTabel(index).getNrInregistrari();
	int* latimi = new int[nrColoane];
	TipDataColoana* tipuriColoane = new TipDataColoana[nrColoane];
	string buffer = "";
	int lungime = 0;
	int auxiliar = 0;
	float auxiliarFloat = 0.0f;
	for (unsigned i = 0; i < nrColoane; i++)
	{
		tipuriColoane[i] = t.getColoanaTabel(i).getTip();
	}
	for (unsigned i = 0; i < t.getColoanaTabel(index).getNrInregistrari(); i++)
	{
		if (t.getColoanaTabel(index).getDataColoana(i) != valoareCautata)
		{
			for (unsigned j = 0; j < nrColoane; j++)
			{
				out << t.getColoanaTabel(j).getDataColoana(i) << " ";
				switch (tipuriColoane[j])
				{
				case Text: {
					buffer = t.getColoanaTabel(j).getDataColoana(i);
					lungime = buffer.length();
					outBin.write((char*)&lungime, sizeof(lungime));
					outBin.write(buffer.c_str(), lungime);
				}
						 break;
				case Integer: {
					auxiliar = stoi(t.getColoanaTabel(j).getDataColoana(i));
					outBin.write((char*)&auxiliar, sizeof(auxiliar));
				}
							break;
				case Float: {
					auxiliarFloat = stof(t.getColoanaTabel(j).getDataColoana(i));
					outBin.write((char*)&auxiliar, sizeof(auxiliar));
				}
						  break;
				default:
					break;
				}
			}
			out << endl;
			for (unsigned j = 0; j < nrColoane; j++)
			{
				dateRand[j] = t.getColoanaTabel(j).getDataColoana(i);
			}
			for (unsigned k = 0; k < nrColoane; k++) {
				Coloana coloana(t.getColoanaTabel(k));
				latimi[k] = (coloana.getDimensiune() > coloana.getNumeColoana().length() ? coloana.getDimensiune() : coloana.getNumeColoana().length());
			}
			f.insertRow(t.getDenumireTabel(), nrColoane, dateRand, latimi);
		}
		else
		{
			nrRanduri--;
		}
	}
	out.close();
	outBin.close();
	modificaNumarInregistrariFisierDate(t.getDenumireTabel(), nrColoane, nrRanduri);
}
void update(Tabel t, string comandaIntreaga)
{
	comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
	string numeTabela = impartireInCuvinte(comandaIntreaga)[1];
	string coloanaDeModificat = impartireInCuvinte(comandaIntreaga)[3];
	string valoareNoua = impartireInCuvinte(comandaIntreaga)[5];
	string coloanaConditie = impartireInCuvinte(comandaIntreaga)[7];
	string valoareColoanaConditie = impartireInCuvinte(comandaIntreaga)[9];
	FisierText f;
	f.scriereTabelInFisier(t);
	f.scriereDateTabelInFisier(t);
	FisierBinar fisierBinar;
	fisierBinar.scriereDateTabelInFisierBinar(t);
	ofstream out((t.getDenumireTabel() + "_date.txt").c_str(), ios::app);
	ofstream outBin((t.getDenumireTabel() + "_date.bin").c_str(), ios::binary | ios::app);
	int nrColoane = t.getNrColoane();
	int index = -1;
	for (unsigned i = 0; i < nrColoane && index == -1; i++)
	{
		if (t.getColoanaTabel(i).getNumeColoana() == coloanaConditie)
		{
			index = i;
		}
	}
	int indexColoanaDeModificat = -1;
	for (unsigned i = 0; i < nrColoane && indexColoanaDeModificat == -1; i++)
	{
		if (t.getColoanaTabel(i).getNumeColoana() == coloanaDeModificat)
		{
			indexColoanaDeModificat = i;
		}
	}
	string* dateRand = new string[nrColoane];
	int* latimi = new int[nrColoane];
	int nrRanduri = t.getColoanaTabel(index).getNrInregistrari();
	TipDataColoana* tipuriColoane = new TipDataColoana[nrColoane];
	string buffer = "";
	int lungime = 0;
	int auxiliar = 0;
	float auxiliarFloat = 0.0f;
	for (unsigned i = 0; i < nrRanduri; i++)
	{
		if (t.getColoanaTabel(index).getDataColoana(i) != valoareColoanaConditie)
		{
			for (unsigned j = 0; j < nrColoane; j++)
			{
				dateRand[j] = t.getColoanaTabel(j).getDataColoana(i);
			}
		}
		else
		{
			for (unsigned j = 0; j < nrColoane; j++)
			{
				if (j != indexColoanaDeModificat)
				{
					dateRand[j] = t.getColoanaTabel(j).getDataColoana(i);
				}
				else
				{
					dateRand[j] = valoareNoua;
				}
			}
		}
		for (unsigned k = 0; k < nrColoane; k++)
		{
			Coloana coloana(t.getColoanaTabel(k));
			latimi[k] = (coloana.getDimensiune() > coloana.getNumeColoana().length() ? coloana.getDimensiune() : coloana.getNumeColoana().length());
		}
		f.insertRow(t.getDenumireTabel(), nrColoane, dateRand, latimi);
		for (unsigned j = 0; j < nrColoane; j++)
		{
			out << dateRand[j] << " ";
			switch (tipuriColoane[j])
			{
			case Text: {
				buffer = t.getColoanaTabel(j).getDataColoana(i);
				lungime = buffer.length();
				outBin.write((char*)&lungime, sizeof(lungime));
				outBin.write(buffer.c_str(), lungime);
			}
					 break;
			case Integer: {
				auxiliar = stoi(t.getColoanaTabel(j).getDataColoana(i));
				outBin.write((char*)&auxiliar, sizeof(auxiliar));
			}
						break;
			case Float: {
				auxiliarFloat = stof(t.getColoanaTabel(j).getDataColoana(i));
				outBin.write((char*)&auxiliar, sizeof(auxiliar));
			}
					  break;
			default:
				break;
			}
		}
		out << endl;
	}
	out.close();
	outBin.close();
}
void select(Tabel t, string comandaIntreaga)
{
	comandaIntreaga.erase(comandaIntreaga.end() - 1, comandaIntreaga.end());
	string coloaneDorite = impartireInCuvinte(comandaIntreaga)[1];
	unsigned nrInregistrari = t.getColoanaTabel(0).getNrInregistrari();
	unsigned nrColoane = t.getNrColoane();
	unsigned i = 0;
	int latime = 0;
	for (; i < nrColoane; i++)
	{
		if (ceil(t.getColoanaTabel(i).getDimensiune()) > latime)
		{
			latime = ceil(t.getColoanaTabel(i).getDimensiune());
		}
	}
	nrComenziSelect++;
	string numeFisier = "SELECT_" + to_string(nrComenziSelect) + ".txt";
	ofstream f(numeFisier, ios::trunc);
	if (upper(coloaneDorite) == "ALL")
	{
		cout << "| ";
		for (i = 0; i < nrColoane; i++)
		{
			int umplutura = latime - t.getColoanaTabel(i).getNumeColoana().length();
			int j = 0;
			for (; j < umplutura / 2; j++) {
				cout << " ";
			}
			cout << upper(t.getColoanaTabel(i).getNumeColoana());
			for (j = 0; j < umplutura / 2; j++) {
				cout << " ";
			}
			if (umplutura > 0 && umplutura % 2 != 0) {
				cout << " ";
			}
			cout << " | ";
		}
		cout << endl;
		cout << string(nrColoane * (latime + 3) + 1, '-');
		cout << endl;
		f << "| ";
		for (i = 0; i < nrColoane; i++)
		{
			printCenter(f, upper(t.getColoanaTabel(i).getNumeColoana()), latime);
		}
		f << endl;
		f << string(nrColoane * (latime + 3) + 1, '-');
		f << endl;
		f.close();
		string** dateSelectate = new string * [nrColoane];
		if (nrCuvinteComanda(comandaIntreaga) < 5)
		{
			for (i = 0; i < nrColoane; i++)
			{
				dateSelectate[i] = new string[nrInregistrari];
			}
			for (i = 0; i < nrColoane; i++)
			{
				for (unsigned j = 0; j < nrInregistrari; j++)
				{
					dateSelectate[i][j] = t.getColoanaTabel(i).getDataColoana(j);
				}
			}
			string** dateSelectateTranspuse = transpusa<string>(dateSelectate, nrColoane, nrInregistrari);
			for (i = 0; i < nrInregistrari; i++)
			{
				cout << "| ";
				for (unsigned j = 0; j < nrColoane; j++)
				{
					cout << fixed << left;
					cout.fill(' ');
					cout.width(latime);
					cout << dateSelectateTranspuse[i][j] << " | ";
				}
				cout << endl;
			}
			FisierText f;
			f.genereazaRaportSelect(nrColoane, nrInregistrari, dateSelectateTranspuse, latime);
			for (i = 0; i < nrColoane; i++)
			{
				delete[]dateSelectate[i];
			}
			delete[]dateSelectate;
			for (i = 0; i < nrInregistrari; i++)
			{
				delete[]dateSelectateTranspuse[i];
			}
			delete[]dateSelectateTranspuse;
		}
		else
		{
			string numeColoana = impartireInCuvinte(comandaIntreaga)[5];
			string valoare = impartireInCuvinte(comandaIntreaga)[7];
			valoare.erase(valoare.end() - 1, valoare.end());
			int indexColoana = -1;
			for (i = 0; i < nrColoane && indexColoana == -1; i++)
			{
				if (t.getColoanaTabel(i).getNumeColoana() == numeColoana)
				{
					indexColoana = i;
				}
			}
			int nrValoriGasite = 0;
			for (i = 0; i < nrInregistrari; i++)
			{
				if (t.getColoanaTabel(indexColoana).getDataColoana(i) == valoare)
				{
					nrValoriGasite++;
				}
			}
			int* indecsi = new int[nrValoriGasite];
			unsigned k = 0;
			for (i = 0; i < nrInregistrari; i++)
			{
				if (t.getColoanaTabel(indexColoana).getDataColoana(i) == valoare)
				{
					indecsi[k++] = i;
				}
			}
			for (i = 0; i < nrColoane; i++)
			{
				dateSelectate[i] = new string[nrValoriGasite];
			}
			for (i = 0; i < nrColoane; i++)
			{
				for (unsigned j = 0; j < nrValoriGasite; j++)
				{
					dateSelectate[i][j] = t.getColoanaTabel(i).getDataColoana(indecsi[j]);
				}
			}
			string** dateSelectateTranspuse = transpusa<string>(dateSelectate, nrColoane, nrValoriGasite);
			for (i = 0; i < nrValoriGasite; i++)
			{
				cout << "| ";
				for (unsigned j = 0; j < nrColoane; j++)
				{
					cout << fixed << left;
					cout.fill(' ');
					cout.width(latime);
					cout << dateSelectateTranspuse[i][j] << " | ";
				}
				cout << endl;
			}
			FisierText f;
			f.genereazaRaportSelect(nrColoane, nrValoriGasite, dateSelectateTranspuse, latime);
			for (i = 0; i < nrColoane; i++)
			{
				delete[]dateSelectate[i];
			}
			delete[]dateSelectate;
			for (i = 0; i < nrValoriGasite; i++)
			{
				delete[]dateSelectateTranspuse[i];
			}
			delete[]dateSelectateTranspuse;
		}
	}
	else
	{
		coloaneDorite.erase(coloaneDorite.end() - 1, coloaneDorite.end());
		coloaneDorite.erase(coloaneDorite.begin(), coloaneDorite.begin() + 1);
		int nrColoaneDorite = nrCuvinteComandaVirgula(coloaneDorite);
		string** dateSelectate = new string * [nrColoaneDorite];
		string* coloane = impartireInCuvinteDupaVirgula(coloaneDorite);
		cout << "| ";
		for (i = 0; i < nrColoaneDorite; i++)
		{
			int umplutura = latime - coloane[i].length();
			int j = 0;
			for (; j < umplutura / 2; j++) {
				cout << " ";
			}
			cout << upper(coloane[i]);
			for (j = 0; j < umplutura / 2; j++) {
				cout << " ";
			}
			if (umplutura > 0 && umplutura % 2 != 0) {
				cout << " ";
			}
			cout << " | ";
		}
		cout << endl;
		cout << string(nrColoaneDorite * (latime + 3) + 1, '-');
		cout << endl;
		f << "| ";
		for (i = 0; i < nrColoaneDorite; i++)
		{
			printCenter(f, upper(coloane[i]), latime);
		}
		f << endl;
		f << string(nrColoaneDorite * (latime + 3) + 1, '-');
		f << endl;
		f.close();
		unsigned* indecsiColoaneDorite = new unsigned[nrColoaneDorite];
		for (i = 0; i < nrColoaneDorite; i++)
		{
			for (unsigned j = 0; j < nrColoane; j++)
			{
				if (t.getColoanaTabel(j).getNumeColoana() == coloane[i])
				{
					indecsiColoaneDorite[i] = j;
				}
			}
		}
		if (nrCuvinteComanda(comandaIntreaga) < 5)
		{
			for (i = 0; i < nrColoaneDorite; i++)
			{
				dateSelectate[i] = new string[nrInregistrari];
			}
			for (i = 0; i < nrColoaneDorite; i++)
			{
				for (unsigned j = 0; j < nrInregistrari; j++)
				{
					dateSelectate[i][j] = t.getColoanaTabel(indecsiColoaneDorite[i]).getDataColoana(j);
				}
			}
			string** dateSelectateTranspuse = transpusa<string>(dateSelectate, nrColoaneDorite, nrInregistrari);
			for (i = 0; i < nrInregistrari; i++)
			{
				cout << "| ";
				for (unsigned j = 0; j < nrColoaneDorite; j++)
				{
					cout << fixed << left;
					cout.fill(' ');
					cout.width(latime);
					cout << dateSelectateTranspuse[i][j] << " | ";
				}
				cout << endl;
			}
			FisierText f;
			f.genereazaRaportSelect(nrColoaneDorite, nrInregistrari, dateSelectateTranspuse, latime);
			for (i = 0; i < nrColoaneDorite; i++)
			{
				delete[]dateSelectate[i];
			}
			delete[]dateSelectate;
			for (i = 0; i < nrInregistrari; i++)
			{
				delete[]dateSelectateTranspuse[i];
			}
			delete[]dateSelectateTranspuse;
		}
		else
		{
			string numeColoana = impartireInCuvinte(comandaIntreaga)[5];
			string valoare = impartireInCuvinte(comandaIntreaga)[7];
			valoare.erase(valoare.end() - 1, valoare.end());
			int indexColoanaCautata = -1;
			for (i = 0; i < nrColoane && indexColoanaCautata == -1; i++)
			{
				if (t.getColoanaTabel(i).getNumeColoana() == numeColoana)
				{
					indexColoanaCautata = i;
				}
			}
			int nrValoriGasite = 0;
			for (i = 0; i < nrInregistrari; i++)
			{
				if (t.getColoanaTabel(indexColoanaCautata).getDataColoana(i) == valoare)
				{
					nrValoriGasite++;
				}
			}
			for (i = 0; i < nrColoaneDorite; i++)
			{
				dateSelectate[i] = new string[nrValoriGasite];
			}
			int* indecsiValoare = new int[nrValoriGasite];
			unsigned k = 0;
			for (i = 0; i < nrInregistrari; i++)
			{
				if (t.getColoanaTabel(indexColoanaCautata).getDataColoana(i) == valoare)
				{
					indecsiValoare[k++] = i;
				}
			}
			for (i = 0; i < nrColoaneDorite; i++)
			{
				for (unsigned j = 0; j < nrValoriGasite; j++)
				{
					dateSelectate[i][j] = t.getColoanaTabel(indecsiColoaneDorite[i]).getDataColoana(indecsiValoare[j]);
				}
			}
			string** dateSelectateTranspuse = transpusa<string>(dateSelectate, nrColoaneDorite, nrValoriGasite);
			for (i = 0; i < nrValoriGasite; i++)
			{
				cout << "| ";
				for (unsigned j = 0; j < nrColoaneDorite; j++)
				{
					cout << fixed << left;
					cout.fill(' ');
					cout.width(latime);
					cout << dateSelectateTranspuse[i][j] << " | ";
				}
				cout << endl;
			}
			FisierText f;
			f.genereazaRaportSelect(nrColoaneDorite, nrValoriGasite, dateSelectateTranspuse, latime);
			for (i = 0; i < nrColoaneDorite; i++)
			{
				delete[]dateSelectate[i];
			}
			delete[]dateSelectate;
			for (i = 0; i < nrValoriGasite; i++)
			{
				delete[]dateSelectateTranspuse[i];
			}
			delete[]dateSelectateTranspuse;
		}
	}
	cout << endl;
}
void displayTable(string comanda)
{
	string numeTabel = impartireInCuvinte(comanda)[2];
	numeTabel.erase(numeTabel.end() - 1, numeTabel.end());
	Tabel tabel = creareTabelDinFisier(numeTabel);
	cout << numeTabel << endl;
	for (unsigned i = 0; i < tabel.getNrColoane(); i++)
	{
		cout << tabel.getColoanaTabel(i).getNumeColoana() << " " << tabel.getColoanaTabel(i).getTip() << " ";
		streamsize ss = cout.precision();
		if (tabel.getColoanaTabel(i).getTip() == Float)
		{
			float dimensiune = tabel.getColoanaTabel(i).getDimensiune();
			float parteFractionara = dimensiune - (int)dimensiune;
			while ((int)parteFractionara % 10 == 0)
			{
				parteFractionara *= 10;
			}
			int precizie = 0;
			while ((int)parteFractionara != 0)
			{
				parteFractionara /= 10;
				precizie++;
			}
			cout << setprecision(precizie) << dimensiune << setprecision(ss) << " ";
		}
		else
		{
			cout << setprecision(0) << tabel.getColoanaTabel(i).getDimensiune() << setprecision(ss) << " ";
		}
		cout << tabel.getColoanaTabel(i).getValoareImplicita();
		cout << endl;
	}
	cout << endl;
	nrComenziDisplay++;
	string numeFisier = "DISPLAY_" + to_string(nrComenziDisplay) + ".txt";
	ofstream f(numeFisier, ios::trunc);
	f << numeTabel << endl;
	for (unsigned i = 0; i < tabel.getNrColoane(); i++)
	{
		f << tabel.getColoanaTabel(i).getNumeColoana() << " " << tabel.getColoanaTabel(i).getTip() << " " << tabel.getColoanaTabel(i).getDimensiune() << " " << tabel.getColoanaTabel(i).getValoareImplicita();
		f << endl;
	}
	f.close();
}

int main(int argc, char* argv[])
{
	//cd C:\Users\mihai\source\repos\MySQLite\Debug
	//MySQLite.exe C:\Users\mihai\source\repos\MySQLite\MySQLite\Proiect_1051_Duca_Elena_Alexandra_Dulgheru_Mihai_Nicolae_Duta_Catalin_Ionut.txt
	try {
		if (argc > 6)
		{
			cout << endl << "Numar de argumente invalid." << endl;
		}
		else
		{
			if (argc > 1)
			{
				string locatie(argv[1]);
				locatie = locatie.substr(0, locatie.find_last_of("\\"));
				if (_chdir(locatie.c_str()))
				{
					cout << endl << "Eroare la schimbarea directorului curent." << endl;
				}
				string* locatii = new string[argc - 1];
				FisierText* vectorFisiere = new FisierText[argc - 1];
				for (unsigned i = 0; i < argc - 1; i++)
				{
					vectorFisiere[i].setNumeFisier(argv[i + 1]);
				}
				ModulFisiereDeIntrare modul(argc - 1, vectorFisiere);
				modul.prelucrareFisiereMain();
			}
		}
		string comanda = "";
		while (true)
		{
			cout << endl << "Introduceti comanda (sau exit): ";
			getline(cin, comanda);
			if (comanda == "exit")
			{
				break;
			}
			else
			{
				switch (tipComanda(comanda))
				{
				case 1: {
					Comanda cmd(comanda);
					if (cmd.validareCreateTable()) {
						createTable(comanda);
						cout << endl;
						cout << "Tabel creat cu succes." << endl;
					}
				}
					  break;
				case 2: {
					Comanda cmd(comanda);
					if (cmd.validareDropTable()) {
						cout << endl;
						dropTable(comanda);
					}
				}
					  break;
				case 3: {
					Comanda cmd(comanda);
					if (cmd.validareDisplayTable()) {
						cout << endl;
						cout << "Structura tabelului " << "<" << impartireInCuvinte(comanda)[2].substr(0, impartireInCuvinte(comanda)[2].length() - 1) << "> este:" << endl;
						displayTable(comanda);
					}
				}
					  break;
				case 4: {
					Comanda cmd(comanda);
					string numeTabel = impartireInCuvinte(comanda)[2];
					Tabel tabel = creareTabelDinFisier(numeTabel);
					if (cmd.validareInsert(tabel)) {
						insertInto(tabel, comanda);
						cout << endl;
						cout << "Date inserate cu succes." << endl;
					}
				}
					  break;
				case 5: {
					Comanda cmd(comanda);
					string numeTabel = impartireInCuvinte(comanda)[3];
					if (numeTabel[numeTabel.length() - 1] == ';')
					{
						numeTabel.erase(numeTabel.end() - 1, numeTabel.end());
					}
					Tabel tabel = creareTabelDinFisier(numeTabel);
					if (cmd.validareSelect(tabel)) {
						cout << endl;
						select(tabel, comanda);
					}
				}
					  break;
				case 6: {
					Comanda cmd(comanda);
					string numeTabel = impartireInCuvinte(comanda)[1];
					Tabel tabel = creareTabelDinFisier(numeTabel);
					if (cmd.validareUpdate(tabel)) {
						update(tabel, comanda);
						cout << endl;
						cout << "Modificari realizate cu succes." << endl;
					}
				}
					  break;
				case 7: {
					Comanda cmd(comanda);
					string numeTabel = impartireInCuvinte(comanda)[2];
					Tabel tabel = creareTabelDinFisier(numeTabel);
					if (cmd.validareDeleteFrom(tabel)) {
						cout << endl;
						deleteFrom(tabel, comanda);
						cout << "Stergere efectuata." << endl;
					}
				}
					  break;
				case 8: {
					Comanda cmd(comanda);
					while (comanda[comanda.length() - 1] == ';') {
						comanda.erase(comanda.end() - 1, comanda.end());
					}
					string numeTabel = impartireInCuvinte(comanda)[1];
					Tabel tabel = creareTabelDinFisier(numeTabel);
					if (cmd.validareImport(tabel)) {
						cout << endl;
						string numeFisier = impartireInCuvinte(comanda)[2];
						FisierCsv* fisierCSV = new FisierCsv();
						fisierCSV->setNumeFisier(numeFisier);
						fisierCSV->importFromCSV(tabel);
						cout << "Date importate cu succes." << endl;
					}
				}
					  break;
				default:
					break;
				}
			}
		}
	}
	catch (Exceptie exceptie) {
		cout << exceptie.getMesajExceptie() << endl;
	}
	catch (...) {
		cout << "Eroare necunoscuta";
	}
	return 0;
}