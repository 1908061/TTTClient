#pragma once
#include "Message.h"

namespace tttmessaging
{

	class ConnectMessage : public Message
	{
		public:
			ConnectMessage();
			~ConnectMessage();

			void SetUsername(string username);
			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			
			string GetUsername();
		private:
			string username;
	};

}