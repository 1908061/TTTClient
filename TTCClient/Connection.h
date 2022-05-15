#pragma once
#include "INet4Add.h"
#include "ConnectionInstance.h"
class Connection
{
	public:
		Connection(INet4Add* address);
		~Connection();

		void InitialiseSocket();
		void CreateSocket();
	protected:
		INet4Add *address;
		SOCKET sockfd;
};

