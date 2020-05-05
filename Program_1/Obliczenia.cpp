#include "pch.h"
#include "Drzewo.h"
#include "Obliczenia.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void obliczanie_wartosci(int M_max, vector<int>wartosc, vector<int> waga, vector<int>stosunek, int ilosc, vector<int>dodanie, int&Max_profit, int&poziom, vector<int>&PROF, vector<int>&WEI, drzewo *wezel, fstream &file, int &krok)
{
	int suma_prof = 0;
	int suma_wei = 0;

	wezel->k = obliczanie_k(dodanie, waga, M_max, ilosc);
	wezel->totweight = obliczanie_totweight(dodanie, waga, wezel->k);
	wezel->bound = obliczanie_bound(dodanie, wezel->k, wartosc, wezel->totweight, stosunek, M_max, ilosc);

	if (dodanie[poziom] == 1)
	{
		PROF.push_back(wartosc[poziom]);
		WEI.push_back(waga[poziom]);

	}

	for (int i = 0; i < PROF.size(); i++)
	{
		suma_prof += PROF[i];
		suma_wei += WEI[i];
	}

	wezel->profit = suma_prof;
	wezel->weight = suma_wei;

	if (suma_prof > Max_profit && wezel->weight<M_max && wezel->bound > Max_profit)
		Max_profit = suma_prof;


	poziom++;

	//wypisanie waroœci w okreœlonym wêŸle

	krok++;

	file << "KROK NR: " << krok << endl << endl;
	file << "Max_profit: " << Max_profit << endl;
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

}

int obliczanie_k(vector<int> dodanie, vector<int> waga, int M_max, int ilosc)
{
	int k = 1;
	int suma = 0;

	for (int i = 0; i < ilosc; i++)
	{
		if (dodanie[i] == 1)
		{
			if (suma + waga[i] <= M_max)
				suma += waga[i];

			else
				break;
		}

		k++;

	}

	return k;
}

int obliczanie_totweight(vector<int> dodanie, vector<int> waga, int k)
{
	int totweight = 0;

	for (int i = 0; i < k - 1; i++)
	{
		if (dodanie[i] == 1)
		{
			totweight += waga[i];
		}

	}

	return totweight;
}

int obliczanie_bound(vector<int> dodanie, int k, vector<int> wartosc, int totweight, vector<int> stosunek, int M_max, int ilosc)
{
	int suma = 0;

	int bound = 0;

	for (int i = 0; i < k - 1; i++)
	{
		if (dodanie[i] == 1)
		{
			suma += wartosc[i];
		}

	}

	int zysk = 0;

	if (k > ilosc)
		zysk = 0;
	else
		zysk = stosunek[k - 1];


	bound = suma + (M_max - totweight) * zysk;

	return bound;
}