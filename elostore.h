#include <string>
#include <queue>
#ifndef ELOSTORE
#define ELOSTORE


extern std::string elostore;

// initialize an elostore directory
void intdir(const std::string& dir);

// add a new player's history and current rating files
void playeradd(std::queue<std::string>& players);

// check a players current elo rating
void checkelo();

#endif
