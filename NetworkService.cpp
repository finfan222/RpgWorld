#include "NetworkService.h"

NetworkService::NetworkService()
{
}

NetworkService::~NetworkService()
{
}

bool NetworkService::tryConnect()
{
	if (!isDisconnected()) {
		return true;
	}

	try {
		NetSocket.setBlocking(false);
		sf::Socket::Status result = NetSocket.connect(IP, PORT);
		if (result == sf::Socket::Done) {
			cout << "Connection accepted to " << IP << ":" << PORT << endl;
		} else {
			cerr << "Connection refused." << endl;
		}
		return result;
	}
	catch (exception e) {
		cerr << "Connection failed. Trying to reconnect after " << getTime() << endl;
		cerr << e.what() << endl;
	}
	return false;
}

void NetworkService::tryDisconnect()
{
	if (!isDisconnected()) {
		NetSocket.disconnect();
		cout << "Connection was closed." << endl;
	}
	else {
		cout << "Already disconnected. Just thread was terminated and released." << endl;
	}
}

bool NetworkService::isDisconnected()
{
	return NetSocket.getRemotePort() == 0;
}

float NetworkService::getTime()
{
	return static_cast<float>(NetReconnectTime.asMilliseconds() / 1000);
}

sf::Packet& operator<<(sf::Packet& packet, VersionRequest& data)
{
	packet.append(&(data.OPCODE), sizeof(UShort));
	packet.append(&(data.version), sizeof(UInt));
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, VersionAnswer& data)
{
	return packet >> data.answer;
}

void sendPacket(VersionRequest& request)
{
	sf::Packet s_packet;
	s_packet << request;
	NetSocket.send(s_packet);
	cout << "Send: " << s_packet.getDataSize() << " bytes" << endl;
}

VersionAnswer& receivePacket()
{
	VersionAnswer versionAnswer;
	sf::Packet packet;
	NetSocket.receive(packet);
	cout << "Filled and getted: " << packet.getDataSize() << endl;
	return versionAnswer;
}
