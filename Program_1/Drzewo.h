#ifndef DRZEWO_H
#define DRZEWO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// stworzenie struktury dla wêz³ów
struct drzewo
{
	drzewo *top, *left, *right;
	int profit=0;
	int weight=0;
	int bound=0;
	int totweight=0;
	int k=0;
};

/* Funkcja odczytuj¹ca dane wejœciowe z pliku tekstowego*/
int odczyt_z_pliku(int & M_max, vector<int>&wartosc, vector<int>& waga, vector<int>& stosunek, int & ilosc, string nazwa_pliku_in);

/* G³ówna funkcja zawieraj¹ca wiêkszoœæ funkcji, tworzy korzeñ drzewa oraz otwiera i zamyka plik tekstowy do zapisu*/
int algorytm_z_powrotami(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, string nazwa_pliku_out);

/* Funkcja tworz¹ca weze³ z lewej strony od rodzica*/
drzewo *dodaj_element_z_lewej(drzewo *wezel);

/* Funkcja tworz¹ca weze³ z prawej strony od rodzica*/
drzewo *dodaj_element_z_prawej(drzewo *wezel);

/* Funkcja powracajaca do rodzica z jej lewego lub prawego dziecka*/
drzewo *nawroc(drzewo *w);

/* Funkcja odpowiadaj¹ca za poruszanie siê i obliczanie wartoœci w lewych wêz³ach*/
void wezly_lewe(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, vector<int>dodanie, int Max_profit, int poziom, vector<int>PROF, vector<int>WEI, drzewo *wezel, fstream &file, int krok);

/* Funkcja odpowiadaj¹ca za poruszanie siê i obliczanie wartoœci w prawych wêz³ach*/
int wezly_prawe(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, vector<int>dodanie, int Max_profit, int poziom, vector<int>PROF, vector<int>WEI, drzewo *wezel, fstream &file, int krok);


#endif
