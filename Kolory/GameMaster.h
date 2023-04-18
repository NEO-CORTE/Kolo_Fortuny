#pragma once
#include "Player.h"
#include "wheel.h"
class GameMaster
{
private:
	Player players[3];
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