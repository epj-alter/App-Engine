#ifndef LADDERSIMULATION_H
#define LADDERSIMULATION_H
#include "Simulation.h"

class LadderSimulation : public Simulation
{
private:
	
	std::vector<Player*> mQueuedPlayers;
	std::vector<LadderMatch*> mSimulatedMatches;

	/* Private Functions */
	void simulate();
	void createMatches(const unsigned min_ELO, const unsigned max_ELO);
	void update();

public:

	/* Constructor */
	LadderSimulation();
	~LadderSimulation();
};


#endif // !LADDERSIMULATION_H
