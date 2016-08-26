#ifndef RFIDHANDLER_H
#define RFIDHANDLER_H

#include <iostream>

extern "C" {
#include <libnfc.h>
}

using namespace std;

class RFIDHandler {
public:
	RFIDHandler();
	bool init();
	void close();
	void set_doorstrike_callback(void (*set_doorstrike)(bool));
	void scan_cards();

protected:
	void set_door(bool open);
	void create_application(uint32_t application_id);
	void authenticate_card(uint32_t application_id);

	std::function<void (bool)> m_doorstrike_callback;
	nfc_device *m_nfc_device;
}

#endif