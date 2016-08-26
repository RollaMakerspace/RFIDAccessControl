//#include "config.h"

#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <nfc/nfc.h>

#include <freefare.h>
#include "freefare_internal.h"

//#include <wiringPi.h>

#include <openssl/rand.h>

#include <curl/curl.h>
#include <jansson.h>


uint8_t default_key_data[16]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

char *access_server = "https://access-control.rollamakerspace.com/has_access.php";
char *json_test_url = "https://access-control.rollamakerspace.com/test.php";