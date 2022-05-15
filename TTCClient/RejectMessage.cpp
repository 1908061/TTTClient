#include "RejectMessage.h"

namespace tttmessaging
{
	RejectMessage::RejectMessage() { type = reject; }

	RejectMessage::RejectMessage(string rejectMessage) {
		type = reject;
		this->rejectMessage = rejectMessage;
	}

	RejectMessage::~RejectMessage() {}

	string RejectMessage::GetRejectMessage() { return rejectMessage; }

	void RejectMessage::Serialise(ostream& os) {
		Message::Serialise(os);
		os << rejectMessage;
	}

	void RejectMessage::UnserialiseType(istream& is) { is >> rejectMessage; }

	void RejectMessage::SetMessage(string rejectMessage) { this->rejectMessage = rejectMessage; }
}