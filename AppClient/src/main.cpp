#include "Client.h"

int main(int argc, char* argv[])
{
	Client::Client* App = Client::Client::Instance();

	//srand(time(NULL)); //DEBUG

	App->run();

	Client::Client::release();

	App = nullptr;

	return 0;
}