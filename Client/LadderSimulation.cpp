#include "stdafx.h"
#include "LadderSimulation.h"

/* Private Functions */
void LadderSimulation::simulate()
{

}

void LadderSimulation::createMatches(const unsigned min_ELO, const unsigned max_ELO)
{
	bool match_found = true;

	while (match_found && (mQueuedPlayers.size() >= 5))
	{
		mSimulatedMatches.push_back(new LadderMatch());

		for (auto& itr : mQueuedPlayers)
		{
			if (itr->getPlayerAttribute().ELO >= min_ELO && itr->getPlayerAttribute().ELO < max_ELO)
			{
				if (mSimulatedMatches.back()->addPlayer(itr, itr->queuedPosition()))
				{
					itr->setQueueStatus(false);
					update();
				}
				else if (mSimulatedMatches.back()->hasEnoughPlayers())
				{
					break;
				}
				else if (itr->getID() == mQueuedPlayers.back()->getID())
				{
					if (!mSimulatedMatches.back()->hasEnoughPlayers())
					{
						delete mSimulatedMatches.back();
						mSimulatedMatches.pop_back();
						match_found = false;
					}
					break;
				}
			}
			else if (itr->getID() == mQueuedPlayers.back()->getID())
			{
				if (!mSimulatedMatches.back()->hasEnoughPlayers())
				{
					mSimulatedMatches.pop_back();
				}
				match_found = false;
			}
		}
	}
	printf("Pairing Teams Done between ELO %i - %i \n", min_ELO, max_ELO);
	printf("Number of created teams: %i \n", mSimulatedMatches.size());
}

void LadderSimulation::update()
{
	mPlayerBase->shuffle();
	mQueuedPlayers.clear();

	for (const auto& itr : mPlayerBase->getPlayerBase())
	{
		if (itr->isQueuedUp())
		{
			mQueuedPlayers.push_back(itr);
		}
	}

	printf("Queued Players Count: %i \n", mQueuedPlayers.size());
}

/* Constructor / Destructor */
LadderSimulation::LadderSimulation(PlayerBase* player_base)
{
	mPlayerBase = player_base;

	update();

	if (mQueuedPlayers.size() >= 5)
	{
		createMatches(Bronze, Silver);
		createMatches(Silver, Gold);
		createMatches(Gold, Platinum);
		createMatches(Platinum, Diamond);
		createMatches(Diamond, Master);
		createMatches(Master, Challenger);
		createMatches(Challenger, ELO_MAX);
	}
	else
		printf("There are not enough players in Queue \n");

	if (mSimulatedMatches.size() > 0)
	{
		for (auto& itr : mSimulatedMatches)
		{
			itr->updateTeams();
		}
	}

}

LadderSimulation::~LadderSimulation()
{
	for (auto& itr : mSimulatedMatches)
	{
		delete itr;
		itr = nullptr;
	}
	mSimulatedMatches.clear();

	//mIterations.clear();

	mQueuedPlayers.clear();
	mPlayerBase = nullptr;
}
