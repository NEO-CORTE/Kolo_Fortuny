#pragma once
#include "Player.h"
#include "wheel.h"
#include <algorithm>
class GameMaster
{
private:
	vector<Player> gracze;
	vector<string>crosswords;
	string mainCrossword;
	int mask[100];
public:
	void GameControl();
	void printPlayers_CC(int queue);
	void getCrosswordsFF();
	void crosswordRNGmask();
	void printCrossMask();
	int isVowel(char c);
	char LoadChar();
	char LoadChoice();

};