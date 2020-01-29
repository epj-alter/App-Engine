#include "StylesHandler.h"

namespace GUI
{
	StylesHandler* StylesHandler::sInstance = nullptr;

	bool StylesHandler::loadColors()
	{
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Data/Styles.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);
				const rapidjson::Value& colors = d["Colors"];

				for (int i = 0; i < colors.Size(); i++)
				{
					mColors.insert
					({ colors[i]["key"].GetString(), SDL_Color{
						static_cast<Uint8>(colors[i]["r"].GetUint()),
						static_cast<Uint8>(colors[i]["g"].GetUint()),
						static_cast<Uint8>(colors[i]["b"].GetUint()),
						static_cast<Uint8>(colors[i]["a"].GetUint())
						}});
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
				else
					return false;
			}
			else
			{
				printf("SCENEDATA::loadColors Could not load File '%s'\n", full_path.c_str());
				return false;
			}
		}
		else
			return false;
		return true;
	}

	bool StylesHandler::loadFonts()
	{
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Data/Styles.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);

				const rapidjson::Value& fonts = d["Fonts"];

				for (int i = 0; i < fonts.Size(); i++)
				{
					mFonts.insert({ fonts[i]["key"].GetString(), fonts[i]["path"].GetString() });
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
				else
					return false;
			}
			else
			{
				printf("SCENEDATA::loadFonts Could not load File '%s'\n", full_path.c_str());
				return false;
			}
		}
		else
			return false;
		return true;
	}

	/* Constructor / Destructor */
	StylesHandler::StylesHandler()
	{
		if (!loadColors() || !loadFonts())
			printf("STYLESHANDLER::FAILED\n");
	}

	StylesHandler::~StylesHandler()
	{
		dFile = nullptr;

		mFonts.clear();
		mColors.clear();
	}

	/* Instance Functions */
	StylesHandler* StylesHandler::instance()
	{
		if (sInstance == nullptr)
			sInstance = new StylesHandler();

		return sInstance;
	}

	void StylesHandler::release()
	{
		delete sInstance;
		sInstance = nullptr;
	}

	/* Functions */
	int StylesHandler::size(StylesHandler::FONT_MODIFIER size_mod)
	{
		int font_size;

		switch (size_mod)
		{
		case GUI::StylesHandler::FONT_MODIFIER::x_small:
			font_size = 8;
			break;
		case GUI::StylesHandler::FONT_MODIFIER::small:
			font_size = 10;
			break;
		case GUI::StylesHandler::FONT_MODIFIER::medium:
			font_size = 14;
			break;
		case GUI::StylesHandler::FONT_MODIFIER::large:
			font_size = 24;
			break;
		case GUI::StylesHandler::FONT_MODIFIER::x_large:
			font_size = 48;
			break;
		}

		return font_size;
	}

	std::string StylesHandler::font(std::string key) const
	{
		return mFonts.at(key);
	}

	SDL_Color StylesHandler::color(std::string key) const
	{
		return mColors.at(key);
	}
}
