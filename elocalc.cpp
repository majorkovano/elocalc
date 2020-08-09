// CPP program for Elo Rating
#include <iostream>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <queue>
using namespace std;
namespace fs = std::filesystem;


string elostore;
float Ra, Rb;


// Function to calculate the Probability
float Probability(int rating1, int rating2) {
 	return 1.0 * 1.0 / (1 + 1.0 *
	pow(10, 1.0 * (rating1 - rating2) / 400));
}

// Function to calculate Elo rating
// K is a constant(maximum elo increase).
// d determines whether Player A wins or Player B.
void EloRating(int K, bool d){
 	// To calculate the Winning
	// Probability of Player B
 	float Pb = Probability(Ra, Rb);
 	// To calculate the Winning
	// Probability of Player A
 	float Pa = Probability(Rb, Ra);
 	// Case -1 When Player A wins
 	// Updating the Elo Ratings
	if (d == 1) {
	Ra = Ra + K * (1 - Pa);
	Rb = Rb + K * (0 - Pb);
	}
 	// Case -2 When Player B wins
	// Updating the Elo Ratings
	else {
	Ra = Ra + K * (0 - Pa);
	Rb = Rb + K * (1 - Pb);
	}
	cout << "\nUpdated Ratings:\n";
 	cout << "Winner: " << Ra << "\n" << "Loser: " << Rb << "\n";
}

void calculator() {
 	//determining players
	string playername_win, playername_lose;
	cout << "Winner alias: ";
	cin >> playername_win;
	cout << "Loser alias: ";
	cin >> playername_lose;

	//opening player's files
	fstream W;
	W.open (elostore+"/players/"+playername_win);
	fstream L;
	L.open (elostore+"/players/"+playername_lose);

	//getting elo score
	string line;
	getline(L,line);
	Rb=stof(line);
	getline(W,line);
	Ra=stof(line);
	float Oa=Ra;
	float Ob=Rb;
	cout << "\nOld Ratings:\n";
	cout << "Winner: " << Oa << "\n" << "Loser: " << Ob << "\n";

	//elo calculation parameters
	int K = 32;
	bool d = 1;

	//calculating elo
 	EloRating(K, d);
	cout << "\nDifference:\n";
	cout << "Winner: " << Ra-Oa << "\n" << "Loser: " << Rb-Ob << "\n";

	//saving new elo
	W.seekp(0, ios::beg);
	L.seekp(0, ios::beg);
	W << to_string(Ra);
	L << to_string(Rb);
	W.close();
	L.close();

	//saving to history
	W.open (elostore+"/history/"+playername_win, ios::app);
	L.open (elostore+"/history/"+playername_lose, ios::app);
	W << to_string(Ra) << "\n";
	L << to_string(Rb) << "\n";
	W.close();
	L.close();
}

void intdir(string dir){
	fs::create_directory(dir);
	ofstream f(dir+"/.eloflag");
	f << "ELOSTORE DIRECTORY";
	f.close();
	fs::create_directories(dir+"/history");
	fs::create_directories(dir+"/players");
	cout << "Elostore initialized" << endl;
}

int optsel(){
	cout << endl << "Select option:\n"
		"1) add player\n"
		"2) calculate new elo rating\n"
		"3) check a player's elo\n"
		"4) exit\n"
		"Option: ";
	int opt;
	while (!(cin >> opt) || (opt > 4) || (opt < 1)) {
		string in;
		cout << "Invalid option: " << in << "\n"
			"Option: ";
	}
	cout << endl;
	return opt;
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
	cin >> name;
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
			cin >> a;
			if (a=="y" || a =="Y") intdir(elostore);
		}

	}

	//main program
	int option;
	option = optsel();
	while (!(option == 4)) {
		if (option == 1){
			static queue<string> players;
			static string player;
			cout << "Enter names/alises of all players you whish to enter into "
				"\"elostore\" " + elostore + " (comma separated):\n";
			string inp;
			cin >> inp;
			unsigned long i = 0;
			while (i < inp.size()){
				string player;
				while (inp[i]!=',' && i < inp.size()){
					player+=inp[i];
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

}
