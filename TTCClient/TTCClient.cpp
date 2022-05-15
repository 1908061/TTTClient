#include "INet4Add.h"
#include "ClientConnection.h"
#include "ConnectionInstance.h"
#include "Messages.h"
#include "TTTNetworkClient.h"

#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace tttmessaging;
using namespace std;

int main(int argc, char** argv)
{
	char ip[] = "127.0.0.1";
	INet4Add* address = new INet4Add(ip, 50039);
	ClientConnection* conn = new ClientConnection(address);

	ConnectionInstance* ci = conn->ConnectToServer();

	TTTNetworkClient* nc = new TTTNetworkClient(ci);
	nc->StartGame();

	system("pause");
}