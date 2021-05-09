#ifndef PLAYER_H_
#define PLAYER_H_

#include "CardDeck.h"

class Player {
public:
	enum Status {BJ, WIN, LOSS, DRAW, HIT, STAND};
protected:
	unsigned int id;
	int budget;
	unsigned int bet = 0;
	CardDeck hand;
	Status currentState = HIT;
public:
	Player() = delete;
	Player(int id, int budget);
	Player(const Player& player) = delete;
	Player& operator=(const Player& player) = delete;
	virtual ~Player() = default;

	void setBudget(int newBudget);
	void setBet(int newBet);
	void setStatus(Status newStatus);
	int getId() const;
	CardDeck& getHand();
	Status getStatus() const;
	int getBet() const;
	int getBudget() const;

	void hit(CardDeck& deck);
	void preparePlayerNewRound();
	virtual bool checkToHit(int dealerValue) const = 0;
	virtual void updateBetAfterWin() = 0;
	virtual void updateBetAfterLoss() = 0;
	virtual void setBetAfterLeave() = 0;

	Player& operator+=(int increaseBudget);
	Player& operator-=(int decreaseBudget);
};


#endif /* PLAYER_H_ */
