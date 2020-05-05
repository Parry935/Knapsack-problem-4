#ifndef OBLICZENIA_H
#define OBLICZENIA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Funkcja obliczajaca K*/
int obliczanie_k(vector<int> dodanie, vector<int> waga, int M_max, int ilosc);

/* Funkcja obliczajaca Totalweight*/
int obliczanie_totweight(vector<int> dodanie, vector<int> waga, int k);

/* Funkcja obliczajaca Bound*/
int obliczanie_bound(vector<int> dodanie, int k, vector<int> wartosc, int totweight, vector<int> stosunek, int M_max, int ilosc);

/* Funkcja obliczajaca wszystkie pozostale wartosci i zapisujaca je do pliku tekstowego*/
void obliczanie_wartosci(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, vector<int>dodanie, int&Max_profit, int&poziom, vector<int>&PROF, vector<int>&WEI, drzewo *wezel, fstream &file, int &krok);

#endif
