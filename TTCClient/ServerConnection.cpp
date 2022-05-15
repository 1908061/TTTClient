#include "ServerConnection.h"

ServerConnection::ServerConnection(INet4Add* address) : Connection(address) {}

ServerConnection::~ServerConnection() {}

void ServerConnection::BindSocket() {
	if (int errorCode = ::bind(
		sockfd,
		(sockaddr*)address->GetSockaddrRef(),
		(int)address->GetSocketAddLengthVal()
	) < 0
		) {
		throw WSAGetLastError();
	}
}

void ServerConnection::ListenOnSocket(int backlog) {
	if (listen(sockfd, backlog) < 0) {
		throw WSAGetLastError();
	}
}

ConnectionInstance* ServerConnection::AcceptClient() {
	SOCKET clientSocket;

	if ((
		clientSocket = accept(
			sockfd,
			(sockaddr*)address->GetSockaddrRef(),
			(int*)address->GetSocketAddLengthRef()
		)
		) < 0
		) {
		throw WSAGetLastError();
	}

	return new ConnectionInstance(clientSocket);
}

void ServerConnection::StartServer(int backlog) {
	InitialiseSocket();
	CreateSocket();
	BindSocket();
	ListenOnSocket(backlog);
}