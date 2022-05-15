#pragma once

#include <string>

#include "Messages.h"
#include "ConnectionInstance.h"

using namespace std;
using namespace tttmessaging;

enum PlayerConnectionStatus { connected, disconnected };

class ConnectedPlayer
{
	public:
		ConnectedPlayer(string playerName, ConnectionInstance* ci);
		~ConnectedPlayer();

		void SetPlayerName(string playerName);
		string GetPlayerName();

		void SetConnectionInstance(ConnectionInstance* ci);
		ConnectionInstance* GetConnectionInstance();

		Message* GetNetworkMessage();
		void SendNetworkMessage(Message* message);

		PlayerConnectionStatus GetConnectionStatus();
		void SetDisconnected();

	private:
		string playerName;
		ConnectionInstance* ci;
		PlayerConnectionStatus status;
};

