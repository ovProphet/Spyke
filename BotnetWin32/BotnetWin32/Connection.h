#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

struct MemoryStruct {
	char *memory;
	size_t size;
};
class Connection
{
public:
	Connection(string address)
	{
		ip = address;
	}
	void HTTPGet(string subdirectory = "");
	void HTTPPost(string id, string message, string subdirectory = "");
	string GetBuffer() { return buffer; };
	string GetIP() { return ip; };
private:
	string ip;
	string buffer;
};
