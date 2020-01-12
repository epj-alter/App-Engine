#include "stdafx.h"
#include "Simulation.h"

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
