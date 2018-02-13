#include "stdafx.h"
#include "Connection.h"

void Connection::Send(char* message)
{
	send(server, message, sizeof(char) * strlen(message), 0);
}