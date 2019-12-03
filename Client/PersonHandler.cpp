#include "stdafx.h"
#include "PersonHandler.h"

PlayerBase::PlayerBase(unsigned players_count)
{
	for (unsigned i = 0; i < players_count; i++)
	{
		mPlayerBase.push_back(new Player("PLA" + std::to_string(i) + "YER"));
		printf("Added new Player: %i \n", i);
		printf("Position: %i\n", static_cast<int>(mPlayerBase.back()->getPosition()));
	}
}

PlayerBase::~PlayerBase()
{	
	for (auto& itr : mPlayerBase)
	{
		delete itr;
		itr = nullptr;
	}
	mPlayerBase.clear();
}

const std::vector<Player*> & PlayerBase::getPlayerBase() const
{
	return mPlayerBase;
}

void PlayerBase::shuffle()
{
	std::random_shuffle(mPlayerBase.begin(), mPlayerBase.end());
}

void PlayerBase::update()
{
	
}
