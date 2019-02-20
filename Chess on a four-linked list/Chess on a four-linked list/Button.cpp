#include "Button.h"

bool Button::checkOfHitInTheRegion(Sprite &buttonSprite, Vector2i mousePosition)
{
	if (mousePosition.x > buttonSprite.getPosition().x - buttonSprite.getOrigin().x * buttonSprite.getScale().x && mousePosition.y > buttonSprite.getPosition().y - buttonSprite.getOrigin().y * buttonSprite.getScale().y && mousePosition.x < buttonSprite.getPosition().x + buttonSprite.getTexture()->getSize().x - buttonSprite.getOrigin().x * buttonSprite.getScale().x && mousePosition.y < buttonSprite.getPosition().y + buttonSprite.getTexture()->getSize().y - buttonSprite.getOrigin().y * buttonSprite.getScale().y)
	{
		return true;
	}
	return false;
}


void Button::setInformation(int coordinateOfX, int coordinateOfY, string typeOfButtonForClass)
{
	maxTimerForPointing = 100;
	maxTimerForPressing = 40;
	epsilonForScale = 0.00001;
	checkTimerForPointing = true;
	checkTimerForPressing = true;
	checkButtonIsPressed = false;
	timerPointing = -maxTimerForPointing;
	timerPressing = -maxTimerForPressing;

	characterSize = 40;

	activateAnAction = false;

	typeOfButton = typeOfButtonForClass;

	nameOfFile = "Date/Objects/Buttons/Button().png";
	nameOfFile = nameOfFile.insert(nameOfFile.find("(") + 1, typeOfButton);

	buttonTexture.loadFromFile(nameOfFile);

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setOrigin(buttonSprite.getTexture()->getSize().x / 2, buttonSprite.getTexture()->getSize().y / 2);
	buttonSprite.setPosition(coordinateOfX, coordinateOfY);
}

void Button::drawButton(RenderTexture &renderTexture)
{
	renderTexture.draw(buttonSprite);
}

void Button::workWithButton(Vector2i mousePosition, bool buttonIsPressed)
{
	if (checkOfHitInTheRegion(buttonSprite, mousePosition) || checkButtonIsPressed)
	{
		timerPointing += timerPointing < 0 ? 1 : timerPointing > 0 ? -1 : 0;
		checkTimerForPointing = false;
	}
	else
	{
		checkTimerForPointing = true;
	}

	if (checkOfHitInTheRegion(buttonSprite, mousePosition) && buttonIsPressed && !checkButtonIsPressed)
	{
		checkButtonIsPressed = true;
	}
	else if (checkOfHitInTheRegion(buttonSprite, mousePosition) && buttonIsPressed && checkButtonIsPressed)
	{
		timerPressing += timerPressing < 0 ? 1 : timerPressing > 0 ? -1 : 0;
		checkTimerForPressing = false;

		if (typeOfButton == "scrollbar")
		{
			activateAnAction = true;
		}
	}
	else if (!checkOfHitInTheRegion(buttonSprite, mousePosition) && buttonIsPressed && checkButtonIsPressed)
	{
		checkTimerForPressing = true;
	}
	else if (checkOfHitInTheRegion(buttonSprite, mousePosition) && !buttonIsPressed && checkButtonIsPressed)
	{
		activateAnAction = true;
		checkTimerForPressing = true;
		checkButtonIsPressed = false;
	}
	else if (!checkOfHitInTheRegion(buttonSprite, mousePosition) && !buttonIsPressed && checkButtonIsPressed)
	{
		checkButtonIsPressed = false;
		checkTimerForPressing = true;
		checkTimerForPointing = true;
	}

	if (timerPointing > -maxTimerForPointing && timerPointing < maxTimerForPointing && checkTimerForPointing)
	{
		timerPointing += timerPointing > 0 ? 1 : -1;
	}

	if (timerPressing > -maxTimerForPressing && timerPressing < maxTimerForPressing && checkTimerForPressing)
	{
		timerPressing += timerPressing > 0 ? 1 : -1;
	}

	buttonSprite.setScale(1 - epsilonForScale * ((timerPointing * timerPointing) + (maxTimerForPressing + timerPressing) * (maxTimerForPressing + timerPressing)), 1 - epsilonForScale * ((timerPointing * timerPointing) + (maxTimerForPressing + timerPressing) * (maxTimerForPressing + timerPressing)));
	
}

void Button::setMaxTimerForPointing(int newMaxTimerForPointing)
{
	maxTimerForPointing = newMaxTimerForPointing;
}

void Button::setMaxTimerForPressing(int newMaxTimerForPressing)
{
	maxTimerForPressing = newMaxTimerForPressing;
}

Sprite *Button::getSprite()
{
	return &buttonSprite;
}

