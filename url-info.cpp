#include <iostream>
#include <string>
#include <cstdlib>
#include "resources/termcolor.hpp"

using namespace std;

void UrlInfo()
{
    string url;
    cout << termcolor::red << "Enter URL: " << termcolor::reset;
    getline(cin >> ws, url);

    if (url.empty())
    {
        cout << termcolor::red << "Error: URL cannot be empty!" << termcolor::reset << endl;
        return;
    }

    cout << termcolor::green << "\n=== HTTP Headers ===\n" << termcolor::reset;
    string headers = "curl -I " + url;
    system(headers.c_str());

    cout << termcolor::green << "\n=== WHOIS Info ===\n" << termcolor::reset;
    string whoisCmd = "whois " + url;
    system(whoisCmd.c_str());

    cout << endl;
}
