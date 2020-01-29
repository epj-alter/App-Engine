#include "Graphics.h"

namespace Engine
{
	Graphics* Graphics::sInstance = nullptr;
	bool Graphics::sInitialized = false;

	/* Constructor / Destructor */
	Graphics::Graphics()
	{
		this->mWindow = nullptr;
		this->mBackBuffer = nullptr;
		this->mRenderer = nullptr; 
		
		mSettings = GraphicsSettings::instance();

		sCamera = { 0, 0, mSettings->get().width, mSettings->get().height };

		this->sInitialized = init();
	}

	Graphics::~Graphics()
	{

		GraphicsSettings::release();
		mSettings = nullptr;

		SDL_DestroyWindow(this->mWindow);
		this->mWindow = nullptr;

		SDL_DestroyRenderer(this->mRenderer);
		this->mRenderer = nullptr;

		this->mBackBuffer = nullptr;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	/* Initializer Functions */
	bool Graphics::init()
	{
		/* Initializing SDL */
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			printf("SDL_Init Error: %s\n", SDL_GetError());
			return false;
		}

		/* Creating Window */
		this->mWindow = SDL_CreateWindow
		(
			mSettings->get().title,
			mSettings->get().x_pos, mSettings->get().y_pos,
			mSettings->get().width, mSettings->get().height, NULL
		);

		if (this->mWindow == nullptr)
		{
			printf("Window Creation Error: %s\n", SDL_GetError());
			return false;
		}

		// try with a new camera..

		/* Creating Renderer */
		this->mRenderer = SDL_CreateRenderer
		(
			mWindow,
			-1,
			SDL_RENDERER_ACCELERATED
		);

		if (this->mRenderer == nullptr)
		{
			printf("Renderer Creation Error: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->mRenderer, 0x00, 0x00, 0x00, 0xFF);

		/* Loading GFX SETTINGS */
		switch (mSettings->get().display_mode)
		{
		case 0:
			SDL_SetWindowFullscreen(mWindow, 0);
			break;

		case 1:
			SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			break;

		case 2:
			SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
			break;

		case 3:
			SDL_SetWindowBordered(mWindow, SDL_FALSE);
			SDL_MaximizeWindow(mWindow);
			break;

		case 4:
			SDL_SetWindowBordered(mWindow, SDL_TRUE);
			SDL_RestoreWindow(mWindow);
			break;
		default:
			SDL_SetWindowFullscreen(mWindow, 0);
			break;
		}

		switch (mSettings->get().Vsync)
		{
		case true:
			SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
			break;
		default:
			SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
			break;
		}

		switch (mSettings->get().filter)
		{
		case 0:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
			break;
		case 1:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
			break;
		case 2:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
			break;
		default:
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
			break;
		}
		//end

		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags))
		{
			printf("Image Initialization Error: %s\n", IMG_GetError());
			return false;
		}

		if (TTF_Init() == -1)
		{
			printf("TTFont Initialization Error: %s\n", TTF_GetError());
			return false;
		}

		/* Adding Buffer */
		this->mBackBuffer = SDL_GetWindowSurface(mWindow);

		return true;
	}

	/* Instance Functions */
	Graphics* Graphics::Instance()
	{
		if (sInstance == nullptr)
			sInstance = new Graphics();

		return sInstance;
	}

	void Graphics::release()
	{
		delete sInstance;
		sInstance = nullptr;

		sInitialized = false;
	}

	bool Graphics::initialized()
	{
		return sInitialized;
	}

	/* Camera Functions */
	SDL_Rect Graphics::getCamera()
	{
		return sCamera;
	}

	void Graphics::setCamera(int x, int y)
	{
		int w = mSettings->get().width;
		int h = mSettings->get().height;

		sCamera = { static_cast<int>(x - w * 0.5f), static_cast<int>(y - h * 0.5f), w, h };
	}

	/* Functions */
	SDL_Texture* Graphics::loadTexture(std::string file_path)
	{
		SDL_Texture* texture = nullptr;
		SDL_Surface* loaded_texture = nullptr;

		/* Loading Image to Surface */

		loaded_texture = SDL_ConvertSurfaceFormat(IMG_Load(file_path.c_str()), SDL_PIXELFORMAT_ABGR8888, 0); //IMG_Load(file_path.c_str());

		if (loaded_texture == nullptr)
		{
			printf("Image Initialization Error: Image-%s Error-%s", file_path.c_str(), IMG_GetError());
			return nullptr;
		}


		/* Creating texture from Surface Image */
		texture = SDL_CreateTextureFromSurface(this->mRenderer, loaded_texture);

		if (texture == nullptr)
		{
			SDL_FreeSurface(loaded_texture);
			printf("Texture Initialization Error: %s\n", IMG_GetError());
			return nullptr;
		}

		SDL_FreeSurface(loaded_texture);

		return texture;
	}

	SDL_Texture* Graphics::createTextTexture(TTF_Font* font, std::string text, SDL_Color fg_olor, FONTMODE mode, SDL_Color bg_color)
	{
		SDL_Surface* surface = nullptr;

		switch (mode)
		{
		case Engine::Graphics::FONTMODE::solid_f:
			surface = TTF_RenderText_Solid(font, text.c_str(), fg_olor);
			break;
		case Engine::Graphics::FONTMODE::shaded_f:
			surface = TTF_RenderText_Shaded(font, text.c_str(), fg_olor, bg_color);
			break;
		case Engine::Graphics::FONTMODE::blended_f:
			surface = TTF_RenderText_Blended(font, text.c_str(), fg_olor);
			break;
		default:
			break;
		}

		if (surface == nullptr)
		{
			printf("Text Surface Initialization Error: Text-%s Error-%s", text.c_str(), IMG_GetError());
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(this->mRenderer, surface);
		if (texture == nullptr)
		{
			printf("Text Texture Creation Error: Text-%s Error-%s", text.c_str(), IMG_GetError());
			return nullptr;
		}

		SDL_FreeSurface(surface);

		return texture;
	}

	void Graphics::clearBackBuffer()
	{
		SDL_RenderClear(this->mRenderer);
	}

	void Graphics::drawRectangle(SDL_Rect* rectangle, SDL_Color fill_color, SDL_Color outline_color)
	{
		if (fill_color.a != 0)
		{
			SDL_SetRenderDrawColor(this->mRenderer, fill_color.r, fill_color.g, fill_color.b, fill_color.a);
			SDL_RenderFillRect(mRenderer, rectangle);
		}

		if(outline_color.a != 0)
		{
			SDL_SetRenderDrawColor(this->mRenderer, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
			SDL_RenderDrawRect(mRenderer, rectangle);
		}

		SDL_SetRenderDrawColor(this->mRenderer, 0x00, 0x00, 0x00, 0xFF);
	}

	void Graphics::drawTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(this->mRenderer, texture, clip, rend, angle, nullptr, flip);
	}

	void Graphics::drawLine(float start_x, float start_y, float end_x, float end_y)
	{
		SDL_SetRenderDrawColor(this->mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(this->mRenderer, start_x, start_y, end_x, end_y);
		SDL_SetRenderDrawColor(this->mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}

	/* Core Functions */
	void Graphics::render()
	{
		SDL_RenderPresent(this->mRenderer);
	}

}