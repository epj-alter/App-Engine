#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Engine
{
	#define PI 3.14159265
	#define DEG_TO_RAD PI / 180.0f
	#define RAD_TO_DEG 180.0f / PI

	/* Maps */
	typedef std::map<std::string, SDL_Texture*> aTextureMap;
	typedef std::map<std::string, TTF_Font*> aFontMap;
	typedef std::map<std::string, Mix_Music*> aMusicMap;
	typedef std::map<std::string, Mix_Chunk*> aSFXMap;
	typedef std::map<std::string, std::string> aStringMap;
	typedef std::map<std::string, SDL_Color> aColorMap;
}

#endif // !CONSTANTS_H
