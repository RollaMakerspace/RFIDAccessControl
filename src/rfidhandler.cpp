#include "rfidhandler.h"

RFIDHandler::RFIDHandler()
{
	m_area = 0;
	m_aid = 0x042069;
}

void RFIDHandler::init()
{
	nfc_connstring devices[1];
	nfc_context *context;

    nfc_init (&context);

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

void RFIDHandler::set_doorstrike_callback(std::function<void (bool)>* callback)
{
	m_doorstrike_callback = callback;
}

void RFIDHandler::scan_cards()
{
	FreefareTag *tags = NULL;

	tags = freefare_get_tags(m_nfc_device);

	if(tags == NULL)
	{
		cout << "Error getting tags..." << endl;
		return;
	}

	for(int i = 0;tags[i];i++)
	{
		if (MIFARE_DESFIRE != freefare_get_tag_type (tags[i]))
		{
			continue;
		}

		//int result;

		char *tag_uid_temp = freefare_get_tag_uid (tags[i]);
		std::string tag_uid(tag_uid_temp);
		delete[] tag_uid_temp;

		RFIDClient rfid_client("https://access-control.rollamakerspace.com/get_key.php");

		bool has_access = false;
		std::vector<uint8_t>* key_data = rfid_client.get_key_and_access(tag_uid, m_area, has_access);

		if(has_access)
		{
			if(authenticate_card(m_aid, key_data))
			{
				this->set_door(true);
				sleep(3);
				this->set_door(false);
			}
		}

		delete key_data;
	}

	freefare_free_tags(tags);
}

void RFIDHandler::set_door(bool open)
{
	(*m_doorstrike_callback)(open);
}

void RFIDHandler::create_application(uint32_t application_id)
{
	//Not implemented
}

bool RFIDHandler::authenticate_card(uint32_t application_id, std::vector<uint8_t>* key_data)
{

			//MifareDESFireKey key = mifare_desfire_aes_key_new(&key_data[0]);
	return false;
}