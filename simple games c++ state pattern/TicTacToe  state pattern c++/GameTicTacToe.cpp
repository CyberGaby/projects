#include <iostream>
#include <algorithm>
#include <conio.h>
#include "GameState.h"

using namespace std;

int rules[] = {
	//horizontal
	 0, 1, 2,
	 3, 4, 5,
	 6, 7, 8,
	 //vertical
	 0, 3, 6,
	 1, 4, 7,
	 2, 5, 8,
	 //diagonal
	 0, 4, 8,
	 2, 4, 6,
	 -1
};

class TicTacToe : public GameState {
private:
	int player;
	char board[9];

public:
	TicTacToe(int _player, char board_param[9]) : player(_player) {
		memcpy(board, board_param, sizeof(board));
	}
	void Draw();
	int WhoWins();
	vector<Move> GetMoves();
	string Input();
	int WhoPlaysNext() { return 1; }; // who always plays
};

void TicTacToe::Draw()
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "\nPlayer 1 [X]  Player 2 [O]" << endl;
	cout << endl;

	cout << "          |     |     " << endl;
	cout << "       " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;
	cout << "     _____|_____|_____" << endl;
	cout << "          |     |     " << endl;
	cout << "       " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;
	cout << "     _____|_____|_____" << endl;
	cout << "          |     |     " << endl;
	cout << "       " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;
	cout << "          |     |     " << endl;
}

int TicTacToe::WhoWins()
{
	for (int i = 0; rules[i] >= 0; i += 3) {
		if (board[rules[i]] == 'X' && board[rules[i + 1]] == 'X' && board[rules[i + 2]] == 'X')
			return 1;
		else if (board[rules[i]] == 'O' && board[rules[i + 1]] == 'O' && board[rules[i + 2]] == 'O')
			return 2;
	}
	for (int i = 0; i < 9; i++)
		if (board[i] != 'X' && board[i] != 'O')
			return 0; // there are still valid moves - the game is not over
	return -1; // there are no valid wins, so the game is a draw
};

string TicTacToe::Input()
{
	cout << "Player " << player << " turn: ";
	return string(1, _getch());
}

vector<Move> TicTacToe::GetMoves()
{
	vector<Move> moves;
	for (int i = 0; i < 9; i++) 
		if (board[i] != 'X' && board[i] != 'O') {
			TicTacToe* p = new TicTacToe(player == 1 ? 2 : 1, board);
			p->board[i] = player == 1 ? 'X' : 'O';
			string input = "1";
			input[0] += i;
			moves.emplace_back(Move(input, p));
		}
	return moves;
}

GameState* CreateTicTacToe()
{
	char board[9] = {'1','2','3','4','5','6','7','8','9'};
	return new TicTacToe(1, board);
}