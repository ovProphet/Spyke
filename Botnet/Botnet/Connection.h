#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Connection
{
public:
	Connection(char* address)
	{
		WSADATA WSAData;

		WSAStartup(MAKEWORD(2, 0), &WSAData);
		server = socket(AF_INET, SOCK_STREAM, 0);

		addr.sin_addr.s_addr = inet_addr(address);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(9090);
		connect(server, (SOCKADDR *)&addr, sizeof(addr));
	}
	~Connection()
	{
		closesocket(server);
		WSACleanup();
	}
	void Send(char* message);
private:
	SOCKET server;
	SOCKADDR_IN addr;
};
