#include "Simulation.h"

namespace Core
{
	void Simulation::simulate()
	{
	}
	
	/* Constructor / Destructor */
	Simulation::Simulation()
	{
		mSimulationIsDone = false;
	}
	
	Simulation::~Simulation()
	{
	
	}
	
	bool Simulation::simulationDone()
	{
		return mSimulationIsDone;
	}
	
	void Simulation::update()
	{
	}
}
