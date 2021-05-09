#ifndef BLACK_JACK_H
#define BLACK_JACK_H

#include <vector>
#include <map>
#include <utility> 

#include "CardDeck.h"
#include "Player.h"
#include "Casino.h"
#include "Calculated.h"
#include "Dealer.h"
#include "Exceptions.h"

#define BJ_WIN 1.5
#define BJ_VALUE 21

struct classcomp {
  bool operator() (int p1,int p2) const {
	 if(p1 < p2) {
	  	return true;
	  }
	  return false;
  }
};

using std::vector;

typedef std::map<int, Player*,classcomp> playerMap;
typedef std::pair<int, Player*> playerPair;
typedef playerMap::iterator playerMapIter;
typedef playerMap::const_iterator constPlayerMapIter;

class BlackJack {
private:
	CardDeck playDeck;
	playerMap players;
	vector <Player*> playersInGame;
	Dealer dealer;
public:
	enum PlayerStrategy { CASINO, CALCULATED };
	
	BlackJack(const CardDeck& deck);
	~BlackJack();

	void addPlayer(int id, PlayerStrategy strategy, int budget);
	void joinGame(int player);
	void joinGame(const vector<int>& players);
	void leaveGame(int player);
	void leaveGame(const vector<int>& players);
	void playRound();

	void reloadDeck(const CardDeck& newDeck);

	int getBalance(int id) const;
	int getRichest() const;

	void initializeRound();
	void addCardToPlayers();
	void dealerHaveBJ() const;
	bool onlyBjAndLoss() const;
	bool playersFinishedRound() const;
	void updatePlayersStatus();
	void endRound();
};

#endif // BLACK_JACK_H

