#pragma once

#include "TicTacToeNetwork.h"

class Lobby
{
	public:
		static Lobby& Inst();
		~Lobby();

		TicTacToeNetwork* GetGame();

	private:
		Lobby();

		TicTacToeNetwork* tttn;
};

