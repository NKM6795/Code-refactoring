#include "DrawBoard.h"

void DrawBoard::setInformation(int sizeOfBoardForClass, int offsetForClass)
{
	sizeOfBoard = sizeOfBoardForClass;
	offset = offsetForClass;
	change = false;

	figureTexture.loadFromFile("Date/Objects/Figures/chess.png");
	figureSprite.setTexture(figureTexture);

	allotmentTexture.loadFromFile("Date/Objects/Buttons/Allotment.png");
	allotmentSprite.setTexture(allotmentTexture);

	freeCellTexture.loadFromFile("Date/Objects/Buttons/Free cell.png");
	freeCellSprite.setTexture(freeCellTexture);

	enemyTexture.loadFromFile("Date/Objects/Buttons/Enemy.png");
	enemySprite.setTexture(enemyTexture);

	changeTexture.loadFromFile("Date/Objects/Figures/figure for change.png");
	changeSprite.setTexture(changeTexture);
}

void DrawBoard::draw(RenderTexture &textureForWindow, int heightOfTheScrean, int widthOfTheScrean, int sizeOfCell, Cell *head, Vector2i allotment, SinglyNode *headForFreeCell, int lengthForFreeCell, SinglyNode *headForEnemy, int lengthForEnemy, int turn)
{
	Cell *beginOfLine = head;
	for (int i = 0; i < sizeOfBoard; ++i)
	{
		Cell *cell = beginOfLine;
		for (int j = 0; j < sizeOfBoard; ++j)
		{
			if (cell->figure != 0)
			{
				figureSprite.setPosition(j * sizeOfCell + offset, i * sizeOfCell + offset);
				figureSprite.setTextureRect(IntRect((cell->figure - 1) * sizeOfCell, (2 - cell->color) * sizeOfCell, sizeOfCell, sizeOfCell));
				textureForWindow.draw(figureSprite);
			}

			cell = cell->right;
		}
		beginOfLine = beginOfLine->down;
	}

	if (allotment.x != -1)
	{
		allotmentSprite.setPosition(allotment.x * sizeOfCell + offset, allotment.y * sizeOfCell + offset);
		textureForWindow.draw(allotmentSprite);
	}

	SinglyNode *node = headForFreeCell;
	for (int i = 0; i < lengthForFreeCell; ++i)
	{
		freeCellSprite.setPosition(node->i * sizeOfCell + offset, node->j * sizeOfCell + offset);
		textureForWindow.draw(freeCellSprite);
		node = node->next;
	}
	node = headForEnemy;
	for (int i = 0; i < lengthForEnemy; ++i)
	{
		enemySprite.setPosition(node->i * sizeOfCell + offset, node->j * sizeOfCell + offset);
		textureForWindow.draw(enemySprite);
		node = node->next;
	}

	if (change)
	{
		Image tempImage;
		tempImage.create(widthOfTheScrean, heightOfTheScrean, sf::Color(0, 0, 0, 200));
		Texture tempTexture;
		tempTexture.loadFromImage(tempImage);
		Sprite tempSprite;
		tempSprite.setTexture(tempTexture);

		textureForWindow.draw(tempSprite);

		changeSprite.setTextureRect(IntRect(0, turn == ColorFigures::White ? 0 : sizeOfCell, sizeOfCell * 4, sizeOfCell));
		changeSprite.setPosition(widthOfTheScrean / 2, heightOfTheScrean / 2);
		changeSprite.setOrigin(changeTexture.getSize().x / 2, changeTexture.getSize().y / 2);
		textureForWindow.draw(changeSprite);
	}
}
