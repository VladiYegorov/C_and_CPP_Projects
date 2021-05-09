#include "Player.h"

Player::Player(int id, int budget) {
	this->id = id;
	this->budget = budget;
}

void Player::setBudget(int newBudget) {
	budget = newBudget;
}

void Player::setBet(int newBet) {
	bet = newBet;
}

void Player::setStatus(Status newStatus) {
	currentState = newStatus;
}

int Player::getId() const {
	return id;
}

CardDeck& Player::getHand() {
	return hand;
}

Player::Status Player::getStatus() const {
	return currentState;
}

int Player::getBet() const {
	return bet;
}

int Player::getBudget() const {
	return budget;
}

Player& Player::operator+=(int increaseBudget) {
	budget += increaseBudget;
	return *this;
}

Player& Player::operator-=(int decreaseBudget) {
	budget -= decreaseBudget;
	return *this;
}

void Player::hit(CardDeck& deck) {
	Card newCard = deck.draw();
	hand += newCard;
	if(hand.value() > 21) {
		setStatus(LOSS);
	}
}

void Player::preparePlayerNewRound() {
	setStatus(HIT);
	hand.clear();
}


