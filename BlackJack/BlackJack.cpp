#include "BlackJack.h"

using blackJack::PlayerAlreadytExistException;
using blackJack::PlayerDoesNotExistException;
using blackJack::NotEnoughCardsException;
using blackJack::NoPlayersException;

static bool checkBJ(const CardDeck& twoCardDeck){
	if(twoCardDeck.appearsOfAces() == 1) {
		if(twoCardDeck.value() == BJ_VALUE) {
			return true;
		}
	}
	return false;
}

static void checkBJ(const vector<Player*>& players) {
	for(unsigned int i=0;i<players.size(); i++) {
		Player* tempPlayer = players[i];
		if(checkBJ(tempPlayer->getHand())) {
			tempPlayer->setStatus(Player::BJ);
		}
	}
}

static bool checkBJ(const CardDeck& deck1,const CardDeck& deck2){
	CardDeck newDeck(deck1);
	newDeck += deck2;
	return checkBJ(newDeck);
}

//////////////////////////////////////////////////////////////////////////////

BlackJack::BlackJack(const CardDeck& deck){
	this->playDeck = deck;
}

BlackJack::~BlackJack() {
	playerMapIter it = players.begin();
	for(;it != players.end(); it++) {
		Player* tempPlayer = (*it).second;
		delete tempPlayer;
	}
}

void BlackJack::addPlayer(int id, PlayerStrategy strategy, int budget) {
	if(players.find(id) != players.end()) {
		throw PlayerAlreadytExistException();
	}
	if(strategy == CASINO) {
		Player* player = new Casino(id,budget);
		players.insert({player->getId(),player});
		return;
	}
	if(strategy == CALCULATED) {
		Player* player = new Calculated(id,budget);
		players.insert({player->getId(),player});
		return;
	}
}

void BlackJack::joinGame(int player) {
	if(players.find(player) == players.end()) {
		throw PlayerDoesNotExistException();
	}
	for(unsigned int i=0; i<playersInGame.size();i++) {
		Player* temp = playersInGame[i];
		if(temp->getId() == player) {
			return;
		}
	}
	Player* insertPlayer = players[player];
	playersInGame.push_back(insertPlayer);
}

void BlackJack::joinGame(const vector<int>& players) {
	for(unsigned int i=0; i< players.size();i++) {
		int id = players[i];
		if(this->players.find(id) == this->players.end()) {
			throw PlayerDoesNotExistException();
		}
	}
	for(unsigned int i=0; i< players.size();i++) {
		int id = players[i];
		joinGame(id);
	}
}

void BlackJack::leaveGame(int player) {
	if(players.find(player) == players.end()) {
		throw PlayerDoesNotExistException();
	}
	vector<Player*>::iterator iter;
	for(iter=playersInGame.begin() ; iter != playersInGame.end(); iter++) {
		Player* tempPlayer = *iter;
		if(tempPlayer->getId() == player) {
			tempPlayer->setBetAfterLeave();
			playersInGame.erase(iter);
			return;
		}
	}
	return;
}

void BlackJack::leaveGame(const vector<int>& players){
	for(unsigned int i=0; i< players.size();i++) {
		int id = players[i];
		if(this->players.find(id) == this->players.end()) {
			throw PlayerDoesNotExistException();
		}
	}
	for(unsigned int i=0; i< players.size();i++) {
		int id = players[i];
		leaveGame(id);
	}
}

void BlackJack::playRound() {
	initializeRound();
	if(playersInGame.size() == 0) {
		return;
	}
	addCardToPlayers();
	dealer.getHand() += playDeck.draw();
	addCardToPlayers();
	dealer.addHiddenCard(playDeck.draw());
	checkBJ(playersInGame);
	if(checkBJ(dealer.getHand(), dealer.getHiddenCard())) {
		dealer.getHand() += dealer.getHiddenCard();
		dealer.setStatus(Player::BJ);
		dealerHaveBJ();
		endRound();
		return;
	}
	while(!playersFinishedRound()) {
		for(unsigned int i=0;i<playersInGame.size(); i++) {
			Player* tempPlayer = playersInGame[i];
			if(tempPlayer->checkToHit(dealer.getHand().value())) {
				tempPlayer->hit(playDeck);
			} else { if(tempPlayer->getStatus() != Player::BJ &&
						tempPlayer->getStatus() != Player::LOSS) {
					tempPlayer->setStatus(Player::STAND);
				}
			}
		}
	}
	if(onlyBjAndLoss()) {
		endRound();
		return;
	}
	dealer.getHand() += dealer.getHiddenCard();
	while(dealer.checkToHit(dealer.getHand().value())) {
		dealer.hit(playDeck);
	}
	updatePlayersStatus();
	endRound();
}

void BlackJack::reloadDeck(const CardDeck& newDeck) {
	playDeck = newDeck;
}

int BlackJack::getBalance(int id) const {
	constPlayerMapIter it = players.find(id);
	if(it == players.end()) {
		throw PlayerDoesNotExistException();
	}
	return (*it).second->getBudget();
}

int BlackJack::getRichest() const{
	if(players.size() == 0) {
		throw NoPlayersException();
	}
	constPlayerMapIter it = players.begin();
	int max = (*it).second->getBudget();
	int maxId = (*it).second->getId();
	for(; it != players.end(); it++) {
		Player* tempPlayer = (*it).second;
		if(tempPlayer->getBudget() > max) {
			max = tempPlayer->getBudget();
			maxId = tempPlayer->getId();
		}
		if(tempPlayer->getBudget() == max) {
			if(tempPlayer->getId() < maxId) {
				maxId = tempPlayer->getId();
			}
		}
	}
	return maxId;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////

void BlackJack::initializeRound() {
	if(playDeck.size() < NUM_OF_SUITS * NUM_OF_VALUES) {
		throw NotEnoughCardsException();
	}
	CardDeck full = CardDeck::getFullDeck();
	if(!(full <= playDeck)) {
		throw NotEnoughCardsException();
	}
	for(unsigned int i=0;i<playersInGame.size(); i++) {
		Player* tempPlayer = playersInGame[i];
		tempPlayer->preparePlayerNewRound();
	}
	dealer.preparePlayerNewRound();
}

void BlackJack::addCardToPlayers() {
	for(unsigned int i=0;i<playersInGame.size(); i++) {
		Player* tempPlayer = playersInGame[i];
		tempPlayer->getHand() += playDeck.draw();
	}
}

void BlackJack::dealerHaveBJ() const {
	for(unsigned int i=0;i<playersInGame.size();i++) {
		Player* tempPlayer = playersInGame[i];
		if(tempPlayer->getStatus() == Player::BJ) {
			tempPlayer->setStatus(Player::DRAW);
		} else {
			tempPlayer->setStatus(Player::LOSS);
		}
	}
}

bool BlackJack::onlyBjAndLoss() const {
	for(unsigned int i=0;i<playersInGame.size(); i++) {
		Player* tempPlayer = playersInGame[i];
		if(tempPlayer->getStatus() != Player::BJ &&
			tempPlayer->getStatus() != Player::LOSS) {
			return false;
		}
	}
	return true;
}

bool BlackJack::playersFinishedRound() const {
	for(unsigned int i=0;i<playersInGame.size(); i++) {
		Player* tempPlayer = playersInGame[i];
		if(tempPlayer->getStatus() == Player::HIT) {
			return false;
		}
	}
	return true;
}

void BlackJack::updatePlayersStatus() {
	unsigned int dealerValue = dealer.getHand().value();
	for(unsigned int i=0;i<playersInGame.size(); i++) {
		Player* tempPlayer = playersInGame[i];
		if(tempPlayer->getStatus() == Player::STAND) {
			if(dealer.getStatus() == Player::LOSS) {
				tempPlayer->setStatus(Player::WIN);
				continue;
			}
			if(tempPlayer->getHand().value() == dealerValue) {
				tempPlayer->setStatus(Player::DRAW);
			}
			if(tempPlayer->getHand().value() > dealerValue) {
				tempPlayer->setStatus(Player::WIN);
			}
			if(tempPlayer->getHand().value() < dealerValue) {
				tempPlayer->setStatus(Player::LOSS);
			}
		}
	}
}


void BlackJack::endRound() {
	for(unsigned int i=0;i<playersInGame.size(); i++) {
		Player* tempPlayer = playersInGame[i];
		Player::Status tempStatus = tempPlayer->getStatus();
		switch(tempStatus) {
			case Player::BJ:	*tempPlayer += (tempPlayer->getBet() * BJ_WIN);
								tempPlayer->updateBetAfterWin(); break;
			case Player::DRAW:	break;
			case Player::WIN:	*tempPlayer += tempPlayer->getBet();
								tempPlayer->updateBetAfterWin(); break;
			case Player::LOSS:	*tempPlayer -= tempPlayer->getBet();
								tempPlayer->updateBetAfterLoss(); break;
			default:			break;
		}
	}
}


