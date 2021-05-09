#ifndef CALCULATED_H_
#define CALCULATED_H_

#include "Player.h"


class Calculated : public Player {
public:
	Calculated() = delete;
	Calculated(int id, int budget);
	Calculated(const Calculated& player) = delete;
	~Calculated() = default;

	bool checkToHit(int dealerValue) const override;
	void updateBetAfterWin() override;
	void updateBetAfterLoss() override;
	void setBetAfterLeave() override;
};

#endif /* CALCULATED_H_ */
