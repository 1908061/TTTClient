#include "INet4Add.h"

INet4Add::INet4Add() {}

INet4Add::INet4Add(char* add, int port) {
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, add, &address.sin_addr);
	length = sizeof(address);
}

INet4Add::INet4Add(int port) {
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	length = sizeof(address);
}

INet4Add::~INet4Add() {}

sockaddr_in* INet4Add::GetSockaddrRef() { return &address; }

size_t* INet4Add::GetSocketAddLengthRef() { return &length; }

size_t INet4Add::GetSocketAddLengthVal() { return length; }

void INet4Add::GetSocketAdd(char* charStr, int len) { inet_ntop(AF_INET, &address.sin_addr, charStr, len); }

string INet4Add::GetSocketAdd() {
	char tString[INET_ADDRSTRLEN];

	GetSocketAdd(tString, INET_ADDRSTRLEN);
	return string(tString);
}

int INet4Add::GetPort() { return ntohs(address.sin_port); }

void INet4Add::Print() {
	//Debugging purposes
	char tString[INET_ADDRSTRLEN];

	GetSocketAdd(tString, INET_ADDRSTRLEN);

	cout << "INet4Address: " << tString << ":" << ntohs(address.sin_port) << endl;
}