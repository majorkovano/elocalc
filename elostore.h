#ifndef	ELOCALC
#define ELOCALC

#include <string>
#include <queue>

class elostore {
	//extern float Ra, Rb; // rating of players (a, b)
	const int K = 32; // elo calculation parameter

	// Function to calculate the Probability
	float Probability(const int& , const int& );

	// Function to calculate Elo rating
	// K is a constant(maximum elo increase).
	void EloRating(float & , float & );

	public:

	std::string store;

	elostore ();
	elostore (std::string);

	void calculate (const std::string & , const std::string & );

	// create the elostore directory
	void intdir ();

	// add a new player's history and current rating files
	void playeradd (std::queue<std::string>& );

	// check a players current elo rating
	std::string checkelo (const std::string &);
};

#endif
