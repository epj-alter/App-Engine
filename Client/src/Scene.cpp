#include "stdafx.h"
#include "Scene.h"

namespace Engine
{
	float Scene::mInputDelayTimer = 0.0f;
	const float Scene::mInputDelay = 5.0f;

	/* Initializers */
	void Scene::initKeyMap()
	{
		if (dFile == nullptr)
		{
			rapidjson::Document d;
			std::string full_path = SDL_GetBasePath();
			full_path.append("Config/Keybinds.json");

			if (fopen_s(&dFile, full_path.c_str(), "rb") == 0)
			{
				char readBuffer[4000];
				rapidjson::FileReadStream is(dFile, readBuffer, sizeof(readBuffer));
				d.ParseStream(is);
				const rapidjson::Value& key_array = d[mSceneName.c_str()];

				for (int i = 0; i < key_array.Size(); i++)
				{
					mKeyMap[key_array[i]["action"].GetString()] = mSceneData->getKeyCode(key_array[i]["key"].GetString());

					if (mKeyMap.at(key_array[i]["action"].GetString()) == NULL)
					{
						printf("SCENE::initKeyMap Could not insert key '%s' into array\n", key_array[i]["key"].GetString());
					}
				}

				if (dFile != nullptr)
				{
					fclose(dFile);
					dFile = nullptr;
				}
			}
			else
			{
				printf("SCENE::initKeyMap Could not load File '%s'\n", full_path.c_str());
			}
		}
	}

	/* Constructor / Destuctor */
	Scene::Scene(std::string scene_name, SCENE_ID scene_id)
		: mSceneName(scene_name), mSceneID(scene_id)
	{
		dFile = nullptr;

		mTimer = Timer::instance();
		mInput = InputHandler::instance();
		mAudio = AudioHandler::instance();
		mSceneData = SceneData::instance();
		mStyles = StylesHandler::instance();

		mMessageBox = MessageBox::instance();

		mEvent = &InputHandler::getEvent();
		mWritting = false;
		mPaused = false;

		mCloseScene = false;

		mInputDelayTimer = 0.f;

		initKeyMap();
	}

	Scene::~Scene()
	{
		mKeyMap.clear();
		
		for (auto& itr : mInputField)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mInputField.clear();
		
		for (auto& itr : mContainer)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mContainer.clear();
		
		for (auto& itr : mButton)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mButton.clear();
		
		for (auto& itr : mCheckButton)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mCheckButton.clear();
		
		for (auto& itr : mDropDownList)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mDropDownList.clear();
		
		for (auto& itr : mProgressBar)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mProgressBar.clear();
		
		for (auto& itr : mSlider)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mSlider.clear();

		for (auto& itr : mConfirmationBox)
		{
			delete itr.second;
			itr.second = nullptr;
		}
		mConfirmationBox.clear();

		mMessageBox = nullptr;

		dFile = nullptr;

		mStyles = nullptr;
		mEvent = nullptr;
		mTimer = nullptr;
		mInput = nullptr;
		mAudio = nullptr;
		mSceneData = nullptr;
	}

	/* Accessors */
	const Scene::SCENE_ID Scene::getID() const
	{
		return mSceneID;
	}

	const bool Scene::inputIsUnlocked() const
	{
		if (mInputDelayTimer >= mInputDelay)
		{
			mInputDelayTimer = 0.f;
			return true;
		}

		return false;
	}

	bool Scene::paused() const
	{
		return mPaused;
	}

	bool Scene::closeScene() const
	{
		return mCloseScene;
	}

	/* GUI Accessors */
	aInputFieldMap* Scene::getInputField()
	{
		return &mInputField;
	}

	/* GUI Modifiers */
	void Scene::addInputField(std::string name, GameEntity* parent,	int x, int y, int width, int height)
	{
		mInputField.insert({name, new InputField(this, x, y, width, height) });
	}

	void Scene::addContainer(std::string name, GameEntity* parent, int x, int y, int width, int height, Uint8 opacity)
	{
		mContainer.insert({ name, new Container(parent, x, y, width, height, opacity) });
	}

	void Scene::addButton(std::string name, GameEntity* parent, std::string text, int x, int y, int width, int height, bool text_only, bool default_button)
	{
		mButton.insert({ name, new Button(parent, text, x, y, width, height, text_only, default_button) });
	}

	void Scene::addCheckButton(std::string name, GameEntity* parent, int x, int y, int width, int height, bool is_radio, bool opaque)
	{
		mCheckButton.insert({ name, new CheckButton(parent, x, y, width, height, is_radio, opaque) });
	}

	void Scene::addDropDownList(std::string name, GameEntity* parent, int x, int y, int width, int height, bool opaque)
	{
		mDropDownList.insert({ name, new DropDownList(parent, x, y, width, height, opaque) });
	}

	void Scene::addProgressBar(std::string name, GameEntity* parent, int x, int y, int width, int height, const float& current_value, const float& max_value, bool show_percentage)
	{
		mProgressBar.insert({ name, new ProgressBar(parent, x, y, width, height, current_value, max_value, show_percentage) });
	}

	void Scene::addSlider(std::string name, GameEntity* parent, int x, int y, int width, int height, int& current_value, const int& max_value)
	{
		mSlider.insert({ name, new Slider(parent, x, y, width, height, current_value, max_value) });
	}

	void Scene::addConfirmationBox(std::string name, std::string message)
	{
		mConfirmationBox.insert({ name, new ConfirmationBox(message) });
	}

	/* Input Updates */
	void Scene::updateInputLock()
	{
		if (mInputDelayTimer < mInputDelay)
			mInputDelayTimer += mTimer->getDeltaTime();
	}

	void Scene::updateInputFields()
	{
		if (mInputField.size() > 0)
			for (auto& itr : mInputField)
			{
				itr.second->update();

				if (!mWritting)
				{
					if (itr.second->hasFocus())
						mWritting = true;
				}
				else if(mWritting && !itr.second->hasFocus())
				{
						mWritting = false;
				}
			}
	}

	void Scene::renderInputFields()
	{
		if (mInputField.size() > 0)
			for (auto& itr : mInputField)
				itr.second->render();
	}
}