#include "Casino.h"

Casino::Casino(int id,int budget) : Player(id,budget) {
	this->bet = 1;
}

bool Casino::checkToHit(int dealerValue) const {
	if(getStatus() == STAND || getStatus() == BJ || getStatus() == LOSS) {
		return false;
	}
	if(hand.value() >= 17) {
		return false;
	}
	return true;
}

void Casino::updateBetAfterWin() {
	this->setBet(1);
}
void Casino::updateBetAfterLoss() {
	this->setBet(bet*2);
}

void Casino::setBetAfterLeave() {
	setBet(1);
}
