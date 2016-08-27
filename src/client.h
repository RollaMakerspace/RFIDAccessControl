#ifndef RFIDCLIENT_H
#define RFIDCLIENT_H

#include <iostream>
#include "restclient-cpp/restclient.h"
#include <string.h>
#include "json.hpp"
#include <cstdint>

using namespace std;
using json = nlohmann::json;

class RFIDClient {
public:
	RFIDClient(string access_script);
	int char2int(char input);
	std::vector<uint8_t>* get_key_and_access(string uid, int area, bool &has_access);
protected:
	string m_access_script;
};

#endif