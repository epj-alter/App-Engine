#ifndef SCENE_H
#define SCENE_H

#include "SceneData.h"

namespace Engine
{
	class Scene : public GameEntity
	{
	public:
		enum SCENE_ID { no_id, load_scene, debug_scene };

	protected:

		static float mInputDelayTimer;
		static const float mInputDelay;

		const SCENE_ID mSceneID;
		const std::string mSceneName;

		SDL_Event* mEvent;
		FILE* dFile;

		Timer* mTimer;
		InputHandler* mInput;
		AudioHandler* mAudio;
		SceneData* mSceneData;
		StylesHandler* mStyles;
		aKeyMap mKeyMap;

		/* GUI Elements */
		MessageBox* mMessageBox;
		aInputFieldMap mInputField;
		aContainerMap mContainer;
		aButtonMap mButton;
		aCheckButtonMap mCheckButton;
		aDropdownListMap mDropDownList;
		aProgressBarMap mProgressBar;
		aSliderMap mSlider;
		aConfirmationBoxMap mConfirmationBox;

		bool mWritting;
		bool mPaused;

		bool mCloseScene;

		/* Initializes the KeyBindings, must be called in each individual scene constructor
			 together with the name of the scene exp mSceneName = "debug_scene"*/
		void initKeyMap();

	public:

		/* Constructor / Destuctor */
		Scene(std::string scene_name, SCENE_ID scene_id);
		virtual ~Scene();

		/* Accessors */
		const SCENE_ID getID() const;

		bool paused() const;
		bool closeScene() const;
		const bool inputIsUnlocked() const;

		/* GUI Accessors */
		aInputFieldMap* getInputField();

		/* GUI Modifiers */
		void addInputField(std::string name, GameEntity* parent, int x, int y, int width, int height);
		void addContainer(std::string name, GameEntity* parent, int x, int y, int width, int height, Uint8 opacity = 255);
		void addButton(std::string name, GameEntity* parent, std::string text, int x, int y, int width, int height, bool text_only = false, bool default_button = true);
		void addCheckButton(std::string name, GameEntity* parent, int x, int y, int width, int height, bool is_radio = false, bool opaque = false);
		void addDropDownList(std::string name, GameEntity* parent, int x, int y, int width, int height, bool opaque = false);
		void addProgressBar(std::string name, GameEntity* parent, int x, int y, int width, int height, const float& current_value, const float& max_value, bool show_percentage = false);
		void addSlider(std::string name, GameEntity* parent, int x, int y, int width, int height, int& current_value, const int& max_value);
		void addConfirmationBox(std::string name, std::string message);
		
		/* Input Updates */
		void updateInputLock();
		void updateInputFields();
		void renderInputFields();

		/* Interface Functions */
		virtual void updateInterface() = 0;
		virtual void renderInterface() = 0;

		/* Core Functions */
		virtual void updateInput() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
	};
}

#endif