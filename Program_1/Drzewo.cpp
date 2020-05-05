#include "pch.h"
#include "Drzewo.h"
#include "Obliczenia.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

int odczyt_z_pliku(int & M_max, vector<int>& wartosc, vector<int>& waga, vector<int>& stosunek, int & ilosc, string nazwa_pliku_in)
{
	fstream file;
	file.open(nazwa_pliku_in.c_str(), ios::in);
	if (file.good() == false)  // sprwadzenie czy plik o podanej nazwie istnieje
	{
		cout << "Nie udalo sie otworzyc pliku" << endl;
		exit(0);
	}

	file >> ilosc;
	file >> M_max;

	int dana = 0;

	for(int i=0; i<ilosc; i++)
	{
		
		file  >> dana;
		wartosc.push_back(dana);

		file >> dana;
		waga.push_back(dana);

		file >> dana;
		stosunek.push_back(dana);

	}

	file.close();  // zamkniecie pliku

	return 0;
}


int algorytm_z_powrotami(int M_max, vector<int> wartosc, vector<int> waga, vector<int> stosunek, int ilosc, string nazwa_pliku_out)
{
	int Max_profit = 0;
	int poziom = 0;
	int krok = 0;
	vector<int> PROF;
	vector<int> WEI;

	// stworzenie korzenia drzewa

	drzewo *korzen = new drzewo;
	drzewo *wezel;

	// stworzenie vectora okreœlaj¹cego ktore przedmioty maj¹ byæ dodane do plecaka w danym wêŸle

	vector<int> dodanie(ilosc, 1);

	korzen->left = nullptr;
	korzen->right = nullptr;
	korzen->top = nullptr;

	korzen->k = obliczanie_k(dodanie, waga, M_max, ilosc);
	korzen->totweight = obliczanie_totweight(dodanie,waga, korzen->k);
	korzen->bound = obliczanie_bound(dodanie, korzen->k , wartosc, korzen->totweight, stosunek, M_max, ilosc);
	
	wezel = korzen;

	// otwarcie pliku do zapisu

	fstream file;
	file.open(nazwa_pliku_out.c_str(), ios::out);
	if (file.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku" << endl;
		exit(0);
	}

	// wpisanie wartoœci dla korzenia

	krok++;

	file << "KROK NR: " << krok << endl << endl;
	file << "Max profit: " << Max_profit << endl;
	file << "Profit: " << wezel->profit << endl;
	file << "Weight: " << wezel->weight << endl;
	file << "Bound: " << wezel->bound << endl;
	file << "K: " << wezel->k << endl;
	file << "Totalweight: " << wezel->totweight << endl;

	if (wezel->weight<M_max && wezel->bound > Max_profit)
		file << "OBIECUJACY" << endl;
	else
		file << "NIEOBIECUJACY" << endl;

	file << endl;



	wezly_lewe(M_max, wartosc, waga, stosunek, ilosc, dodanie, Max_profit, poziom, PROF, WEI, wezel,file,krok);

	file.close(); // zamkniêcie pliku do zapisu

	return 0;
}

drzewo *dodaj_element_z_lewej(drzewo *w)
{
	drzewo * n;

	n = new drzewo;

	n->top = w;
	n->left = nullptr;
	n->right = nullptr;

	w->left = n;
	
	return n;
}

drzewo *dodaj_element_z_prawej(drzewo *w)
{
	drzewo * n;

	n = new drzewo;

	n->top = w;
	n->left = nullptr;
	n->right = nullptr;

	w->right = n;

	return n;
}

drzewo *nawroc(drzewo *w)
{
	w = w->top;

	return w;
}

void wezly_lewe(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, vector<int>dodanie, int Max_profit, int poziom, vector<int>PROF, vector<int>WEI, drzewo *wezel, fstream &file, int krok)
{
	while (wezel->weight<M_max && wezel->bound > Max_profit)
	{
		wezel = dodaj_element_z_lewej(wezel);

		obliczanie_wartosci(M_max, wartosc, waga, stosunek, ilosc, dodanie, Max_profit, poziom, PROF, WEI, wezel,file,krok);
	}

	wezel = nawroc(wezel); //jeœli warunki nie s¹ spe³nione wróæ do rodzica
	poziom--; // zmniejsz poziom

	PROF.pop_back();
	WEI.pop_back();

	// przejdŸ do wez³u prawego

	wezly_prawe(M_max, wartosc, waga, stosunek, ilosc, dodanie, Max_profit, poziom, PROF, WEI, wezel,file,krok);

}

int wezly_prawe(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, vector<int>dodanie, int Max_profit, int poziom, vector<int>PROF, vector<int>WEI, drzewo *wezel, fstream &file, int krok)
{

	if (wezel->right == nullptr) // jeœli nie ma wêz³u prawego -> stworz go
	{
		wezel = dodaj_element_z_prawej(wezel);
		dodanie[poziom] = 0;

		obliczanie_wartosci(M_max, wartosc, waga, stosunek, ilosc, dodanie, Max_profit, poziom, PROF, WEI, wezel,file,krok);
	

		if (wezel->weight<M_max && wezel->bound > Max_profit) //jeœli wêze³ prawy jest obiecuj¹cy -> twórz od niego wêz³y lewe
			wezly_lewe(M_max, wartosc, waga, stosunek, ilosc, dodanie, Max_profit, poziom, PROF, WEI, wezel,file,krok);

	}

	wezel = nawroc(wezel); // jeœli nie jest obiecuj¹cy -> wróæ do rodzica
	poziom--;
	dodanie[poziom] = 1;


	while (wezel->right != nullptr) //szukanie miejsca dla wêz³a prawego
	{

		if (poziom == 0 && wezel->right != nullptr) //zakoñczenie ca³ego algorytmu
			return 0;


		wezel = nawroc(wezel);
		poziom--;

		if (poziom >= 0)
		{
			if (dodanie[poziom] == 1)
			{
				if (!PROF.empty() && !WEI.empty())
				{
					PROF.pop_back();
					WEI.pop_back();
				}
			}

			dodanie[poziom] = 1;
		}
	}

	// jeœli znajdziemy miejsce dla wez³a prawego przechodzimy do tworzenia go

	wezly_prawe(M_max, wartosc, waga, stosunek, ilosc, dodanie, Max_profit, poziom, PROF, WEI, wezel,file,krok);
}


