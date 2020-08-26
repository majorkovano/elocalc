#include <iostream>
#include <filesystem>
#include <queue>

#include "calc.h"
#include "elostore.h"
#include "ui.h"
#include "common.h"

using namespace std;
namespace fs = std::filesystem;

float Ra,Rb;
string elostore;

int main(){
	//determine location of elostore directory
	while (!fs::exists(elostore) || !fs::exists(elostore+"/.eloflag")){
		cout << "Enter a valid path to an existing or new \"elostore\" directory: ";
		cin >> elostore;
		cout << endl;
		if (!fs::exists(elostore) || !fs::exists(elostore+"/.eloflag")){
			cout << "Would you like to create and/or "
				"initialize " + elostore + " as a \"elostore\" directory? [y/N] ";
			string a;
			getline(cin >> ws,a,'\n');
			deltrailspace(a);
			//cin >> a;
			if (a=="y" || a =="Y") intdir(elostore);
		}

	}

	//main program
	int option;
	option = optsel();
	while (!(option == 4)) {
		if (option == 1){
			queue<string> players;

			cout << "Enter names/alises of all players you whish to enter into "
				"\"elostore\" " + elostore + " (comma separated):\n";

			string inp;
			getline(cin >> ws,inp,'\n');

			unsigned long i = 0;
			string player;
			bool inname;
			while (i < inp.size()){
				player = "";
				inname=false;
				while (inp[i]!=',' && i < inp.size()){
					if (!(isspace(inp[i])) || inname) {
						player+=inp[i];
						inname=true;
					}
					i++;
				}
				i++;
				players.push(player);
			}

			playeradd(players);
		}
		else if (option == 2) calculator();
		else if (option == 3) checkelo();

		option = optsel();
	}

	return 0;
}
