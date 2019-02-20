#include "Edition function.h"

int main()
{
	ifstream fileInForStart("Date/Date for start.dat");

	int widthOfTheScrean, heightOfTheScrean, sizeOfCell, timeForWorkProgram, timeForFPS;
	fileInForStart >> widthOfTheScrean >> heightOfTheScrean >> sizeOfCell >> timeForWorkProgram >> timeForFPS;


	RenderTexture textureForWindow;
	RenderWindow window(VideoMode(widthOfTheScrean, heightOfTheScrean), "Beta chess", Style::None);

	textureForWindow.create(widthOfTheScrean, heightOfTheScrean);

	game(window, textureForWindow, heightOfTheScrean, widthOfTheScrean, timeForWorkProgram, timeForFPS, sizeOfCell);

	return 0;
}