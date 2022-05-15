#include "TicTacToeNetwork.h"

TicTacToeNetwork::TicTacToeNetwork() {}

TicTacToeNetwork::~TicTacToeNetwork() {}

void TicTacToeNetwork::PrintGrid() {
	cout << endl;

	vector<vector<SquareState>> board = ttt->GetBoard();

	for (auto col : board)
	{
		for (auto square : col)
		{
			switch (square)
			{
			case SquareState::empty:
				cout << "_ ";
				break;

			case SquareState::player1:
				cout << "O ";
				break;

			case SquareState::player2:
				cout << "X ";
				break;
			}
		}
		cout << endl;
	}

	cout << endl;
}

void TicTacToeNetwork::PlayGame(ConnectedPlayer* tPlayer) {
	ConnectedPlayer* winner = nullptr;
	ConnectedPlayer* opponent;

	//Wait for two players to be connected
	while (player1 == nullptr || player2 == nullptr)
	{
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	if (tPlayer == player1)
	{
		opponent = player2;
	}
	else if (tPlayer == player2)
	{
		opponent = player1;
	}
	else
	{
		cerr << "Game start attempted with player who isn't linked to game." << endl;
		return;
	}

	while (winner == nullptr && ttt->CheckForMovesRemaining() == true)
	{

		ConnectedPlayer* currentPlayer = ttt->GetCurrentPlayer();

		while (true)
		{
			Message* m = tPlayer->GetNetworkMessage();

			//A null message means either nothing received or a disconnect - handle as such.
			if (m == nullptr || m->GetType() == disconnect)
			{
				tPlayer->SetDisconnected();
				HandleDisconnect(opponent);
				//Everything else should already be handled deeper in the logic, just return.
				//There is an argument we should send back an acknowledgement.
				return;
			}
			else if (m->GetType() != requestupdate)
			{
				tPlayer->SendNetworkMessage(new RejectMessage("Invalid message.  Please try again."));
			}
			else
			{

				//Check for disconnected opponent
				if (tPlayer->GetConnectionStatus() == connected && opponent->GetConnectionStatus() == disconnected)
				{
					tPlayer->SetDisconnected();
					tPlayer->SendNetworkMessage(new DisconnectMessage("Your opponent disconnected."));
					return;
				}

				//Send message to players which informs them which player's turn it is.
				if (tPlayer == currentPlayer)
				{
					tPlayer->SendNetworkMessage(new GameState(yourturn));
				}
				else
				{
					tPlayer->SendNetworkMessage(new GameState(opponentturn));
				}
				break;
			}
		}
		if (tPlayer == currentPlayer)
		{
			lock_guard<mutex> lock(turnSync);

			while (true)
			{
				//valid messages here are makemove and disconnect.
				Message* m = tPlayer->GetNetworkMessage();

				if (m == nullptr || m->GetType() == disconnect)
				{
					//This is a condition for the condition_variable - we force this so the other player "wakes up"
					ttt->SwapTurn();
					turnChange.notify_one();
					return;
				}
				else if (m->GetType() == makemove || m->GetType() == kaboom)
				{
					if (ttt->MakeMove(((MakeMove*)m)->GetCol(), ((MakeMove*)m)->GetRow()))
					{
						tPlayer->SendNetworkMessage(new GridUpdate(ttt->GetBoard()));
						turnChange.notify_one();
						break;
					}
					else
					{
						tPlayer->SendNetworkMessage(new RejectMessage("Invalid move.  Please try again."));
					}

				}
				else
				{
					tPlayer->SendNetworkMessage(new RejectMessage("Invalid message.  Please try again."));
				}
			}
		}
		else
		{
			//The only valid messages here are requestupdate and disconnect.
			while (true)
			{
				//We expect a requestupdate here.
				Message* m = tPlayer->GetNetworkMessage();

				if (m->GetType() == disconnect)
				{
					return;
				}
				if (m->GetType() == requestupdate)
				{
					break;
				}
				else
				{
					tPlayer->SendNetworkMessage(new RejectMessage("Invalid message.  Please try again."));
				}
			}

			//Wait for opponent's turn to be over.
			unique_lock<mutex> lockT(turnSync);
			turnChange.wait(lockT, [&] {return tPlayer == ttt->GetCurrentPlayer() || opponent->GetConnectionStatus() == disconnected; });
			lockT.unlock();

			if (opponent->GetConnectionStatus() == disconnected)
			{
				tPlayer->SetDisconnected();
				tPlayer->SendNetworkMessage(new DisconnectMessage("Your opponent disconnected."));
				return;
			}
			else
			{
				tPlayer->SendNetworkMessage(new GridUpdate(ttt->GetBoard()));
			}
		}

		if (tPlayer->GetConnectionStatus() == disconnected)
		{
			HandleDisconnect(opponent);
			return;
		}
		winner = ttt->CheckForVictory();
	}

	while (true)
	{
		Message* m = tPlayer->GetNetworkMessage();

		if (m->GetType() != requestupdate)
		{
			tPlayer->SendNetworkMessage(new RejectMessage("Invalid message.  Please try again."));
		}
		else
		{
			if (winner == nullptr)
			{
				tPlayer->SendNetworkMessage(new GameState(draw));
			}
			else if (winner == tPlayer)
			{
				tPlayer->SendNetworkMessage(new GameState(win));
			}
			else
			{
				tPlayer->SendNetworkMessage(new GameState(loss));
			}

			break;
		}
	}
}

GamePhase TicTacToeNetwork::GetState() {
	return state;
}

bool TicTacToeNetwork::AddPlayer(ConnectedPlayer* player) {
	if (player1 == nullptr)
	{
		player1 = player;
		return true;
	}

	if (player2 == nullptr)
	{
		player2 = player;

		InitialiseGame();

		return true;
	}

	return false;

}

void TicTacToeNetwork::InitialiseGame() {
	ttt = new TicTacToe(player1, player2);
	state = GamePhase::Playing;
}

void TicTacToeNetwork::HandleDisconnect(ConnectedPlayer* opponent) {
	/*This method handles disconnection to ensure the opponent doesn't get stuck in the
	mutex or condition_variable.  It forces turn to the opponent's turn, then notifies the
	cv for a spurious wakeup.  Repeats until the opponent responds and disconnects.	*/
	while (opponent->GetConnectionStatus() != disconnected)
	{
		if (ttt->GetCurrentPlayer() != opponent)
		{
			ttt->SwapTurn();
		}

		turnChange.notify_one();
	}
}