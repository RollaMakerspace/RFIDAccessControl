void create_makerspace_application(FreefareTag tag)
{
  int res;
  res = mifare_desfire_create_application_aes(tag, main_aid, 0x0F, 3);
  if(res < 0)
  {
    printf("Error: create_makerspace_application: failed to create application\n");
  }
  
  res = mifare_desfire_select_application(tag, main_aid);
  if(res < 0)
  {
    printf("Error: create_makerspace_application: failed to select application\n");
  }
}

void init_makerspace_keys(FreefareTag tag, MifareDESFireKey rkeys[])
{
  MifareDESFireKey keys[3];
  
  for(uint8_t j = 0;j < 3;j++)
  {
    MifareDESFireKey temp = generate_rand_aes_key();
    keys[j] = temp;
    printf("Key %u:", j);
    print_key(temp);
    printf("\n");
    
    if(j == 0)
    {
      modify_makerspace_key(tag, j, temp, default_key, default_key);
    } else
    {
      modify_makerspace_key(tag, j, temp, default_key, keys[0]);
    }
  }
  
  rkeys = keys;
}

void modify_makerspace_key(FreefareTag tag, uint8_t key_no, MifareDESFireKey new_key, MifareDESFireKey old_key, MifareDESFireKey master)
{
  int res;
  res = mifare_desfire_select_application(tag, main_aid);
  if(res < 0)
  {
    printf("Error: modify_makerspace_main_key: failed to select application\n");
  }
  
  res = mifare_desfire_authenticate(tag, 0, master);
  if(res < 0)
  {
    printf("Error: modify_makerspace_main_key: failed to authenticate\n");
  }
  
  res = mifare_desfire_change_key(tag, key_no, new_key, old_key);
  if(res < 0)
  {
    printf("Error: modify_makerspace_main_key: failed to change key\n");
  }
  //mifare_desfire_key_free (key1);
}

bool authenticate(FreefareTag tag, MifareDESFireKey key, uint8_t key_no)
{
  //MifareDESFireKey key1 = mifare_desfire_aes_key_new (new_key_data);
  mifare_desfire_select_application(tag, main_aid);
  int auth = mifare_desfire_authenticate(tag, key_no, key);
  return (auth>=0);
}

void print_key(MifareDESFireKey key)
{
  for(int i =0;i<16;i++)
  {
    printf("%02X", key->data[i]);
    if(i!=15) printf("-");
  }
}

MifareDESFireKey generate_rand_aes_key()
{
  uint8_t rand_key[16];
  RAND_bytes(rand_key, 16);
  MifareDESFireKey nkey = mifare_desfire_aes_key_new (rand_key);
  
  return nkey;
}

uint8_t hex_to_byte(const char a)
{
  switch (a)
  {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'a':
    case 'A':
      return 10;
    case 'b':
    case 'B':
      return 11;
    case 'c':
    case 'C':
      return 12;
    case 'd':
    case 'D':
      return 13;
    case 'e':
    case 'E':
      return 14;
    case 'f':
    case 'F':
      return 15;
    default:
      return -1;
  }
}

uint8_t hex_set_to_byte(const char a, const char b)
{
  return ((hex_to_byte(a) << 4) +  hex_to_byte(b));
}
