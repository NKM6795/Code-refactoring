#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;
using namespace sf;

enum Figure
{
	Nothing = 0,
	King,
	Queen,
	Rook,
	Bishop,
	Knight,
	Pawn
};

enum ColorFigures
{
	NoColor = 0,
	White,
	Black
};


struct Cell
{
	bool moveThroughOne;
	bool firstUnique;
	Figure figure;
	ColorFigures color;
	Vector2i position;

	Cell *up = nullptr;
	Cell *down = nullptr;
	Cell *left = nullptr;
	Cell *right = nullptr;

	Cell();

	void setInformation(int figureForStruct, int colorForStruct, int i, int j);
};

struct SinglyNode
{
	int i;
	int j;
	SinglyNode *next = nullptr;
	SinglyNode(int iForStruct, int jForStruct);
};
