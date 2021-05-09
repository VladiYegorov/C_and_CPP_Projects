#include "Casino.h"

class Dealer: public Casino{
private:
	Card hiddenCard;
public:
	Dealer();
	Dealer(const Dealer& dealer) = delete;
	~Dealer() = default;

	void setBudget(int newBudget) = delete;
	void setBet(int newBet) = delete;
	int getId() const = delete;
	int getBet() const = delete;
	int getBudget() const = delete;

	void preparePlayerNewRound();
	Card& getHiddenCard();
	void addHiddenCard(const Card& card);

	void updateBetAfterWin() override {};
	void updateBetAfterLoss() override {};
	void setBetAfterLeave() override {};
};
