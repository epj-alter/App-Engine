#ifndef SIMULATION_H
#define SIMULATION_H
#include "LadderMatch.h"

class Simulation
{
protected:

	bool mSimulationIsDone;

	/* Private Functions */
	virtual void simulate() = 0;
	virtual void update() = 0;

public:

	/* Constructor */
	Simulation();
	virtual ~Simulation() = 0;

	/* Accessors */
	bool simulationDone();
};

#endif //