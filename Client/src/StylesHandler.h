#ifndef STYLESHANDLER_H
#define STYLESHANDLER_H

namespace Engine
{
	class StylesHandler
	{
	public:
		enum class FONT_MODIFIER {x_small, small, medium, large, x_large };

	private:

		static StylesHandler* sInstance;

		FILE* dFile;
		aColorMap mColors;
		aStringMap mFonts;

		bool loadColors();
		bool loadFonts();

		StylesHandler();
		~StylesHandler();

	public:

		static StylesHandler* instance();
		static void release();

		/* Functions */
		int size(StylesHandler::FONT_MODIFIER size_mod = StylesHandler::FONT_MODIFIER::medium);
		std::string font(std::string key) const;
		SDL_Color color(std::string key) const;

	};
}

#endif