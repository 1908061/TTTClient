#pragma once
#include "Message.h"

namespace tttmessaging {
	class Kaboom : public Message {
		public:
			Kaboom();
			Kaboom(int col, int row);
			~Kaboom();

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