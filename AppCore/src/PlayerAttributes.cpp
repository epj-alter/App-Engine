#include "PlayerAttributes.h"

namespace Core
{
	void PlayerAttributes::initAttributes()
	{
		/* Progress Attributes */
		mProgressAtt.Level = 1;
		mProgressAtt.CurrentExp = 0;
		mProgressAtt.NextLevelExp 
			= static_cast<unsigned long long int>((50 / 3) * (pow(mProgressAtt.Level + 1, 3) - 6 * pow(mProgressAtt.Level + 1, 2) + ((double(mProgressAtt.Level) + 1) * 17) - 12));
	
		/* Basic Attributes */
		mTechnicalAtt = {};
		mMentalAtt = {};
		mPersonalityAtt = {};
		mOverallAtt = {};
	
		calculateOverall();
	}
	
	void PlayerAttributes::calculateOverall()
	{
		mOverallAtt.Laning =
			((mTechnicalAtt.lasthitting + mTechnicalAtt.trading + mTechnicalAtt.harassing + mTechnicalAtt.awareness + mMentalAtt.concentration + mMentalAtt.aggression) * 2 +
			(mTechnicalAtt.accuracy + mTechnicalAtt.dodging + mTechnicalAtt.eliminating + mTechnicalAtt.flair + mTechnicalAtt.positioning + mTechnicalAtt.survivability + 
				mMentalAtt.anticipation + mMentalAtt.creativity + mMentalAtt.decisions)) / 21;
	
		mOverallAtt.Surviving =
			((mTechnicalAtt.survivability + mTechnicalAtt.positioning + mTechnicalAtt.flair + mTechnicalAtt.dodging) * 2 +
			(mTechnicalAtt.awareness + mMentalAtt.anticipation + mMentalAtt.composure + mMentalAtt.concentration + mMentalAtt.decisions)) / 13;
	
		mOverallAtt.TeamFighting =
			((mTechnicalAtt.positioning + mMentalAtt.anticipation + mMentalAtt.composure + mMentalAtt.concentration + mMentalAtt.creativity + mMentalAtt.decisions + mMentalAtt.teamwork) * 2 +
			(mTechnicalAtt.accuracy + mTechnicalAtt.dodging + mTechnicalAtt.eliminating + mTechnicalAtt.flair + mTechnicalAtt.survivability + mMentalAtt.aggression)) / 20;
	
		mOverallAtt.Roaming =
			((mTechnicalAtt.awareness + mTechnicalAtt.flair + mTechnicalAtt.harassing + mTechnicalAtt.trading + mMentalAtt.bravery + mMentalAtt.decisions) * 2 +
			(mMentalAtt.anticipation + mMentalAtt.leadership + mMentalAtt.teamwork)) / 15;
	
		mOverallAtt.Assassinating =
			((mTechnicalAtt.eliminating + mTechnicalAtt.flair + mTechnicalAtt.positioning + mTechnicalAtt.survivability + mTechnicalAtt.accuracy + 
				mMentalAtt.aggression + mMentalAtt.anticipation + mMentalAtt.bravery + mMentalAtt.creativity + mMentalAtt.decisions) * 2 +
			(mMentalAtt.leadership + mMentalAtt.teamwork + mMentalAtt.workrate + mTechnicalAtt.dodging)) / 24;
	
		mOverallAtt.SplitPushing =
			(mTechnicalAtt.awareness + mTechnicalAtt.dodging + mTechnicalAtt.flair + mTechnicalAtt.positioning + mTechnicalAtt.survivability + 
				mMentalAtt.anticipation + mMentalAtt.bravery + mMentalAtt.creativity + mMentalAtt.decisions + mMentalAtt.teamwork) / 10;
	}
	
	void PlayerAttributes::randomizeAttributes()
	{
		mProgressAtt.ELO = rand() % 3000 + 1;
		mTechnicalAtt.accuracy = rand() % 20 + 1;
		mPersonalityAtt.adaptability = rand() % 20 + 1;
		mMentalAtt.aggression = rand() % 20 + 1;
		mPersonalityAtt.ambition = rand() % 20 + 1;
		mMentalAtt.anticipation = rand() % 20 + 1;
		mTechnicalAtt.awareness = rand() % 20 + 1;
		mMentalAtt.bravery = rand() % 20 + 1;
		mMentalAtt.composure = rand() % 20 + 1;
		mMentalAtt.concentration = rand() % 20 + 1;
		mPersonalityAtt.consistency = rand() % 20 + 1;
		mPersonalityAtt.controversy = rand() % 20 + 1;
		mMentalAtt.creativity = rand() % 20 + 1;
		mMentalAtt.decisions = rand() % 20 + 1;
		mTechnicalAtt.dodging = rand() % 20 + 1;
		mTechnicalAtt.eliminating = rand() % 20 + 1;
		mTechnicalAtt.flair = rand() % 20 + 1;
		mTechnicalAtt.harassing = rand() % 20 + 1;
		mTechnicalAtt.lasthitting = rand() % 20 + 1;
		mMentalAtt.leadership = rand() % 20 + 1;
		mPersonalityAtt.loyalty = rand() % 20 + 1;
		mTechnicalAtt.positioning = rand() % 20 + 1;
		mPersonalityAtt.pressurehandling = rand() % 20 + 1;
		mPersonalityAtt.professionalism = rand() % 20 + 1;
		mPersonalityAtt.sportsmanship = rand() % 20 + 1;
		mTechnicalAtt.survivability = rand() % 20 + 1;
		mMentalAtt.teamwork = rand() % 20 + 1;
		mPersonalityAtt.temperament = rand() % 20 + 1;
		mTechnicalAtt.trading = rand() % 20 + 1;
		mPersonalityAtt.versatility = rand() % 20 + 1;
		mMentalAtt.workrate = rand() % 20 + 1;
	}
	
	void PlayerAttributes::updateLevel()
	{
		mProgressAtt.Level++;
	
		mProgressAtt.NextLevelExp
			= static_cast<unsigned long long int>((50 / 3) * (pow(mProgressAtt.Level + 1, 3) - 6 * pow(mProgressAtt.Level + 1, 2) + ((double(mProgressAtt.Level) + 1) * 17) - 12));
	
		//this->updateStats(true);
	}
	
	/* Constructor / Destructor */
	PlayerAttributes::PlayerAttributes()
	{
		initAttributes();
		randomizeAttributes();
	}
	
	PlayerAttributes::~PlayerAttributes()
	{
	}
	
	const Progress PlayerAttributes::getProgressAtt() const
	{
		return mProgressAtt;
	}
	
	/* Accessors */
	const Technical PlayerAttributes::getTechnicalAtt() const
	{
		return mTechnicalAtt;
	}
	
	const Mental PlayerAttributes::getMentalAtt() const
	{
		return mMentalAtt;
	}
	
	const Personality PlayerAttributes::getPersonalityAtt() const
	{
		return mPersonalityAtt;
	}
	
	const Overall PlayerAttributes::getOverallAtt() const
	{
		return mOverallAtt;
	}
	
	/* Update Functions */
	void PlayerAttributes::updateExp(const int gained_exp)
	{
		mProgressAtt.CurrentExp += gained_exp;
	
		if (mProgressAtt.CurrentExp > ExpLimit)
			mProgressAtt.CurrentExp = ExpLimit;
	
		if (mProgressAtt.CurrentExp >= mProgressAtt.NextLevelExp)
		{
			mProgressAtt.CurrentExp = 0;
			updateLevel();
		}
	}
}
