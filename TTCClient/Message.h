#pragma once

#include <iostream>
#include <sstream>

namespace tttmessaging {
	using namespace std;

	enum MessageType { 
		connect, 
		disconnect, 
		accept, 
		reject, 
		requestupdate, 
		gamegrid, 
		makemove,
		kaboom,
		gamestate 
	};

	class Message {
		public:
			Message();
			~Message();

			virtual void Serialise(ostream& os);
			virtual void UnserialiseType(istream& is) = 0;
			
			void SetType(MessageType type);

			static Message* Unserialise(istream& is);
			static Message* Unserialise(string s);

			MessageType GetType();

			string Serialise();
			string GetStringFromStream(istream& is);
		protected:
			MessageType type;
	};
}