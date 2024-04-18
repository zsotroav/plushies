#include <string>
#include <cstdio>
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
        string sys, line;
        vector<string> re, row;
        #ifdef __WIN32__
            sys = exec(R"(for /f "tokens=2 delims=[]" %a in ('ping -n 1 -4 "%computername%"') do @echo %a)");
        #else
            sys = exec(R"ip -4 addr | grep -oP '(?<=inet\s)\\d+(\.\d+){3}'");
        #endif

        stringstream ss(sys);
        while (getline(ss, line, '\n')) re.emplace_back(line);

        return re;
    }
}
