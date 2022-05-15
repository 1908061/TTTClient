#pragma once

#include <string>
#include <sstream>

#include "ConnectionInstance.h"
#include "Messages.h"

using namespace std;
using namespace tttmessaging;

class TTTNetworkClient
{
	public:
		TTTNetworkClient(ConnectionInstance* ci);
		~TTTNetworkClient();

		string GetStringFromConsole(string prompt);
		int GetIntFromConsole(string prompt);

		void StartGame();

		void SendNetworkMessage(Message* m);
		Message* GetNetworkMessage();

	private:
		ConnectionInstance* ci;
		bool canUseKaboom = true;

		bool ConnectToTTTServer();
		GameState* PlayGame();

		void PrintBoard(vector<vector<SquareState>> board);

		void GetGridUpdate();
		void GetGridUpdate(Message* rg);
		void SelectMove();
		void UseKaboom();
		void PlayerOptionSelection();
};

