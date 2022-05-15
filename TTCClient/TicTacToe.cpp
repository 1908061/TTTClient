#include "TicTacToe.h"
#include "ConnectedPlayer.h"

TicTacToe::TicTacToe(ConnectedPlayer* p1, ConnectedPlayer* p2) {
	const int limit = 3;
	for (int i = 0; i < limit; i++)
	{
		vector<SquareState> row;

		for (int j = 0; j < limit; j++)
		{
			row.push_back(SquareState::empty);
		}

		board.push_back(row);
	}

	this->p1 = p1;
	this->p2 = p2;

	playerTurn = SquareState::player1;
}

TicTacToe::~TicTacToe() {}

vector<vector<SquareState>> TicTacToe::GetBoard() {
	return board;
}

ConnectedPlayer* TicTacToe::GetPlayer(SquareState ss) {
	//A helper function to get the winning player from a SquareState.
	switch (ss)
	{
	case player1:
		return p1;
		break;
	case player2:
		return p2;
		break;
	default:
		return nullptr; //empty - error
	}
}

bool TicTacToe::MakeMove(int column, int row) {
	//Boundary check
	if (column < 0 || column > 2)
	{
		return false;
	}

	if (row < 0 || row > 2)
	{
		return false;
	}

	//Emptiness check
	if (board[row][column] != SquareState::empty)
	{
		return false;
	}

	board[row][column] = playerTurn;
	SwapTurn();

	return true;
}

bool TicTacToe::Kaboom(int col, int row) {
	//Boundary & Emptiness check
	if (col < 0 || col > 2) { return false; }
	if (row < 0 || row > 2) { return false; }
	if (board[row][col] != SquareState::empty) { return false; }

	board[row][col] = SquareState::empty;

	//Collapse above game pieces in column
	for (int i = col; i < 3; i++) {
		int aboveIndex = i++;
		if (board[row][col] != SquareState::empty) {
			board[row][col] = board[row][aboveIndex];
		}
	}
	SwapTurn();
	return true;
}

void TicTacToe::SwapTurn() {
	switch (playerTurn)
	{
	case player1:
		playerTurn = player2;
		return;
	case player2:
		playerTurn = player1;
		return;
	}
}

ConnectedPlayer* TicTacToe::CheckForVictory() {
	//columns

	for (int i = 0; i < 3; i++)
	{
		//I could loop this, but for 3 squares, why bother?
		if (board[0][i] != SquareState::empty && board[0][i] == board[1][i] && board[0][i] == board[2][i])
		{
			return GetPlayer(board[0][i]);
		}
	}

	//rows
	for (auto row : board)
	{
		if (equal(row.begin() + 1, row.end(), row.begin()) && row[0] != SquareState::empty)
		{
			return GetPlayer(row[0]);
		}
	}

	if (board[1][1] == SquareState::empty)
	{
		return nullptr;
	}

	//diagonals
	if (board[0][0] == board[1][1] && board[2][2] == board[1][1])
	{
		return GetPlayer(board[1][1]);
	}

	if (board[0][2] == board[1][1] && board[2][0] == board[1][1])
	{
		return GetPlayer(board[1][1]);
	}

	return nullptr;
}

bool TicTacToe::CheckForMovesRemaining() {
	for (auto row : board)
	{
		if (any_of(row.begin(), row.end(), [](SquareState ss) { return ss == SquareState::empty; }))
		{
			return true;
		}
	}

	return false;
}

ConnectedPlayer* TicTacToe::GetCurrentPlayer() { return GetPlayer(playerTurn); }