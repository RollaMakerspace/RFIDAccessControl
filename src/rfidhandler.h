#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <iostream>
#include <string.h>
#include <vector>
#include "client.h"
#include <unistd.h>
#include <functional>

extern "C" {
#include <libnfc/include/nfc/nfc.h>
}

extern "C" {
#include <libfreefare/libfreefare/freefare.h>
}

using namespace std;

class RFIDHandler {
public:
	RFIDHandler();
	void init();
	void close();
	void set_doorstrike_callback(std::function<void (bool)>* callback);
	void scan_cards();

protected:
	void set_door(bool open);
	void create_application(uint32_t application_id);
	bool authenticate_card(uint32_t application_id, std::vector<uint8_t>* key_data);

	std::function<void (bool)>* m_doorstrike_callback;
	nfc_device *m_nfc_device;
	int m_area, m_aid;
};

#endif