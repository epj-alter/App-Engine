#include "LadderSimulation.h"
#include "DataHandler.h"

namespace Core
{
	/* Private Functions */
	void LadderSimulation::simulate()
	{
		//for (auto& match : mSimulatedMatches)
		//{
		//	match->simulate();
		//}
	
		mSimulatedMatches.back()->simulate();
	}
	
	void LadderSimulation::createMatches(const unsigned min_ELO, const unsigned max_ELO)
	{
		bool match_found = true;
	
		while (match_found && (mQueuedPlayers.size() >= 5))
		{
			mSimulatedMatches.push_back(new LadderMatch());
	
			for (auto& player : mQueuedPlayers)
			{
				if (player->getPlayerAttribute().getProgressAtt().ELO >= min_ELO && player->getPlayerAttribute().getProgressAtt().ELO < max_ELO)
				{
					if (mSimulatedMatches.back()->addPlayer(player, player->queuedPosition()))
					{
						player->setQueueStatus(false);
						update();
					}
					else if (mSimulatedMatches.back()->hasEnoughPlayers())
					{
						break;
					}
					else if (player->getID() == mQueuedPlayers.back()->getID())
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
				else if (player->getID() == mQueuedPlayers.back()->getID())
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
		DataHandler::instance()->shuffle();
		mQueuedPlayers.clear();
	
		for (const auto& player : *DataHandler::instance()->getPlayersDB())
		{
			if (player->isQueuedUp())
			{
				mQueuedPlayers.push_back(player);
			}
		}
	
		printf("Queued Players Count: %i \n", mQueuedPlayers.size());
	}
	
	/* Constructor / Destructor */
	LadderSimulation::LadderSimulation()
	{
		printf("Updating player queues.\n");
	
		update();
	
		printf("Creating Matches. \n");
	
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
	
		printf("Updating teams \n");
	
		if (mSimulatedMatches.size() > 0)
		{
			for (auto& itr : mSimulatedMatches)
			{
				itr->updateTeams();
			}
		}
	
		printf("Simulating Matches. \n");
	
		std::thread t1(&LadderSimulation::simulate, this); //???? //THREAD SUCCESSFULL?
		t1.detach(); // DETATCH OR JOIN=?=???= join waits for the thread to be finished.
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
	}
}
