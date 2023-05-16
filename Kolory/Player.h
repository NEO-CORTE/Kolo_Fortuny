#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
using namespace std;


class Player {
private:
	string name;
	int money = 0;
	int wallet = 0;
public:
	//friend inline bool comparePlayers(Player* gracz1, Player* gracz2);
	friend istream& operator >> (istream& is, Player& gracz) {
		cout << "Podaj imie:" << endl;
		is >> gracz.name;
		cout << endl;
		return is;
	}

	friend ostream& operator << (ostream& os, Player* gracz) {
		os << "Imie: \033[1;32m" << gracz->name << "\033[0m\t" << "Pieniadze: \033[1;31m" << gracz->money << "\033[0m" << endl;
		return os;
	}
	// Alteration

	void alterName(string n);
	void alterWallet(int m);
	void alterMoney(int m);

	// Retrival

	string getPlayer_Name();
	int getPlayer_Wallet();
	int getPlayer_Money();
};

// Compare the players
//inline bool comparePlayers(Player* gracz1, Player* gracz2) {
//	if (&gracz1->wallet != &gracz2->wallet) {
//		return &gracz1->wallet > &gracz2->wallet;
//	}
//}