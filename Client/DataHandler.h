#ifndef DATAHANDLER_H
#define DATAHANDLER_H

namespace Engine
{
	class DataHandler
	{
	private:

		static DataHandler* sInstance;

		/* Constructor / Destructor */
		DataHandler();
		~DataHandler();

	public:

		static DataHandler* instance();
		static void release();
	};
}

#endif // !DATAHANDLER_H