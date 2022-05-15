#pragma once
#include "Message.h"
#include <string>

using namespace std;

namespace tttmessaging {
	class AcceptMessage : public Message {
		public:
			AcceptMessage();
			AcceptMessage(string acceptMessage);
			~AcceptMessage();

			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			void SetMessage(string acceptMessage);

			string GetAcceptMessage();
		private:
			string acceptMessage;
	};
}