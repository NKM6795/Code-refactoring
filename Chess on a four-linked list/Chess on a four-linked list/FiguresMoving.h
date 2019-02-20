#include "SinglyLinked.h"

class FiguresMoving
{
private:
	void checkPosition(Cell *cell, Cell *beginCell, SinglyLinked &freeCell, SinglyLinked &enemy);
	void checkPositionForKing(Cell *cell, SinglyLinked &freeCell, SinglyLinked &enemy);
	void checkVertAndHoriz(Cell *cell, SinglyLinked &freeCell, SinglyLinked &enemy);
	void checkDiagonal(Cell *cell, SinglyLinked &freeCell, SinglyLinked &enemy);
	void checkPositionForKnight(Cell *cell, SinglyLinked &freeCell, SinglyLinked &enemy);
	void checkPositionForPawn(Cell *cell, SinglyLinked &freeCell, SinglyLinked &enemy);
public:
	void erase(Cell *cell);
	void goTo(Cell *firsCell, Cell *secondCell);
	void checkAllFunction(Cell *cell, SinglyLinked &freeCell, SinglyLinked &enemy);
};