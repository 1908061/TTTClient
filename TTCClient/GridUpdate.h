#pragma once

#include <vector>
#include "TicTacToe.h"
#include "Message.h"

namespace tttmessaging
{
	class GridUpdate : public Message
	{
		public:
			GridUpdate();
			GridUpdate(vector<vector<SquareState>> board);
			~GridUpdate();

			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			void SetBoard(vector<vector<SquareState>> board);

			vector<vector<SquareState>> GetBoard();
		private:
			vector<vector<SquareState>> board;
	};
}