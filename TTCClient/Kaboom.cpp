#include "Kaboom.h"

namespace tttmessaging {
	Kaboom::Kaboom() { type = kaboom; }

	Kaboom::Kaboom(int col, int row) {
		type = kaboom;
		this->col = col;
		this->row = row;
	}

	Kaboom::~Kaboom() {}

	void Kaboom::SetRow(int row) { this->row = row; }
	void Kaboom::SetCol(int col) { this->col = col; }

	int Kaboom::GetRow() { return row; }
	int Kaboom::GetCol() { return col; }

	void Kaboom::Serialise(ostream& os) {
		Message::Serialise(os);
		os << row << endl << col;
	}

	void Kaboom::UnserialiseType(istream& is) {
		is >> row;
		is >> col;
	}
}