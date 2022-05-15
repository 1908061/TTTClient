#pragma once
#include "Connection.h"
#include "ConnectionInstance.h"
class ClientConnection : Connection
{
	public:
		ClientConnection(INet4Add* address);
		~ClientConnection();

		void BindConnection();
		ConnectionInstance* ConnectToServer();
};

