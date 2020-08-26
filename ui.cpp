#include "ui.h"
#include <iostream>

using namespace std;

int optsel(){
	cout << endl << "Select option:\n"
		"1) add player\n"
		"2) calculate new elo rating\n"
		"3) check a player's elo\n"
		"4) exit\n"
		"Option: ";
	int opt;
	string inp;

	getline(cin >> ws,inp,'\n');
	try {
		opt=stoi(inp);

	} catch(invalid_argument e) {
		cout << "Invalid option: " << inp << "\n";
	}

	if ((opt > 4) || (opt < 1)) {
		cout << "Invalid option: " << opt << "\n";
	}

	cout << endl;
	return opt;
}
