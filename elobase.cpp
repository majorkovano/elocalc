#include "elobase.h"
#include <cmath>
#include <iostream>

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
