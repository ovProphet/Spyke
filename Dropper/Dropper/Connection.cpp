#include "stdafx.h"
#include "Connection.h"

void Connection::Send(char* message)
{
	send(server, message, sizeof(char) * strlen(message), 0);
}
char* Connection::Recv()
{
	recv(server, buf, sizeof(char) * 250000, 0);
	return GetBuf();
	// probably you should send and receive payload for dropper in chunks of 1024 bytes so that the buffer doesn't overflows
}