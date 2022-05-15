#pragma once

#include <WS2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

class INet4Add
{
	public:
		INet4Add();
		INet4Add(char* add, int port);
		INet4Add(int port);

		~INet4Add();

		//Using the sock address pointer to connect
		sockaddr_in* GetSockaddrRef();

		//Get either the reference to add length, or the value itself
		size_t *GetSocketAddLengthRef();
		size_t GetSocketAddLengthVal();

		void GetSocketAdd(char*, int len);
		string GetSocketAdd();

		int GetPort();

		void Print();

	private:
		sockaddr_in address;
		size_t length;
};

