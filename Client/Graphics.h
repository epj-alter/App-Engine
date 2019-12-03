#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "GraphicSettings.h"

namespace Engine
{
	class Graphics
	{
	public:
		enum FONTMODE {solid_f, shaded_f, blended_f};
	private:

		/* Static Instances */
		static Graphics* sInstance;
		static bool sInitialized;
		SDL_Rect sCamera;

		/* Core Window Variables*/
		SDL_Window* mWindow;
		SDL_Surface* mBackBuffer;
		SDL_Renderer* mRenderer;
		GraphicsSettings* mSettings;

		/* Constructor / Destructor */
		Graphics();
		~Graphics();

		/* Initializer Functions */
		bool init();

	public:

		/* Instance Functions */
		static Graphics* Instance();
		static void release();
		static bool initialized();

		/* Camera Functions */
		SDL_Rect getCamera();
		void setCamera(int x, int y);

		/* Functions */
		SDL_Texture* loadTexture(std::string path);
		SDL_Texture* createTextTexture(TTF_Font* font, std::string text, SDL_Color fg_color, FONTMODE mode = solid_f, SDL_Color bg_color = {0, 0, 0});
		void clearBackBuffer();
		void drawRectangle(SDL_Rect* rectangle, SDL_Color fill_color, SDL_Color outline_color);
		void drawTexture
		(
			SDL_Texture* texture, 
			SDL_Rect* clip = nullptr, 
			SDL_Rect* rend = nullptr, 
			float angle = 0.0f, 
			SDL_RendererFlip flip = SDL_FLIP_NONE
		);
		void drawLine(float start_x, float start_y, float end_x, float end_y);

		/* Core Functions */
		void render();
	};

}

#endif