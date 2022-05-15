#include "ConnectionInstance.h"

ConnectionInstance::ConnectionInstance(SOCKET sock) { this->sock = sock; }

ConnectionInstance::~ConnectionInstance() {}

void ConnectionInstance::Writen(const char* data, int bytesToWrite)
{
	//How many bytes we have left to write...
	int nleft = bytesToWrite;
	//... and how many have been written.
	int nwritten;

	while (nleft > 0) //Write until the buffer has been written to the end.
	{
		if ((nwritten = send(sock, data, nleft, 0)) <= 0)
		{
			//send returned an error - handle it.
			if (nwritten < 0 && errno == EINTR)
			{
				//EINTR indicates an interrupt stopped our read.  Retry.
				nwritten = 0;
			}
			else
			{
				//Error reported by write drop out with an error code.
				throw - 1;
			}
		}
		else //Read successful (0 or more bytes read)
		{
			//Decrement bytes left.
			nleft -= nwritten;
			//More pointer along buffer (bytes).
			data += nwritten;
		}
	}

	//Check the amount we have left (should be 0).
	if (nleft != 0)
	{
		throw nleft;
	}
}

void ConnectionInstance::Readn(char* data, int bytesToRead)
{
	//How many bytes we have left to read...
	int nleft = bytesToRead;
	//... and how many have been read.
	int nread;

	while (nleft > 0) //Read until the buffer is full.
	{
		if ((nread = recv(sock, data, nleft, 0)) < 0)
		{
			//recv returned an error - handle it.
			if (errno == EINTR) //host delivery failure
			{
				nread = 0;  //reset count and go back around the loop.
			}
			else
			{
				throw - 1;	//return error code
			}
		}
		else
		{
			//No error.
			if (nread == 0)
			{
				break; //connection closed - exit loop.
			}
			else //read success
			{
				//Update pointers
				nleft -= nread;
				data += nread;
			}
		}
	}

	//Check the amount we have left (should be 0).
	if (nleft != 0)
	{
		throw nleft;
	}
}

void ConnectionInstance::SendInt(int value)
{
	value = htonl(value);
	char* tosend = (char*)&value;
	Writen(tosend, sizeof(value));
}

int ConnectionInstance::ReceiveInt()
{
	int value = 0;
	char* recv_buffer = (char*)&value;
	Readn(recv_buffer, sizeof(int));

	return ntohl(value);
}

void ConnectionInstance::SendString(string value)
{
	SendInt((int)value.length());

	Writen(value.c_str(), (int)value.length());
}

string ConnectionInstance::ReceiveString()
{
	int incMessageSize = ReceiveInt();

	char* incMessage = new char[incMessageSize + 1];
	Readn(incMessage, incMessageSize);

	incMessage[incMessageSize] = '\0';

	string s(incMessage);

	delete incMessage;

	return s;

}

void ConnectionInstance::SetSocket(SOCKET sock) { this->sock = sock; }

SOCKET ConnectionInstance::GetSocket() { return sock; }

void ConnectionInstance::Disconnect() { closesocket(sock); }