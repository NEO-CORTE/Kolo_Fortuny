#include "GameMaster.h"
void GameMaster::GameControl() {
	srand(time(NULL));
	GameMaster::getCrosswordsFF();
	players[0].alterName("Player 1");
	players[1].alterName("Player 2");
	players[2].alterName("Player 3");
	string crossword, trial, result;
	char singleLetter, choice;
	int sum = 0, guessed = 0, are_consonants = 0, amount = 0, queue = 0;
	wheel tmpWheel;
	int* board = tmpWheel.getWheel();
	GameMaster::crosswordRNGmask();


	do {
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
				players[queue].alterMoney(players[queue].getPlayer_Wallet() + players[queue].getPlayer_Money());
				break;
			}
			else {
				queue = (queue + 1) % 3;
				sum = 1;
				cout << endl << " <---------- WRONG GUESS ----------> " << endl;
				continue;
			}
			result = "";
			int rng = rand() % 15;
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

			if (board[rng] == (0 || -1)) {
				if (board[rng] == -1) {
					players[queue].alterMoney(0);
				}
				queue = (queue + 1) % 3;
				sum = 1;
				cout << endl << "<------------------------------>" << endl;
				continue;
			}
			cout << players[queue].getPlayer_Name() << ": Pass the letter" << endl;
			singleLetter = GameMaster::LoadChar();
			guessed = 0;
			if (GameMaster::isVowel(singleLetter)) {
				cout << "Vowel";
			}
			else {
				cout << "Consonant";
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
				players[queue].alterMoney(players->getPlayer_Money() + amount * guessed);

				cout << endl << players[queue].getPlayer_Name() << "\033[1;32m " << players[queue].getPlayer_Money() << "\033[0m";
			}
			else {
				cout << "You guessed wrond";
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
		}

	} while (sum);

	cout << "Well Done";
	exit(0);
}

void GameMaster::printPlayers_CC(int queue){
	cout << "\n";
	for (int i = 0; i < 3; i++) {
		if (i == queue) {
			cout << "\033[1;34m";
		}
		cout << players[i].getPlayer_Name() << "\t" << players[i].getPlayer_Money() << "\n";
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

