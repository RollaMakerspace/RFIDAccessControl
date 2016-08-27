#include "client.h"

RFIDClient::RFIDClient(string access_script)
{
	m_access_script = access_script;
}

/**
	This function requests the key from a server for a specified card UID. If the server replies
	with no access for that UID then this function will return a null pointer and false to the 
	&has_access argument. If the server replies with a key then this function will return the 
	key and set has_access to true.

	@param[in] uid UID in hexadecimal string form
	@param[in] area Area number
	@param[out] has_access Boolean value indicating if the specified UID has access to the area
	
	@return Returns a vector<uint8_t> containing the 16 byte AES key for the specified UID or
		a null pointer if the UID doesn't have access.
*/
std::vector<uint8_t>* RFIDClient::get_key_and_access(string uid, int area, bool &has_access)
{
	has_access = false;
	json j;
	j["uid"] = uid;
	j["area"] = area;

	RestClient::Response r = RestClient::post(m_access_script, "text/json", j.dump());

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

/**
	This function converts a single hex character into decimal form.

	@param[in] input A single hexadecimal character
	@return The 0-15 integer the hex input represents
*/
int RFIDClient::char2int(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}