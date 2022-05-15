#include "Lobby.h"

Lobby::Lobby() { tttn = new TicTacToeNetwork(); }

Lobby::~Lobby() {}

Lobby& Lobby::Inst() {
	static Lobby lobby;
	return lobby;
}

TicTacToeNetwork* Lobby::GetGame() { return tttn; }