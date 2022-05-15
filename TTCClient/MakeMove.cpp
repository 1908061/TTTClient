#include "MakeMove.h"

namespace tttmessaging
{
	MakeMove::MakeMove() { type = makemove; }

	MakeMove::MakeMove(int row, int col) {
		type = makemove;
		this->row = row;
		this->col = col;
	}

	MakeMove::~MakeMove() {}

	void MakeMove::SetRow(int row) { this->row = row; }

	void MakeMove::SetCol(int col) { this->col = col; }

	int MakeMove::GetRow() { return row; }

	int MakeMove::GetCol() { return col; }

	void MakeMove::Serialise(ostream& os) {
		Message::Serialise(os);
		os << row << endl << col;
	}

	void MakeMove::UnserialiseType(istream& is) {
		is >> row;
		is >> col;
	}
}