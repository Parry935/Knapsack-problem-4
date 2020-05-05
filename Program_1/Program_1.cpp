 // Pepaś Dominik - 11:00

#include "pch.h"
#include "Drzewo.h"
#include "Obliczenia.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	string nazwa_pliku_in;
	string nazwa_pliku_out;

	int M_max = 0;
	int ilosc = 0;

	vector<int>	wartosc;
	vector<int> waga;
	vector<int> stosunek;

	cout << "Podaj nazwe pliku z ktorego chcesz odczytac dane wejsciowe: " << endl;
	cin >> nazwa_pliku_in;
	cout << endl;

	cout << "Podaj nazwe pliku z ktorego chcesz odczytac dane wejsciowe: " << endl;
	cin >> nazwa_pliku_out;
	cout << endl;

	odczyt_z_pliku(M_max, wartosc, waga, stosunek, ilosc, nazwa_pliku_in);

	algorytm_z_powrotami(M_max, wartosc, waga, stosunek, ilosc,nazwa_pliku_out);

	return 0;
}


