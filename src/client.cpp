#include <iostream>
#include "restclient-cpp/restclient.h"
#include <string.h>
#include "json.hpp"
#include <cstdint>

using namespace std;
using json = nlohmann::json;

string access_script = "https://access-control.rollamakerspace.com/get_key.php";

int char2int(char input);

std::vector<uint8_t>* get_key_and_access(string uid, int area, bool &has_access)
{
	has_access = false;
	json j;
	j["uid"] = uid;
	j["area"] = area;

	RestClient::Response r = RestClient::post(access_script, "text/json", j.dump());

	auto json_response = json::parse(r.body);

	if(json_response["access"] == 0)
	{
		has_access = false;
		return NULL;
	}
	else
	{
		has_access = true;
	}

	string key_hex = json_response["key"];

	if(key_hex.length() != 32)
	{
		cout << "Error invalid key length" << endl;
		return NULL;
	}

	std::vector<uint8_t>* key_data = new std::vector<uint8_t>(16);

	for(int i = 0;i < 32;i = i + 2)
	{
		uint8_t j = (char2int(key_hex[i]) << 4) + char2int(key_hex[i+1]);
		key_data->push_back(j);
	}

	return key_data;
}

int char2int(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}