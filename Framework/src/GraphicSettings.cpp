#include "GraphicSettings.h"

namespace Engine
{
	GraphicsSettings* GraphicsSettings::sInstance = nullptr;
	gfxSettings GraphicsSettings::mSettings = {0, 800, 600, 0, false, 0};
	float GraphicsSettings::FPS_Limit = 60;

	/* Constructor / Destructor */
	GraphicsSettings::GraphicsSettings()
	{
		this->load();
	}

	GraphicsSettings::~GraphicsSettings()
	{
		
	}

	/* Instancers */
	GraphicsSettings* GraphicsSettings::instance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new GraphicsSettings();
		}

		return sInstance;
	}

	void GraphicsSettings::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	/* Accessors */
	const float GraphicsSettings::FPS()
	{
		return FPS_Limit;
	}

	const gfxSettings GraphicsSettings::get()
	{
		return mSettings;
	}

	/* Functions */
	bool GraphicsSettings::save() const
	{
		return false;
	}

	void GraphicsSettings::load()
	{
		FILE* config = nullptr;
		rapidjson::Document d;

		std::string full_path = SDL_GetBasePath();
		full_path.append("Config/Config.json");
		fopen_s(&config, full_path.c_str(), "rb");

		if (config == nullptr)
		{
			printf("Could not load 'Config' File\n");
		}
		else
		{
			char readBuffer[4000];
			rapidjson::FileReadStream is(config, readBuffer, sizeof(readBuffer));
			d.ParseStream(is);

			mSettings = {d["w_position"].GetInt(), d["width"].GetInt(), d["height"].GetInt(), d["display_mode"].GetInt(), d["V_SYNC"].GetBool(), d["anisotropic_filter"].GetInt()};

			fclose(config);
			config = nullptr;
		}
	}

	void GraphicsSettings::reload()
	{
	}
}