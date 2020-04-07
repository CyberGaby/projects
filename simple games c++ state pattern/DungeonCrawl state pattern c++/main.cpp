#include <iostream>
#include "GameState.h"

using namespace std;

GameState* ProcessInput(GameState* state)
{
	vector<Move> moves = state->GetMoves();
	// process input
	while (true) {
		string input = state->Input();
		for (auto move : moves)
			if (move.key == input)
				return move.state;
		cout << "Invalid input!" << endl;
	}
}

string VictoryMessage(GameState* state) {
	if (state->WhoWins() == 1)
		return "You win!";
	else
		return "You lose!";
}

void Play(GameState* state) {
	while (true) {
		state->Draw();
		cout << endl;
		if (state->WhoWins() != 0) { // game over
			cout << VictoryMessage(state);
			return;
		}
		state = ProcessInput(state);
	}
}

GameState* CreateDungeonCrawl(); // this is a forward declaration of a function - the function itself is in GameDungeonCrawl.cpp

int main() {
	Play(CreateDungeonCrawl());
}