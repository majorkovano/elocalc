#include "calc.h"
#include "common.h"
#include "elostore.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

float Probability(const int& rating1,const int& rating2) {
 	return 1.0 * 1.0 / (1 + 1.0 *
	pow(10, 1.0 * (rating1 - rating2) / 400));
}

void EloRating(){

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

void calculator() {
 	// determining players
	string playername_win, playername_lose;
	cout << "Winner alias: ";
	//cin >> playername_win;
	getline(cin >> ws,playername_win,'\n');
	deltrailspace(playername_win);
	cout << "Loser alias: ";
	//  cin >> playername_lose;
	getline(cin >> ws, playername_lose,'\n');
	deltrailspace(playername_lose);

	// opening player's files
	fstream W;
	W.open (elostore+"/players/"+playername_win);
	fstream L;
	L.open (elostore+"/players/"+playername_lose);

	// getting elo score
	string line;
	getline(L,line);
	Rb=stof(line);
	getline(W,line);
	Ra=stof(line);
	float Oa=Ra;
	float Ob=Rb;
	cout << "\nOld Ratings:\n";
	cout << "Winner: " << Oa << "\n" << "Loser: " << Ob << "\n";

	//calculating elo
 	EloRating();
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
