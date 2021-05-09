#ifndef CASINO_H_
#define CASINO_H_

#include "Player.h"

class Casino : public Player {
public:
	Casino() = delete;
	Casino(int id,int budget);
	~Casino() = default;

	bool checkToHit(int dealerValue) const override;
	void updateBetAfterWin() override;
	void updateBetAfterLoss() override;
	void setBetAfterLeave() override;
};

#endif /* CASINO_H_ */
