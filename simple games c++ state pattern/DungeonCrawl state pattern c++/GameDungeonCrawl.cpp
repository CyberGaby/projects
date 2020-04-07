#include <iostream>
#include <algorithm>
#include <conio.h>
#include "GameState.h"

using namespace std;

class DungeonCrawl : public GameState { //reproduces a single state of the game (a specific player position).
private:
	int player_x, player_y;
	static char Grid[7][10];

public:
	static void InitGrid(); // static functions have no this pointer and can access only static members of the class

	DungeonCrawl(int x, int y) // note how you can define functions within the class declaration
	{
		player_x = clamp(x, 0, 9);
		player_y = clamp(y, 0, 6);
	}
	void Draw();
	int WhoPlaysNext() { return 1; }; // who always plays
	int WhoWins();
	vector<Move> GetMoves();
	string Input();
};


char DungeonCrawl::Grid[7][10]; // static data members should be defined outside the class

void DungeonCrawl::InitGrid()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Grid[i][j] = '.';
		}
	}

	Grid[2][6] = 'T';
	Grid[4][4] = 'T';
	Grid[5][6] = 'T';
	Grid[6][9] = 'X';
}

void DungeonCrawl::Draw()
{
	system("cls");
	cout << "\n\t\tDUNGEON CRAWL\n";

	for (int row = 0; row < 7; row++)
	{
		cout << "\t\t";
		for (int col = 0; col < 10; col++)
		{
			if (col == player_x && row == player_y)
			{
				cout << 'G';
			}
			else
			{
				cout << Grid[row][col];
			}
		}
		cout << "\n";
	}
}

int DungeonCrawl::WhoWins()
{
	if (Grid[player_y][player_x] == 'X')
		return 1;
	if (Grid[player_y][player_x] != '.')
		return 2;
	return 0;
};

string DungeonCrawl::Input()
{
	cout << "Use WASD to move" << endl;
	return string(1, _getch());
}

vector<Move> DungeonCrawl::GetMoves()
{
	vector<Move> moves;

	if (player_y > 0)
		moves.emplace_back(Move("w", new DungeonCrawl(player_x, player_y - 1)));
	if (player_x > 0)
		moves.emplace_back(Move("a", new DungeonCrawl(player_x - 1, player_y)));
	if (player_y < 6)
		moves.emplace_back(Move("s", new DungeonCrawl(player_x, player_y + 1)));
	if (player_x < 9)
		moves.emplace_back(Move("d", new DungeonCrawl(player_x + 1, player_y)));

	return moves;
}

GameState* CreateDungeonCrawl() // creates the starting position for DungeonCrawl
{
	DungeonCrawl::InitGrid(); // note how static functions are called without an instance
	return new DungeonCrawl(0, 0);
}