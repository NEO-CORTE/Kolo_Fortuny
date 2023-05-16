#pragma once
#include <iostream>
using namespace std;
class wheel
{
private: 
	int values[16] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
public:
	friend ostream& operator << (ostream& os, const wheel& kolo) {
		cout << "Values on the Wheel: " << endl;
		for (auto& t : kolo.values) {
			if (t == -1) {
				cout << "Bankrupt" << endl;
			}
			else if (t == 0) {
				cout << "Skip" << endl;
			}
			else {
				cout << t << endl;
			}
			cout << endl;
			
		}
		return os;
	}
	int* getWheel();
};