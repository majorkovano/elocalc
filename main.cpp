#include <iostream>
#include <filesystem>
#include <queue>

#include "elostore.h"

using namespace std;
namespace fs = std::filesystem;

int optsel(){
	cout << endl << "Select option:\n"
		"1) add player\n"
		"2) calculate new elo rating\n"
		"3) check a player's elo\n"
		"4) exit\n"
		"Option: ";
	int opt;
	string inp;
	bool tag=false;

	getline(cin >> ws,inp,'\n');
	try {
		opt=stoi(inp);

	} catch(invalid_argument e) {
		cout << "Invalid option: " << inp << "\n";
		tag=true;
	}

	if (((opt > 4) || (opt < 1)) && !tag) {
		cout << "Invalid option: " << opt << "\n";
	}

	cout << endl;
	return opt;
}

void deltrailspace(string& str){
	int i = 0;
	string nstr;
	while (i != str.size() && !isspace(str[i])){
		nstr+=str[i];
		i++;
	}
	str = nstr;
 }

int main(){
	//determine location of elostore directory
	elostore league;

	while (!fs::exists(league.store) || !fs::exists(league.store+"/.eloflag")){
		cout << "Enter a valid path to an existing or new \"elostore\" directory: ";
		cin >> league.store;
		cout << endl;
		if (!fs::exists(league.store) || !fs::exists(league.store+"/.eloflag")){
			cout << "Would you like to create and/or "
				"initialize " + league.store + " as a \"elostore\" directory? [y/N] ";
			string a;
			getline(cin >> ws,a,'\n');
			deltrailspace(a);
			//cin >> a;
			if (a=="y" || a =="Y") league.intdir();
		}

	}

	//main program
	int option;
	option = optsel();
	while (!(option == 4)) {
		if (option == 1){
			queue<string> players;

			cout << "Enter names/alises of all players you whish to enter into "
				"\"elostore\" " + league.store + " (comma separated):\n";

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
				cout << "\""+player+"\""<<endl;
				players.push(player);
			}

			league.playeradd(players);
		}
		else if (option == 2) {
			//determining players
			string playername_win, playername_lose;
			cout << "Winner alias: ";
			getline(cin >> ws,playername_win,'\n');
			deltrailspace(playername_win);
			cout << "Loser alias: ";
			getline(cin >> ws, playername_lose,'\n');
			deltrailspace(playername_lose);

			league.calculate(playername_win, playername_lose);
		}
		else if (option == 3) {
			cout << "Enter the name of the player: ";
			string name;
			getline(cin >> ws,name,'\n');
			deltrailspace(name);
			cout << endl;
			if (fs::exists(league.store+"/players/"+name))
				cout << name+"'s rating: "+league.checkelo(name)+"\n" ;
			else cout << "Player "+name+" doesn't exist\n";
		}

		option = optsel();
	}

	return 0;
}
