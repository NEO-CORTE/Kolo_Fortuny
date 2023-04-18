#include "Player.h"

// Alter the name of player
void Player::alterName(string n) {
	name = n;
}

// Alters the wallet value
void Player::alterWallet(int m) {
	wallet = m;
}

// Alters the money value
void Player::alterMoney(int m) {
	money = m;
}

// Retrives player name
string Player::getPlayer_Name() {
	return name;
}

// Retrieves player wallet value
int Player::getPlayer_Wallet() {
	return wallet;
}

// Retrieves player money value
int Player::getPlayer_Money() {
	return money;
}