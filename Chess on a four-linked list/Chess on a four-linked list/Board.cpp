#include "Board.h"

Cell *Board::getCell(int i, int j)
{
	Cell *cell = head;
	for (int k = 0; k < j; ++k)
	{
		cell = cell->down;
	}
	for (int k = 0; k < i; ++k)
	{
		cell = cell->right;
	}
	return cell;
}

void Board::setInformation(int sizeOfBoardForClass, int offsetForClass, string addressOfBeginingPosition)
{
	turn = ColorFigures::White;
	moveThroughOne = -1;
	keyIsPressed = false;
	needDoing = false;
	figureIsAllotment = false;
	allotment = { -1, -1 };
	sizeOfBoard = sizeOfBoardForClass;
	offset = offsetForClass;

	ifstream fileIn(addressOfBeginingPosition);
	int figure, color;
	Cell *cell = head;
	for (int i = 0; i < sizeOfBoard; ++i)
	{
		Cell *temp = new Cell();
		fileIn >> figure >> color;
		temp->setInformation(figure, color, 0, i);

		if (i == 0)
		{
			head = temp;
			cell = head;
		}
		else
		{
			temp->left = cell;
			cell->right = temp;
			cell = cell->right;
		}
	}
	
	Cell *beginOfLine = head;
	Cell *cellUp = head->right;
	for (int i = 1; i < sizeOfBoard; ++i)
	{
		cellUp = beginOfLine->right;
		cell = beginOfLine;

		for (int j = 0; j < sizeOfBoard; ++j)
		{
			Cell *temp = new Cell();

			fileIn >> figure >> color;
			temp->setInformation(figure, color, i, j);
			if (j == 0)
			{
				temp->up = cell;
				cell->down = temp;
				cell = cell->down;
			}
			else
			{
				temp->left = cell;
				cell->right = temp;
				temp->up = cellUp;
				cellUp->down = temp;
				cell = cell->right;
				cellUp = cellUp->right;
			}
		}
		beginOfLine = beginOfLine->down;
	}

	drawBoard.setInformation(sizeOfBoard, offset);
}

void Board::work(Vector2i mousePosition, bool isPressed, int sizeOfCell)
{
	if (!drawBoard.change)
	{
		if (isPressed)
		{
			keyIsPressed = true;
			int i = (mousePosition.x - offset) / sizeOfCell,
				j = (mousePosition.y - offset) / sizeOfCell;
			if (i >= 0 && i < sizeOfBoard && j >= 0 && j < sizeOfBoard && mousePosition.x > offset && mousePosition.y > offset)
			{
				Cell *cell = getCell(i, j);

				if (cell->figure != 0 && cell->color == turn)
				{
					allotment = { i, j };
					if (allotment != allotmentPast)
					{
						figureIsAllotment = true;
						allotmentPast = allotment;
					}
				}
			}
		}

		if (!isPressed && keyIsPressed)
		{
			needDoing = true;
			keyIsPressed = false;
		}

		if (needDoing && allotment.x != -1)
		{
			needDoing = false;
			int i = (mousePosition.x - offset) / sizeOfCell,
				j = (mousePosition.y - offset) / sizeOfCell;
			if (i >= 0 && i < sizeOfBoard && j >= 0 && j < sizeOfBoard && mousePosition.x > offset && mousePosition.y > offset)
			{
				bool check = false;

				SinglyNode *node = freeCell.getHead();
				for (int k = 0; k < freeCell.getSize(); ++k)
				{
					if (node->i == i && node->j == j)
					{
						check = true;
					}
					node = node->next;
				}
				node = enemy.getHead();
				for (int k = 0; k < enemy.getSize(); ++k)
				{
					if (node->i == i && node->j == j)
					{
						check = true;
					}
					node = node->next;
				}

				if (check)
				{
					Cell *first = getCell(allotment.x, allotment.y);
					Cell *second = getCell(i, j);
					if (first->figure == Figure::Pawn)
					{
						first->firstUnique = false;
						if (allotment.y - j == 2 || allotment.y - j == -2)
						{
							first->moveThroughOne = true;
							moveThroughOne = turn;
						}
						if ((allotment.x - i == 1 || allotment.x - i == -1) && (allotment.y - j == 1 || allotment.y - j == -1) && second->color == ColorFigures::NoColor)
						{
							if ((allotment.x - i == 1 && allotment.y - j == 1) || (allotment.x - i == 1 && allotment.y - j == -1))
							{
								figuresMoving.erase(first->left);
							}
							else if ((allotment.x - i == -1 && allotment.y - j == 1) || (allotment.x - i == -1 && allotment.y - j == -1))
							{
								figuresMoving.erase(first->right);
							}
						}
						if (second->position.x == sizeOfBoard - 1 || second->position.x == 0)
						{
							drawBoard.change = true;
						}
					}
					else if (first->figure == Figure::King)
					{
						first->firstUnique = false;
						if (allotment.x - i == -2)
						{
							figuresMoving.goTo(first->right->right->right, first->right);
						}
						if (allotment.x - i == 2)
						{
							figuresMoving.goTo(first->left->left->left->left, first->left);
						}
					}
					else if (first->figure == Figure::Rook)
					{
						first->firstUnique = false;
					}

					figuresMoving.goTo(first, second);
					allotment = { -1, -1 };
					enemy.clear();
					freeCell.clear();

					turn = (ColorFigures)(2 - (turn + 1) % 2);

					if (moveThroughOne == turn)
					{
						Cell *beginOfLine = head;
						for (int i = 0; i < sizeOfBoard; ++i)
						{
							Cell *cell = beginOfLine;
							for (int j = 0; j < sizeOfBoard; ++j)
							{
								if (cell->moveThroughOne)
								{
									cell->moveThroughOne = false;
								}

								cell = cell->right;
							}
							beginOfLine = beginOfLine->down;
						}
						moveThroughOne = -1;
					}
				}
			}
		}

		if (figureIsAllotment)
		{
			enemy.clear();
			freeCell.clear();
			Cell *cell = getCell(allotment.x, allotment.y);

			figuresMoving.checkAllFunction(cell, freeCell, enemy);

			
			figureIsAllotment = false;
		}
	}
	else
	{
		if (isPressed && mousePosition.x - offset >= 2 * sizeOfCell && mousePosition.x - offset < 6 * sizeOfCell && mousePosition.y - offset >= 3 * sizeOfCell && mousePosition.y - offset < 4 * sizeOfCell)
		{
			Cell *beginOfLine = head;
			for (int i = 0; i < sizeOfBoard; ++i)
			{
				Cell *cell = beginOfLine;
				for (int j = 0; j < sizeOfBoard; ++j)
				{
					if (cell->figure == Figure::Pawn && (cell->position.x == sizeOfBoard - 1 || cell->position.x == 0))
					{
						cell->figure = (Figure)((mousePosition.x - offset) / sizeOfCell);
					}
					cell = cell->right;
				}
				beginOfLine = beginOfLine->down;
			}
			drawBoard.change = false;
		}
	}
}

void Board::draw(RenderTexture &textureForWindow, int heightOfTheScrean, int widthOfTheScrean, int sizeOfCell)
{
	drawBoard.draw(textureForWindow, heightOfTheScrean, widthOfTheScrean, sizeOfCell, head, allotment, freeCell.getHead(), freeCell.getSize(), enemy.getHead(), enemy.getSize(), turn);
}