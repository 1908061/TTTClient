#pragma once
#include "Message.h"

enum TTTGameStatus { draw, win, loss, yourturn, opponentturn };

namespace tttmessaging
{
	class GameState : public Message
	{
		public:
			GameState();
			GameState(TTTGameStatus state);
			~GameState();

			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			void SetState(TTTGameStatus state);
			
			TTTGameStatus GetState();
		private:
			TTTGameStatus state;
	};
}