//
// Created by zsotroav on 2024-04-18.
//

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <regex>

using namespace std;

namespace nyetwork {
    string exec(const char* cmd) {
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw runtime_error("popen() failed!");

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

     vector<string> getIPv4() {
        regex regexip("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\b){4}$");
        string sys;
        #ifdef __WIN32__
            sys = exec("ipconfig | findstr /i \"ipv4\"");
        #else
            sys = exec("ifconfig | grep "inet "");
        #endif

        const auto ip_beg = sregex_iterator(sys.begin(), sys.end(), regexip);
        const auto ip_end = sregex_iterator();

        vector<string> re;

        for (std::sregex_iterator i = ip_beg; i != ip_end; ++i)
            re.emplace_back(i->str());

        return re;
    }
}
