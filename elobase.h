#ifndef ELOBASE
#define ELOBASE

extern float Ra, Rb; // rating of players (a, b)
const int K = 32; // elo calculation parameter

// Function to calculate the Probability
float Probability(const int& rating1, const int& rating2);

// Function to calculate Elo rating
// K is a constant(maximum elo increase).
// d determines whether Player A wins or Player B.
void EloRating();

#endif
