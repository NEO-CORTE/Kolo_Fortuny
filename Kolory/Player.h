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
	int money;
	int wallet;
public:
	// Alteration

	void alterName(string n);
	void alterWallet(int m);
	void alterMoney(int m);

	// Retrival

	string getPlayer_Name();
	int getPlayer_Wallet();
	int getPlayer_Money();
};

