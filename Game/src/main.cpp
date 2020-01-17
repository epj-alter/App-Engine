#include "stdafx.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Engine::Game* game = Engine::Game::Instance();

	srand(time(NULL)); //DEBUG

	game->run();

	Engine::Game::release();

	game = nullptr;

	return 0;
}