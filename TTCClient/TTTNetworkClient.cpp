#include "TTTNetworkClient.h"



TTTNetworkClient::TTTNetworkClient(ConnectionInstance* ci)
{
	this->ci = ci;
}


TTTNetworkClient::~TTTNetworkClient()
{
}

void TTTNetworkClient::StartGame()
{
	if (!ConnectToTTTServer())
	{
		//Error
		exit(-1);
	}

	GameState* endState = PlayGame();

	if (endState->GetState() == win)
	{
		cout << "Congratulations, you win!" << endl;
	}
	else if (endState->GetState() == loss)
	{
		cout << "Sorry, you lose." << endl;
	}
	else if (endState->GetState() == draw)
	{
		cout << "It's a draw." << endl;
	}
	else
	{
		cout << "Invalid end state." << endl;
		exit(-1);
	}
}

bool TTTNetworkClient::ConnectToTTTServer()
{
	while (true)
	{
		//Start by sending a connection object.  Requires a string for the username.
		string username = GetStringFromConsole("Please enter username");

		ConnectMessage* cm = new ConnectMessage();
		cm->SetUsername(username);

		SendNetworkMessage(cm);

		delete cm;

		Message* m = GetNetworkMessage();

		switch (m->GetType())
		{
		case MessageType::accept:
			cout << ((AcceptMessage*)m)->GetAcceptMessage() << endl;

			delete m;
			return true;

		case MessageType::reject:
			cout << ((RejectMessage*)m)->GetRejectMessage() << endl;
			delete m;

			break;

		default:
			cout << "Error: Incorrect message type received." << endl;
			delete m;
			return false;

		}
	}
}

GameState* TTTNetworkClient::PlayGame()
{
	while (true)
	{
		//Request current game state.

		SendNetworkMessage(new RequestUpdate());

		//Should get a response which is a GameState
		Message* m = GetNetworkMessage();

		if (m->GetType() == disconnect)
		{
			cout << ((DisconnectMessage*)m)->GetDisconnectInfo() << endl;
			return new GameState(win);
		}
		else if (m->GetType() != gamestate)
		{
			cout << "Error: server gave incorrect response." << endl;
			exit(-1);
		}



		if (((GameState*)m)->GetState() == yourturn)
		{
			while (true)
			{
				if (canUseKaboom) {
					PlayerOptionSelection();
				}
				else {
					SelectMove();
				}

				Message* tm = GetNetworkMessage();

				if (tm->GetType() == disconnect)
				{
					cout << ((DisconnectMessage*)tm)->GetDisconnectInfo() << endl;
					return new GameState(win);
				}
				else if (tm->GetType() == gamegrid)
				{
					//Move was successful - print grid
					GetGridUpdate(tm);
					break;
				}
				else if (tm->GetType() == reject)
				{
					cout << ((RejectMessage*)tm)->GetRejectMessage() << endl;
				}
				else
				{
					cout << "Error: server gave incorrect response." << endl;
					exit(-1);
				}

			}

		}
		else if (((GameState*)m)->GetState() == opponentturn)
		{
			//Request an update

			cout << "It is your opponent's turn - please wait!" << endl;
			//Send a request - the return should be a grid.
			SendNetworkMessage(new RequestUpdate());
			Message* tm = GetNetworkMessage();

			if (tm->GetType() == disconnect)
			{
				cout << ((DisconnectMessage*)tm)->GetDisconnectInfo() << endl;
				return new GameState(win);
			}
			else if (tm->GetType() == gamegrid)
			{
				//Move was successful - print grid
				GetGridUpdate(tm);
			}
			else
			{
				cout << "Error: server gave incorrect response." << endl;
				exit(-1);
			}

		}
		else
		{
			return (GameState*)m;
		}
	}
}

string TTTNetworkClient::GetStringFromConsole(string prompt)
{
	cout << prompt << endl;

	string inText;

	getline(cin, inText);

	return inText;
}

int TTTNetworkClient::GetIntFromConsole(string prompt)
{
	stringstream ss;
	ss.str(GetStringFromConsole(prompt));
	int val;
	ss >> val;
	return val;
}

void TTTNetworkClient::SendNetworkMessage(Message* m)
{
	try
	{
		ci->SendString(m->Serialise());
	}
	catch (...)
	{
		cout << "Error: Disconnected from server." << endl;
		exit(-1);
	}
}

Message* TTTNetworkClient::GetNetworkMessage()
{
	try
	{
		string msgStr = ci->ReceiveString();
		return Message::Unserialise(msgStr);
	}
	catch (...)
	{
		cout << "Error: Disconnected from server." << endl;
		exit(-1);
	}
}

void TTTNetworkClient::GetGridUpdate()
{
	Message* rg = GetNetworkMessage();

	GetGridUpdate(rg);
}

void TTTNetworkClient::GetGridUpdate(Message* rg)
{
	if (rg->GetType() != gamegrid)
	{
		cout << "Error: server gave incorrect response." << endl;
		exit(-1);
	}

	PrintBoard(((GridUpdate*)rg)->GetBoard());
}

void TTTNetworkClient::PrintBoard(vector<vector<SquareState>> board)
{

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

void TTTNetworkClient::SelectMove() {
	int col = GetIntFromConsole("Please select column (0-2)");
	int row = GetIntFromConsole("Please select row (0-2)");

	SendNetworkMessage(new MakeMove(row, col));
}

void TTTNetworkClient::UseKaboom() {
	int col = GetIntFromConsole("Please select column (0-2)");
	int row = GetIntFromConsole("Please select row (0-2)");

	SendNetworkMessage(new Kaboom(col, row));
}

void TTTNetworkClient::PlayerOptionSelection() {
	string response = GetStringFromConsole(
		"Please respond with an option: 'move' to place a piece on the board, 'kaboom' to remove a game piece from the board"
	);
	if (response == "move") {
		SelectMove();
	}
	else if (response == "kaboom") {
		UseKaboom();
		canUseKaboom = false;
	}
	else {
		//If no valid response is given, run the function again
		PlayerOptionSelection();
	}
}