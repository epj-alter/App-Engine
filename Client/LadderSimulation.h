#ifndef LADDERSIMULATION_H
#define LADDERSIMULATION_H
#include "Simulation.h"

class LadderSimulation : public Simulation
{
private:
	
	PlayerBase* mPlayerBase;
	//std::map<unsigned, std::string> mIterations; // so it doesn't repeat an iteration
	std::vector<Player*> mQueuedPlayers;
	//std::map<std::string, Match*> mSimulatedMatches; //ID STUFF NOT YET
	std::vector<LadderMatch*> mSimulatedMatches;

	/* Private Functions */
	void simulate();
	void createMatches(const unsigned min_ELO, const unsigned max_ELO);
	void update();

public:

	/* Constructor */
	LadderSimulation(PlayerBase* player_base);
	~LadderSimulation();
};


#endif // !LADDERSIMULATION_H
