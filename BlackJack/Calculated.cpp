#include "Calculated.h"

Calculated::Calculated(int id,int budget) : Player(id,budget) {
	this->bet = 20;
}

bool Calculated::checkToHit(int dealerValue) const {
	if(getStatus() == STAND || getStatus() == BJ) {
		return false;
	}
	CardDeck tempOriginalDeck(hand);
	CardDeck tempNewDeck;
	for(unsigned int i=0;i<hand.size();i++) {
		Card tempCard = tempOriginalDeck.draw();
		if(tempCard.getValue() != 1) {
			tempNewDeck += tempCard;
		}
	}
	if(tempNewDeck.value() + hand.appearsOfAces() != hand.value()) {
		if(hand.value() < 18) {
			return true;
		}
		if(hand.value() == 18) {
			if(dealerValue != 2 && dealerValue != 7 && dealerValue != 8) {
				return true;
			}
		}
		return false;
	}
	if(hand.value() < 12) {
		return true;
	}
	if(hand.value() == 12) {
		if(dealerValue != 4 && dealerValue != 5 && dealerValue != 6) {
			return true;
		}
	}
	if(hand.value() >= 13 && hand.value() <=16) {
		if(dealerValue >=2 && dealerValue <=6) {
			return false;
		}
	}
	return false;
}

void Calculated::updateBetAfterWin() {
	this->setBet(bet+1);
}
void Calculated::updateBetAfterLoss() {
	if(bet-1 == 0) {
		return;
	}
	this->setBet(bet-1);
}

void Calculated::setBetAfterLeave() {
	return;
}
