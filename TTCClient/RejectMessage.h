#pragma once
#include "Message.h"

namespace tttmessaging
{
	class RejectMessage : public Message
	{
		public:
			RejectMessage();
			RejectMessage(string rejectMessage);
			~RejectMessage();

			void Serialise(ostream& os) override;
			void UnserialiseType(istream& is) override;
			void SetMessage(string rejectMessage);

			string GetRejectMessage();
		private:
			string rejectMessage;
	};
}