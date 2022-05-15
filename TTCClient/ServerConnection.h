#pragma once
#include "Connection.h"
#include "ConnectionInstance.h"
class ServerConnection : Connection
{
	public:
		ServerConnection(INet4Add* address);
		~ServerConnection();

		ConnectionInstance* AcceptClient();

		void BindSocket();
		void ListenOnSocket(int backlog);
		void StartServer(int backlog);
};

