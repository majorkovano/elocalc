#include "elostore.h"
#include "common.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void intdir(const string& dir){ fs::create_directory(dir);
	ofstream f(dir+"/.eloflag");
	f << "ELOSTORE DIRECTORY";
	f.close();
	fs::create_directories(dir+"/history");
	fs::create_directories(dir+"/players");
	cout << "Elostore initialized" << endl;
}

void playeradd(queue<string>& players){
	while (!players.empty()){
		ofstream pf;
		if (!(fs::exists(elostore+"/history/"+players.front()))){
			pf.open(elostore+"/history/"+players.front(), ios::app);
			pf << "1000\n";
			pf.close();
		}

		if(!(fs::exists(elostore+"/players/"+players.front()))){
			pf.open(elostore+"/players/"+players.front(), ios::app);
			pf << "1000\n";
			pf.close();
		}

		players.pop();
	}
}

void checkelo(){
	cout << "Enter the name of the player: ";
	string name;
	//cin >> name;
	getline(cin >> ws,name,'\n');
	deltrailspace(name);
	cout << endl;
	if (fs::exists(elostore+"/players/"+name)) {
			ifstream f(elostore+"/players/"+name);
			string rating;
			getline(f,rating);
			f.close();
			cout << name+"'s rating: "+rating+"\n" ;
	}
	else cout << "Player "+name+" doesn't exist\n";
}
