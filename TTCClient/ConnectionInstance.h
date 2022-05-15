#pragma once

#include <WS2tcpip.h>
#include <string>

using namespace std;

class ConnectionInstance
{
public:
	ConnectionInstance(SOCKET sock);
	~ConnectionInstance();

	void Writen(const char* data, int bytesToWrite);
	void Readn(char* data, int bytesToRead);

	void SendInt(int value);
	int ReceiveInt();

	void SendString(string value);
	string ReceiveString();

	void SetSocket(SOCKET sock);
	SOCKET GetSocket();

	void Disconnect();

private:
	SOCKET sock;
};

