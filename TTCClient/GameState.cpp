#include "GameState.h"

namespace tttmessaging
{
	GameState::GameState() { type = gamestate; }

	GameState::GameState(TTTGameStatus state) {
		type = gamestate;
		this->state = state;
	}

	GameState::~GameState() {}

	void GameState::Serialise(ostream& os) {
		Message::Serialise(os);
		os << state;
	}

	void GameState::UnserialiseType(istream& is) {
		int tmp;
		if (is >> tmp)
		{
			state = static_cast<TTTGameStatus>(tmp);
		}
	}

	void GameState::SetState(TTTGameStatus state) {
		this->state = state;
	}

	TTTGameStatus GameState::GetState() {
		return state;
	}
}