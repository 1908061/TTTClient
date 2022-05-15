#pragma once
#include "Message.h"

namespace tttmessaging
{
	class DisconnectMessage : public Message
	{
		public:
			DisconnectMessage();
			DisconnectMessage(string disconnectInfo);
			~DisconnectMessage();

			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			void SetDisconnectInfo(string disconnectInfo);

			string GetDisconnectInfo();

		private:
			string disconnectInfo;
	};
}