#include "Client.h"

int main(int argc, char* argv[])
{
	Client::Client* game = Client::Client::Instance();

	srand(time(NULL)); //DEBUG

	game->run();

	Client::Client::release();

	game = nullptr;

	return 0;
}