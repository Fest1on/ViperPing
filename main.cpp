#include <cstdlib>
#include "ip-info.cpp"
#include <iostream>
#include <ostream>
#include <string>
#include "resources/termcolor.hpp"
#include "icmpf.cpp"
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>
#include <cctype>
#include <arpa/inet.h>
#include "url-info.cpp"
#include "port-scanner.cpp"

extern void icmpf();
extern void IpInfo();
extern void UrlInfo();

using namespace std;

void tor_start()
{
    if (getenv("TOR")) return;
    system("tor --SocksPort 9050 --quiet & sleep 4");
    setenv("TOR", "1", 1);
    char path[1024]{};
    readlink("/proc/self/exe", path, sizeof(path));
    execve(path, const_cast<char* const*>(__environ), environ);
}

int main()
{
   tor_start();
   system("clear");
   string logo = R"(
 __  __                                 ____
/\ \/\ \  __                           /\  _`\   __
\ \ \ \ \/\_\  _____      __   _ __    \ \ \L\ \/\_\    ___      __
 \ \ \ \ \/\ \/\ '__`\  /'__`\/\`'__\   \ \ ,__/\/\ \ /' _ `\  /'_ `\
  \ \ \_/ \ \ \ \ \L\ \/\  __/\ \ \/     \ \ \/  \ \ \/\ \/\ \/\ \L\ \
   \ `\___/\ \_\ \ ,__/\ \____\\ \_\      \ \_\   \ \_\ \_\ \_\ \____ \
    `\/__/  \/_/\ \ \/  \/____/ \/_/       \/_/    \/_/\/_/\/_/\/___L\ \
                 \ \_\                                           /\____/
                  \/_/                                           \_/__/ )";

   cout << termcolor::red << logo << "\n\n";
   cout << "1. --icmpf ICMP Flood" << endl;
   cout << "2. --ps Port scanner" << endl;
   cout << "3. --ipi IP info" << endl;
   cout << "4. --urlinfo URL info" << endl << endl;
   string choice;
   cout << "> ";
   getline(cin, choice);
   if (choice == "--icmpf")
   {
     icmpf();
   } else if (choice == "--ipi") {
     IpInfo();
   } else if (choice == "--urlinfo") {
     UrlInfo();
   } else if (choice == "--ps"){
    startScan();
   } else {
    cout << "Unknown command" << endl;
    sleep(2);
    main();
   }
   return 0;
}
