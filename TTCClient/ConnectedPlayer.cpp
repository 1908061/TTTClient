#include "ConnectedPlayer.h"

ConnectedPlayer::ConnectedPlayer(string playerName, ConnectionInstance* ci) {
	this->playerName = playerName;
	this->ci = ci;
	status = connected;
}

ConnectedPlayer::~ConnectedPlayer() {}

void ConnectedPlayer::SetPlayerName(string playerName) { this->playerName = playerName; }

string ConnectedPlayer::GetPlayerName() { return playerName; }

void ConnectedPlayer::SetConnectionInstance(ConnectionInstance* ci) { this->ci = ci; }

ConnectionInstance* ConnectedPlayer::GetConnectionInstance() { return ci; }

Message* ConnectedPlayer::GetNetworkMessage() {
	try
	{
		string msgStr = ci->ReceiveString();
		Message* m = Message::Unserialise(msgStr);

		if (m->GetType() == disconnect)
		{
			cout << "Info: " << playerName << " disconnected during game." << endl;
			status = disconnected;
		}

		return Message::Unserialise(msgStr);
	}
	catch (...)
	{
		cout << "Info: " << playerName << " disconnected unexpectedly." << endl;
		status = disconnected;
		return nullptr;
	}
}

void ConnectedPlayer::SendNetworkMessage(Message* message) {
	try
	{
		ci->SendString(message->Serialise());
	}
	catch (...)
	{
		cout << "Info: " << playerName << " disconnected unexpectedly." << endl;
		status = disconnected;
	}
}

PlayerConnectionStatus ConnectedPlayer::GetConnectionStatus() { return status; }

void ConnectedPlayer::SetDisconnected() { status = disconnected; }