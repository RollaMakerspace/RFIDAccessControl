#include "rfidhandler.h"

RFIDhandler::RFIDHandler()
{
	//
}

void RFIDHandler::init()
{
	nfc_connstring devices[1];
	nfc_context *context;

	if(nfc_list_devices (context, devices, 1) == 0)
	{
		cout << "Error no NFC devices found..." << endl;
	}

	m_nfc_device = nfc_open (context, devices[0]);

	if(m_nfc_device == NULL)
	{
		cout << "Error unable to open NFC device" << endl;
	}
}