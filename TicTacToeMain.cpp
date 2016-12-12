#include <iostream>
#include <conio.h>
using namespace std;

#define KEY_UP 56
#define KEY_UP_RIGHT 57
#define KEY_UP_LEFT 55
#define KEY_DOWN 50
#define KEY_DOWN_RIGHT 51
#define KEY_DOWN_LEFT 49
#define KEY_LEFT 52
#define KEY_RIGHT 54
#define KEY_ENTER 13

char squares[3][3] = { {' ', ' ', ' '}, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } }; //keeps track of what belongs in each square.

char cursor = 'X';
int cursorPosX = 0;
int cursorPosY = 0;
int winConditions = -1;
bool playerTurn = true;

void checkwin();
void drawBoard();
int playerSelection();
void PlayerInput();
bool MarkSquare(bool unmark);
bool MoveCursor(int incrementX, int incrementY);
int WrapValue(int min, int max, int value);
int CheckPos(int xPos, int yPos);
void FindValidCell();

int main()
{
	
	MarkSquare(false);
	do
	{
		drawBoard(); //draw board every frame
		
		if (playerTurn == true)
		{
			PlayerInput();
		}
		else
		{
			//AI turn
			cout << "AI TURN." << endl;
			PlayerInput();
		}
	} while (winConditions == -1); //check if game over


	switch (winConditions)
	{
	case 0:
		cout << "Player 1 Wins!" << endl;
		break;
	case 1:
		cout << "Player 2 Wins!" << endl;
		break;
	case 2:
		cout << "Game was a draw!" << endl;
		break;
	default:
		break;
	}
	
	cin.get();

	return 0;
}

void checkwin() //Long method consisting of mainly repeated code, must be a better way.
{
	//look along lines from current position
	int x = cursorPosX;
	int y = cursorPosY;
	int c = playerTurn ? 1 : 2; //which mark to look for

	for (int xAxis = 0; xAxis <= 2; xAxis++) //look along x axis
	{
		x = WrapValue(0, sizeof(squares[0]), x + 1);
		if (CheckPos(x, y) != c) //if we don't find the same mark, must not be a horizontal line, otherwise, break out.
		{
			x = cursorPosX; //reset x
			break;
		}
		else if (xAxis == 2)
		{
			winConditions = playerTurn ? 0 : 1;
			return;
		}
	}

	for (int yAxis = 0; yAxis <= 2; yAxis++) //look along y axis
	{
		y = WrapValue(0, sizeof(squares[0]), y + 1);
		if (CheckPos(x, y) != c)
		{
			y = cursorPosY;
			break;
		}
		else if (yAxis == 2)
		{
			winConditions = playerTurn ? 0 : 1;
			return;
		}
	}

	//set xy to center, as diagonal win must use it.
	x = 1;
	y = 1;

	for (int xyAxisPos = 0; xyAxisPos <= 2; xyAxisPos++) //Right hand diagonal
	{
		x = WrapValue(0, sizeof(squares[0]), x + 1);
		y = WrapValue(0, sizeof(squares[0]), y + 1);
		if (CheckPos(x, y) != c)
		{
			x = 1; //reset x
			y = 1; //reset y
			break;
		}
		else if (xyAxisPos == 2)
		{
			winConditions = playerTurn ? 0 : 1;
			return;
		}
	}

	for (int xyAxisNeg = 0; xyAxisNeg <= 2; xyAxisNeg++) //Left hand diagonal
	{
		x = WrapValue(0, sizeof(squares[0]), x - 1);
		y = WrapValue(0, sizeof(squares[0]), y + 1);
		if (CheckPos(x, y) != c)
		{
			x = 1; //reset x
			y = 1; //reset y
			break;
		}
		else if (xyAxisNeg == 2)
		{
			winConditions = playerTurn ? 0 : 1;
			return;
		}
	}

	
}

void PlayerInput()
{
	int key = 0;

	switch ((key=_getch()))
	{
	case KEY_UP:
		MarkSquare(true); //unmark
		MoveCursor(0, 1);
		MarkSquare(false); //mark
		break;
	case KEY_UP_LEFT:
		MarkSquare(true);
		MoveCursor(-1, 1);
		MarkSquare(false);
		break;
	case KEY_UP_RIGHT:
		MarkSquare(true);
		MoveCursor(1, 1);
		MarkSquare(false);
		break;
	case KEY_DOWN:
		MarkSquare(true);
		MoveCursor(0, -1);
		MarkSquare(false);
		break;
	case KEY_DOWN_LEFT:
		MarkSquare(true);
		MoveCursor(-1, -1);
		MarkSquare(false);
		break;
	case KEY_DOWN_RIGHT:
		MarkSquare(true);
		MoveCursor(1, -1);
		MarkSquare(false);
		break;
	case KEY_LEFT:
		MarkSquare(true);
		MoveCursor(-1, 0);
		MarkSquare(false);
		break;
	case KEY_RIGHT:
		MarkSquare(true);
		MoveCursor(1, 0);
		MarkSquare(false);
		break;
	case KEY_ENTER:
		checkwin();
		if(winConditions == -1)
		{
			playerTurn = !playerTurn;
			cursor = playerTurn ? 'X' : 'O';
			FindValidCell();
			drawBoard();
		}

		break;
	default:
		break;
	}
}

bool MoveCursor(int incrementX, int incrementY)
{
	int tempX = cursorPosX;
	int tempY = cursorPosY;

	for (int i = 0; i < 2; i++)
	{
		if (incrementX != 0)
		{
			tempX = WrapValue(0, sizeof(squares[0]), tempX + incrementX);
		}

		if (incrementY != 0)
		{
			tempY = WrapValue(0, sizeof(squares[0]), tempY + incrementY);
		}

		if (CheckPos(tempX, tempY) == 0) //test new pos
		{
			cursorPosX = tempX;
			cursorPosY = tempY;
			return true;
		}
	}

	return false;
}

int CheckPos(int xPos, int yPos)
{
	char cell = squares[xPos][yPos];
	if (cell == ' ')
	{
		return 0;
	}
	else if (cell == 'X')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

void FindValidCell() //find closest free cell.
{
	if (!MoveCursor(1, 0)) // try horizontal first.
	{
		for (int h = 0; h < 3; h++)//check all columns.
		{
			if (MoveCursor(0, 1)) //try the vertical cells.
			{
				MarkSquare(false);
				return;
			}
		}
		//no valid cells, its a draw.
		winConditions = 2;
	}
	else
	{
		MarkSquare(false);
	}
}

bool MarkSquare(bool unmark) //set a mark on the current square, return true if successful
{
	bool complete = false;
	if (squares[cursorPosX] [cursorPosY] == ' ' && !unmark)
	{
		squares[cursorPosX] [cursorPosY] = cursor;
		complete = true;
	}
	else
	{
		if (unmark)
		{
			squares[cursorPosX][cursorPosY] = ' ';
		}
	}
	return complete;
}

int WrapValue(int min, int max, int value)
{
	auto range = max - min;

	while (value >= max)
	{
		value -= range;
	}
	while (value < min)
	{
		value += range;
	}

	return value;
}


void drawBoard()
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << squares[0][2] << "  |  " << squares[1][2] << "  |  " << squares[2][2] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << squares[0][1] << "  |  " << squares[1][1] << "  |  " << squares[2][1] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << squares[0][0] << "  |  " << squares[1][0] << "  |  " << squares[2][0] << endl;
	cout << "     |     |     " << endl << endl;
}