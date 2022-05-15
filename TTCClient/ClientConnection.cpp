#include "ClientConnection.h"

ClientConnection::ClientConnection(INet4Add* address) : Connection(address) {}

ClientConnection::~ClientConnection() {}

void ClientConnection::BindConnection() {
	if (int errorCode = connect(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddLengthVal()) < 0)
	{
		throw WSAGetLastError();
	}
}

ConnectionInstance* ClientConnection::ConnectToServer() {
	InitialiseSocket();
	CreateSocket();
	BindConnection();

	return new ConnectionInstance(sockfd);
}