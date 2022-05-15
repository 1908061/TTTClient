#pragma once
#include "Message.h"

namespace tttmessaging
{
	class MakeMove : public Message
	{
		public:
			MakeMove();
			MakeMove(int row, int col);
			~MakeMove();

			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			void SetRow(int row);
			void SetCol(int col);

			int GetRow();
			int GetCol();

		private:
			int row;
			int col;
	};
}