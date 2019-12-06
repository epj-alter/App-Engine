#include "DataHandler.h"

namespace Engine
{
	/* instance to nullptr */
	DataHandler* DataHandler::sInstance = nullptr;

	Engine::DataHandler::DataHandler()
	{
	}

	Engine::DataHandler::~DataHandler()
	{
	}

	DataHandler* Engine::DataHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new DataHandler();

		return sInstance;
	}

	void Engine::DataHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}
}
