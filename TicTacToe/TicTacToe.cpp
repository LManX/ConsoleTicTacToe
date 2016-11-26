// TicTacToe.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

char square[10] = { 'o','1','2','3','4','5','6','7','8','9' };
char cursor = '[]';

int checkConditions();
void drawBoard();
void input();

int main()
{
	bool playerTurn;
	int i, choice;
	char mark;

	drawBoard();



    return 0;
}

void drawBoard()
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

	cout << "     |     |     " << endl << endl;
}

void input()
{

}
