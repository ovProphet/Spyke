#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class Connection
{
public:
	Connection(char* address, int port)
	{
		WSADATA WSAData;

		WSAStartup(MAKEWORD(2, 0), &WSAData);
		server = socket(AF_INET, SOCK_STREAM, 0);

		addr.sin_addr.s_addr = inet_addr(address);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		connect(server, (SOCKADDR *)&addr, sizeof(addr));
		//u_long iMode = 1;
		//ioctlsocket(server, FIONBIO, &iMode);
	}
	~Connection()
	{
		closesocket(server);
		WSACleanup();
	}
	void Shutdown()
	{
		shutdown(server, SD_SEND);
	}
	void Send(char* message);
	char* Recv();
	char* GetBuf() { return buf; };
private:
	char buf[1000000];
	SOCKET server;
	SOCKADDR_IN addr;
};
