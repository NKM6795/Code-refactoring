#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

using namespace std;
using namespace sf;

class Button
{
private:
	int maxTimerForPointing;
	int maxTimerForPressing;
	float epsilonForScale;
	bool checkTimerForPointing;
	bool checkTimerForPressing;
	bool checkButtonIsPressed;

	int characterSize;

	int timerPointing;
	int timerPressing;

	Texture buttonTexture;
	string nameOfFile;
	string typeOfButton;
	Sprite buttonSprite;

public:

	bool activateAnAction;

	bool checkOfHitInTheRegion(Sprite &buttonSprite, Vector2i mousePosition);


	void setInformation(int coordinateOfX, int coordinateOfY, string typeOfButtonForClass);

	void drawButton(RenderTexture &renderTexture);

	void workWithButton(Vector2i mousePosition, bool buttonIsPressed);

	void setMaxTimerForPointing(int newMaxTimerForPointing);

	void setMaxTimerForPressing(int newMaxTimerForPressing);

	Sprite *getSprite();
};
