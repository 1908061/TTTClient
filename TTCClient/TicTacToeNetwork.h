#pragma once

#include <iostream>
#include <condition_variable>

#include "Messages.h"
#include "TicTacToe.h"
#include "ConnectedPlayer.h"

enum GamePhase { WaitingForFirstPlayer, WaitingForSecondPlayer, Playing, Ended };

using namespace tttmessaging;

class TicTacToeNetwork
{
public:
	TicTacToeNetwork();
	~TicTacToeNetwork();

	void PrintGrid();
	void PlayGame(ConnectedPlayer* tPlayer);

	GamePhase GetState();
	bool AddPlayer(ConnectedPlayer* player);

private:
	void HandleDisconnect(ConnectedPlayer* opponent);

	TicTacToe* ttt;

	ConnectedPlayer* player1 = nullptr;
	ConnectedPlayer* player2 = nullptr;

	void InitialiseGame();

	condition_variable turnChange;
	mutex turnSync;

	GamePhase state;
};

