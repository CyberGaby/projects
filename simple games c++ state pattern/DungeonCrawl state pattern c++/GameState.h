#pragma once

#include <string>
#include <vector>

class GameState; // forward declaration of a class, this allows us to declare a pointer to the class in the Move structure

struct Move {
	std::string key;   // what the player should enter to indicate that he wants to play this move; for example in chess a popular move is E2-E4
	GameState* state;  // the new state of the game if the player makes this move 

	Move(std::string key, GameState* state)
		: key(key), state(state) {} // note how you can initialize members in constructors, even the names can be the same
};

class GameState {
public:
	GameState() {}
	virtual ~GameState() {}
	virtual void Draw() = 0; // draws the game state on the screen
	virtual int WhoPlaysNext() = 0; // returns the 1 based index of the player who should make the next move
	virtual int WhoWins() = 0; // returns the 1 based index of the player who is victorious in this state; 0 means no player has won (the game continues); -1 means a draw; 
	virtual std::vector<Move> GetMoves() = 0; // returns the possible next GameStates from the current GameState
	virtual std::string Input() = 0; // reads keyboard input - some games may read only 1 key, others may need more info
};