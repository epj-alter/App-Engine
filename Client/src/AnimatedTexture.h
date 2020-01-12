#ifndef ANIMATEDTEXTURE_H
#define ANIMATEDTEXTURE_H
#include "Texture.h"

namespace Engine
{
	typedef std::map<std::string, Texture*> TextureMap;

	class AnimatedTexture : public Texture
	{
	public:

		enum class WRAP_MODE { once, loop };
		enum class ANIM_DIR { horizontal, vertical };

	protected:

		Timer* mTimer;

		int mStartX;
		int mStartY;

		float mAnimationTimer;
		float mAnimationSpeed;
		float mTimerPerFrame;

		int mFrameCount;

		WRAP_MODE mWrapMode;
		ANIM_DIR mAnimationDirection;

		bool mAnimationIsDone;

		virtual void runAnimation();


	public:

		/* Constructor / Destructor */
		AnimatedTexture(std::string file_name, int x, int y, int w, int h, int frame_count, float animation_speed, ANIM_DIR animation_direction);
		virtual ~AnimatedTexture();

		/* Accessors */
		bool isAnimating();

		/* Modifiers */
		void wrapMode(WRAP_MODE mode);
		virtual void resetAnimation();

		/* Core Functions */
		virtual void update();

	};
}

#endif