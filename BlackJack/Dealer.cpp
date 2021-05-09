#include "Dealer.h"

Dealer::Dealer() : Casino(0,0) {
}

void Dealer::preparePlayerNewRound() {
	setStatus(HIT);
	hand.clear();
	hiddenCard = Card();
}


Card& Dealer::getHiddenCard(){
	return this->hiddenCard;
}

void Dealer::addHiddenCard(const Card& card) {
	hiddenCard = card;
}
