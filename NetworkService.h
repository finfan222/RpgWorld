/*
///////// Description:
Пример создания коннекта:
    void myfunc() {
        ...some code
        NetworkService network; // whe constructor called - it starts connect
    }
Для закрытия коннекта используйте tryDisconnect()
*/

#ifndef NETWORK_SERVICE_HPP
#define NETWORK_SERVICE_HPP

#include "System.h"
#include "Structures.h"

static const UShort PORT = 10001; // to config
static const String IP = "127.0.0.1"; // to config

static sf::TcpSocket NetSocket;
static sf::TcpListener NetListener;
static sf::SocketSelector NetSelector;
static sf::Time NetTimeOut = sf::seconds(15); // to config
static sf::Time NetReconnectTime = sf::seconds(5); // to config

static sf::TcpSocket::Status Disconnected = sf::TcpSocket::Status::Disconnected;
static sf::TcpSocket::Status Connected = sf::TcpSocket::Status::Done;
static sf::TcpSocket::Status Error = sf::TcpSocket::Status::Error;
static sf::TcpSocket::Status NotReady = sf::TcpSocket::Status::NotReady;

template<typename T, typename enable_if<is_base_of<BaseStruct, T>::value>::type* = nullptr>
inline char* write(T structure)
{
	return reinterpret_cast<char*>(&structure);
}

template<typename T, typename enable_if<is_base_of<BaseStruct, T>::value>::type* = nullptr >
inline T* read(char* data)
{
	return (T*)data;
}

sf::Packet& operator<<(sf::Packet& packet, VersionRequest& data);
sf::Packet& operator>>(sf::Packet& packet, VersionAnswer& data);

void sendPacket(VersionRequest& request);
VersionAnswer& receivePacket();

class NetworkService
{
private:
	float getTime();

public:
	NetworkService();
	~NetworkService();
	bool tryConnect();
	void tryDisconnect();
	bool isDisconnected();
};

#endif