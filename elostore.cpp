#include <cmath>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "elostore.h"

using namespace std;

elostore::elostore (std::string league) {
	store=league;
}

elostore::elostore (){
	store="";
}


float elostore::Probability (const int& rating1,const int& rating2) {
 	return 1.0 * 1.0 / (1 + 1.0 *
	pow(10, 1.0 * (rating1 - rating2) / 400));
}

void elostore::EloRating (float & Ra, float & Rb){

 	// To calculate the Winning
	// Probability of Player B
 	float Pb = Probability(Ra, Rb);

 	// To calculate the Winning
	// Probability of Player A
 	float Pa = Probability(Rb, Ra);

 	// Updating the Elo Ratings
	Ra = Ra + K * (1 - Pa);
	Rb = Rb + K * (0 - Pb);

	// Print results
	cout << "\nUpdated Ratings:\n";
 	cout << "Winner: " << Ra << "\n" << "Loser: " << Rb << "\n";
}

void elostore::calculate (const string & playername_win, const string & playername_lose) {
	// opening player's files
	fstream W;
	W.open (store+"/players/"+playername_win);
	fstream L;
	L.open (store+"/players/"+playername_lose);

	// getting elo score
	string line;
	getline(L,line);
	float Rb=stof(line);
	getline(W,line);
	float Ra=stof(line);

	//calculating elo
 	EloRating(Ra,Rb);

	//saving new elo
	W.seekp(0, ios::beg);
	L.seekp(0, ios::beg);
	W << to_string(Ra);
	L << to_string(Rb);
	W.close();
	L.close();

	//saving to history
	W.open (store+"/history/"+playername_win, ios::app);
	L.open (store+"/history/"+playername_lose, ios::app);
	W << to_string(Ra) << "\n";
	L << to_string(Rb) << "\n";
	W.close();
	L.close();
}

namespace fs = std::filesystem;

void elostore::intdir(){
	fs::create_directory(store);
	ofstream f(store+"/.eloflag");
	f << "ELOSTORE DIRECTORY";
	f.close();
	fs::create_directories(store+"/history");
	fs::create_directories(store+"/players");
}

void elostore::playeradd(queue<string>& players){
	while (!players.empty()){
		ofstream pf;
		if (!(fs::exists(store+"/history/"+players.front()))){
			pf.open(store+"/history/"+players.front(), ios::app);
			pf << "1000\n";
			pf.close();
		}

		if(!(fs::exists(store+"/players/"+players.front()))){
			pf.open(store+"/players/"+players.front(), ios::app);
			pf << "1000\n";
			pf.close();
		}

		players.pop();
	}
}

string elostore::checkelo(const string & name){
	ifstream f(store+"/players/"+name);
	string rating;
	getline(f,rating);
	f.close();
	return rating;
}
