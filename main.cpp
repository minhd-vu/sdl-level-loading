
#include "MyGame.h"

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " *.txt" << std::endl;
		return 1;
	}

	GMUCS425::MyGame *game = new GMUCS425::MyGame(800, 800);
	assert(game);
	GMUCS425::setMyGame(game);

	//Start up SDL and create window
	if (!game->init("CS425 PA01"))
	{
		std::cerr << "ERROR: Failed to initialize!" << std::endl;
	}
	else
	{
		//Load media
		if (!game->loadMedia(argv[1]))
		{
			std::cerr << "ERROR: Failed to load media!" << std::endl;
		}
		else
		{
			game->run();
		}
	}

	game->close();

	delete game;

	return 0;
}
