#pragma once
#include "GameMaster.h"
void GameMaster::GameControl() {
	srand(time(NULL));
	setlocale(LC_CTYPE, "pl_PL");
	GameMaster::getCrosswordsFF();
	Player gracz1;
	Player gracz2;
	Player gracz3;
	cin >> gracz1;
	cin >> gracz2;
	cin >> gracz3;
	gracze.push_back(gracz1);
	gracze.push_back(gracz2);
	gracze.push_back(gracz3);
	string crossword, trial, result;
	char singleLetter, choice;
	int rng = 0, sum = 0, guessed = 0, are_consonants = 0, amount = 0, queue = 0;
	wheel tmpWheel;
	int* board = tmpWheel.getWheel();
	GameMaster::crosswordRNGmask();

	cout << tmpWheel;
	
	do {
		amount = 0;
		GameMaster::printCrossMask();
		are_consonants = 0;
		amount = 0;
		for (int i = 0; i < mainCrossword.size(); i++) {
			if (!GameMaster::isVowel(mainCrossword[i]) && mask[i]) {
				are_consonants = 1;
				break;
			}
		}
		if (are_consonants) {
			cout << " <-- There are consonants in the crossword -->" << endl;
		}
		GameMaster::printPlayers_CC(queue);
		cout << "1. Guess the Crossword" << endl;
		cout << "2. Spin the wheel" << endl;

		choice = GameMaster::LoadChoice();
		if (choice == '1') {
			cout << "Input your guess" << endl;
			getline(cin >> ws, trial);
			for (auto& c : trial) {
				c = toupper(c);
			}
			if (mainCrossword == trial) {
				cout << endl << " <---------- WIN ----------> " << endl;
				gracze[queue].alterMoney(gracze[queue].getPlayer_Wallet() + gracze[queue].getPlayer_Money());
				break;
			}
			else {
				queue = (queue + 1) % 3;
				sum = 1;
				cout << endl << " <---------- WRONG GUESS ----------> " << endl;
				continue;
			}
		}
		else {
			result = "";
			rng = rand() % 15;
			if (board[rng] == 0) {
				result = "Turn Loss";
			}
			if (board[rng] == -1) {
				result = "Bankrupt";
			}
			if (result != "") {
				cout << "\033[1;31m" << result << "\033[0m" << endl;
			}
			else {
				cout << "\033[1;34m" << board[rng] << "\033[0m" << endl;
				amount = board[rng];
			}

			if ((board[rng] == 0) || (board[rng] == -1)) {
				if (board[rng] == -1) {
					gracze[queue].alterMoney(0);
				}
				queue = (queue + 1) % 3;
				sum = 1;
				cout << endl << "<------------------------------>" << endl;
				continue;
			}
			cout << gracze[queue].getPlayer_Name() << ": Pass the letter" << endl;
			singleLetter = GameMaster::LoadChar();
			guessed = 0;
			if (GameMaster::isVowel(singleLetter)) {
				cout << "Vowel";
			}
			else {
				cout << "Consonant";
			}
		}
		cout << endl;
		for (int i = 0; i < mainCrossword.size(); i++) {
			if ((mainCrossword[i] == singleLetter) && (mask[i] == 1)) {
				mask[i] = 0;
				guessed++;
			}
		}
		if (guessed) {
			cout << "You guessed right";
			gracze[queue].alterMoney(gracze[queue].getPlayer_Money() + amount * guessed);

			cout << endl << gracze[queue].getPlayer_Name() << "\033[1;32m " << gracze[queue].getPlayer_Money() << "\033[0m";
		}
		else {
			cout << "You guessed wrong";
			queue = (queue + 1) % 3;
			cout << "<------------------------------>" << endl;
			sum = 1;
			continue;
		}
		cout << endl;

		sum = 0;
		for (int i = 0; i < mainCrossword.size(); i++) {
			sum += mask[i];
		}
		amount = 0;
	} while (sum);

	//sort(gracze.begin(), gracze.end(), comparePlayers);
	for (auto t : gracze) {
		cout << &t;
	}
	exit(0);
}


void GameMaster::printPlayers_CC(int queue){
	cout << "\n";
	for (int i = 0; i < 3; i++) {
		if (i == queue) {
			cout << "\033[1;34m";
		}
		cout << &gracze[i];
		cout << "\033[0m";
	}
	cout << "\n";
}

void GameMaster::getCrosswordsFF() {
	ifstream crossin;
	crossin.open("dane.txt");
	while (!crossin.eof()) {
		string words;
		getline(crossin, words);
		crosswords.push_back(words);
	}
	crossin.close();
}

void GameMaster::crosswordRNGmask() {
	for (string words : crosswords) {
		cout << words << endl;
	}
	assert(crosswords.size() > 0);
	int j = rand() % crosswords.size();
	mainCrossword = crosswords[j];
	int n = mainCrossword.size();

	for (int i = 0; i < n; i++) {
		if (mainCrossword[i] == ' ') {
			mask[i] = 0;
		}
		else {
			mask[i] = 1;
		}
	}
}

void GameMaster::printCrossMask() {
	cout << "\033[47m" << "\033[31m";
	for (int i = 0; i < mainCrossword.size(); i++) {
		if (mask[i] == 1) {
			cout << "*";
		}
		else {
			cout << mainCrossword[i];
		}
	}
	cout << "\033[0m";
	cout << endl;
}

int GameMaster::isVowel(char c) {
	if (c == ("a" || "e" || "i" || "o" || "u" || "y" || "A" || "E" || "I" || "O" || "U" || "Y")) {
		return 1;
	}
	else {
		return 0;
	}
}

char GameMaster::LoadChar() {
	string letter;
	cin >> letter;
	while (letter.size() != 1) {
		cout << endl << "Please type a single letter and press <Enter>" << endl;
		cin >> letter;
	}

	for (auto& c : letter) {
		c = toupper(c);
	}
	return letter[0];
}

char GameMaster::LoadChoice() {
	char choice;
	choice = GameMaster::LoadChar();
	while (choice != '1' && choice != '2') {
		cout << endl << "Choose [1-2]:\n";
		cin >> choice;
	}
	return choice;
}

