#include "Message.h"
#include "Messages.h"

namespace tttmessaging
{
	Message::Message() {}

	Message::~Message()	{}

	void Message::Serialise(ostream& os) { os << type << endl; }

	string Message::Serialise() {
		stringstream ss;
		Serialise(ss);

		return ss.str();
	}

	Message* Message::Unserialise(istream& is) {
		Message* m = nullptr;

		unsigned int tType = 0;
		MessageType type;

		if (is >> tType)
		{
			type = static_cast<MessageType>(tType);
		}

		switch (type)
		{
		case accept:
			m = new AcceptMessage();
			break;

		case connect:
			m = new ConnectMessage();
			break;

		case disconnect:
			m = new DisconnectMessage();
			break;

		case gamestate:
			m = new GameState();
			break;

		case gamegrid:
			m = new GridUpdate();
			break;

		case makemove:
			m = new MakeMove();
			break;

		case reject:
			m = new RejectMessage();
			break;

		case requestupdate:
			m = new RequestUpdate();
			break;
		}

		m->UnserialiseType(is);

		return m;
	}

	Message* Message::Unserialise(string s) {
		stringstream ss;
		ss.str(s);
		return Unserialise(ss);
	}

	void Message::SetType(MessageType type) { this->type = type; }

	MessageType Message::GetType() { return type; }

	string Message::GetStringFromStream(istream& is) {
		string msg;

		is.ignore(numeric_limits<streamsize>::max(), '\n');

		while ((is.peek() != '\n') && (is.peek() != EOF))
		{
			string tmp;
			is >> tmp;
			msg = msg + tmp + " ";
		}

		return msg;
	}
}