#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H
#include "CheckButton.h"

namespace GUI
{
	class DropDownList : public Container
	{
	private:

		Button* mIndex;
		std::vector<Button*> mItems;
		const int mMaxHeight = 100;
		
		bool mOpen;
		int mOpenHeight;

		SDL_Color mTextColor;

	public:
		/* Constructor / Destructor */
		DropDownList(GameEntity* parent, int x, int y, int width, int height, bool opaque = false);

		~DropDownList();

		/* Accessors */
		const std::string getIndex() const;

		/* Functions */
		void open();
		void addItem(std::string label);
		void removeItem();

		/* Core Functions */
		void update() override;
		void render() override;
	};
}

#endif