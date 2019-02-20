#include "Edition function.h"

void game(RenderWindow &window, RenderTexture &textureForWindow, int heightOfTheScrean, int widthOfTheScrean, int timeForWorkProgram, int timeForFPS, int sizeOfCell)
{
	ifstream fileIn("Date/Date for game.dat");

	int countOfButtons;
	fileIn >> countOfButtons;

	Button *buttonsForGame = new Button[countOfButtons];

	for (int i = 0; i < countOfButtons; ++i)
	{
		int x, y, timerForPointing, timerForPressing;
		fileIn >> x >> y >> timerForPointing >> timerForPressing;
		buttonsForGame[i].setInformation(x, y, string("Update"));
		buttonsForGame[i].setMaxTimerForPressing(timerForPressing);
		buttonsForGame[i].setMaxTimerForPointing(timerForPointing);
	}


	string addressOfbackground;
	getline(fileIn, addressOfbackground);
	getline(fileIn, addressOfbackground);

	Texture backgroundTexture;
	backgroundTexture.loadFromFile(addressOfbackground);
	
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	

	Vector2i mousePosition;

	Clock timerForProgramOperation, timerForDrawingObject;

	Board temp;
	temp.setInformation(8, 25, string("Date/Date for board.dat"));

	while (window.isOpen())
	{
		if (timerForProgramOperation.getElapsedTime().asMicroseconds() >= timeForWorkProgram)
		{
			mousePosition = Mouse::getPosition(window);
			Event events;
			while (window.pollEvent(events))
			{
				if (events.type == Event::Closed || (events.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
					window.close();
			}

			for (int i = 0; i < countOfButtons; ++i)
			{
				buttonsForGame[i].workWithButton(mousePosition, Mouse::isButtonPressed(Mouse::Left));
			}


			temp.work(mousePosition, Mouse::isButtonPressed(Mouse::Left), sizeOfCell);

			if (timerForDrawingObject.getElapsedTime().asMicroseconds() >= timeForFPS)
			{
				textureForWindow.draw(backgroundSprite);


				temp.draw(textureForWindow, heightOfTheScrean, widthOfTheScrean, sizeOfCell);

				for (int i = 0; i < countOfButtons; ++i)
				{
					buttonsForGame[i].drawButton(textureForWindow);
				}

				drawWindow(window, textureForWindow);
				timerForDrawingObject.restart();
			}

			timerForProgramOperation.restart();
		}
	}
}

void drawWindow(RenderWindow &window, RenderTexture &textureForWindow)
{
	textureForWindow.display();

	Sprite spriteForWindow;
	spriteForWindow.setTexture(textureForWindow.getTexture());
	window.draw(spriteForWindow);
	window.display();
	window.clear(Color(50, 100, 50));

	textureForWindow.clear(Color(50, 100, 50));
}
