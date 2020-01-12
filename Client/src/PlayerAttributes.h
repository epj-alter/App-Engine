#ifndef PLAYERATTRIBUTES_H
#define PLAYERATTRIBUTES_H
#include "PlayerData.h"

class PlayerAttributes
{
private:

	/* Progress Attributes */
	Progress mProgressAtt;

	/* Primary Attributes */
	Technical mTechnicalAtt;
	Mental mMentalAtt;
	Personality mPersonalityAtt;
	Overall mOverallAtt;

	/* Initializers */
	void initAttributes();
	void calculateOverall();
	void randomizeAttributes();
	void updateLevel();

public:

	/* Constructors */
	PlayerAttributes();
	~PlayerAttributes();

	/* Accessors */
	const Progress getProgressAtt() const;
	const Technical getTechnicalAtt() const;
	const Mental getMentalAtt() const;
	const Personality getPersonalityAtt() const;
	const Overall getOverallAtt() const;

	/* Update Functions */
	void updateExp(const int gained_exp);
};
#endif // !PLAYERATTRIBUTES_H
