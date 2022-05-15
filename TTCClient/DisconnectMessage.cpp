#include "DisconnectMessage.h"

namespace tttmessaging
{
	DisconnectMessage::DisconnectMessage() { type = disconnect; }

	DisconnectMessage::DisconnectMessage(string disconnectInfo) {
		type = disconnect;
		this->disconnectInfo = disconnectInfo;
	}

	DisconnectMessage::~DisconnectMessage() {}

	void DisconnectMessage::Serialise(ostream& os) {
		Message::Serialise(os);
		os << disconnectInfo;
	}

	void DisconnectMessage::UnserialiseType(istream& is) { disconnectInfo = GetStringFromStream(is); }

	void DisconnectMessage::SetDisconnectInfo(string disconnectInfo) { this->disconnectInfo = disconnectInfo; }

	string DisconnectMessage::GetDisconnectInfo() { return disconnectInfo; }
}