// CPP program for Elo Rating
 #include <bits/stdc++.h>
 using namespace std; 

// Function to calculate the Probability 
float Probability(int rating1, int rating2) {
 	return 1.0 * 1.0 / (1 + 1.0 * 
	pow(10, 1.0 * (rating1 - rating2) / 400)); 
}

// Function to calculate Elo rating 
// K is a constant(maximum elo increase). 
// d determines whether Player A wins or Player B.
float Ra, Rb; 
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
int main() {
 	//determining players
	string playername_win, playername_lose;
	cout << "Winner alias: ";
	cin >> playername_win;
	cout << "Loser alias: ";
	cin >> playername_lose;
	
	//opening player's files
	fstream W; 
	W.open ("/home/luka/d/pingač/players/"+playername_win);
	fstream L;
	L.open ("/home/luka/d/pingač/players/"+playername_lose);

	//getting elo score
	string line;	
	getline(L,line);
	Rb=stof(line);
	getline(W,line);
	Ra=stof(line);
	W.close();
	L.close();
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
	W.open ("/home/luka/d/pingač/players/"+playername_win);
	L.open ("/home/luka/d/pingač/players/"+playername_lose);
	W.seekp(0, ios::beg);
	L.seekp(0, ios::beg);
	W << to_string(Ra);
	L << to_string(Rb);
	W.close();
	L.close();

	//saving to history 
	W.open ("/home/luka/d/pingač/history/"+playername_win, ios::app);
	L.open ("/home/luka/d/pingač/history/"+playername_lose, ios::app);
	W << to_string(Ra) << "\n";
	L << to_string(Rb) << "\n";
	W.close();
	L.close();

	return 0;
 } 
