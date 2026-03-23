#include <iostream>
#include <string>
#include <cstdlib>
#include "resources/termcolor.hpp"

using namespace std;

void IpInfo()
{
    string ip;
    cout << termcolor::red << "Enter IP address: " << termcolor::reset;
    getline(cin >> ws, ip);

    if (ip.empty())
    {
        cout << termcolor::red << "Error: IP address cannot be empty!" << termcolor::reset << endl;
        return;
    }

    string command = "curl -s https://ipapi.co/" + ip + "/json/";

    cout << termcolor::green << "\n=== IP Address Information ===" << termcolor::reset << endl;
    system(command.c_str());
    cout << endl;
}
