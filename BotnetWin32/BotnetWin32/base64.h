#include "stdafx.h"
#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;
using namespace std;


#endif
class base64
{
public:
	string base64_encode(BYTE const* buf, unsigned int bufLen);
	vector<BYTE> base64_decode(string const&);
};