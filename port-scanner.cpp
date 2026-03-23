#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

mutex mtx;

map<int, string> commonPorts = {
    {21, "FTP"},
    {22, "SSH"},
    {23, "TELNET"},
    {25, "SMTP"},
    {53, "DNS"},
    {80, "HTTP"},
    {110, "POP3"},
    {143, "IMAP"},
    {443, "HTTPS"},
    {3306, "MySQL"},
    {3389, "RDP"}
};

string resolveHost(const string& host)
{
    addrinfo hints{}, *res;
    hints.ai_family = AF_INET;

    if (getaddrinfo(host.c_str(), NULL, &hints, &res) != 0)
        return "";

    char ip[INET_ADDRSTRLEN];
    sockaddr_in* addr = (sockaddr_in*)res->ai_addr;
    inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));

    freeaddrinfo(res);
    return string(ip);
}

void scanPort(const string& ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return;

    sockaddr_in target{};
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    if (connect(sock, (sockaddr*)&target, sizeof(target)) == 0)
    {
        lock_guard<mutex> lock(mtx);

        cout << "[OPEN] Port " << port;

        if (commonPorts.count(port))
            cout << " (" << commonPorts[port] << ")";

        cout << endl;
    }

    close(sock);
}

void startScan()
{
    string target;
    cout << "Enter IP or domain: ";
    cin >> target;

    string ip = resolveHost(target);
    if (ip.empty())
    {
        cout << "Error resolving host!\n";
        return;
    }

    cout << "Resolved IP: " << ip << endl;

    int startPort, endPort;
    cout << "Start port: ";
    cin >> startPort;
    cout << "End port: ";
    cin >> endPort;

    int maxThreads = 200;
    vector<thread> threads;

    cout << "\nScanning...\n";

    for (int port = startPort; port <= endPort; port++)
    {
        threads.emplace_back(scanPort, ip, port);

        if (threads.size() >= maxThreads)
        {
            for (auto& t : threads) t.join();
            threads.clear();
        }
    }

    for (auto& t : threads) t.join();

    cout << "\nScan complete \n";
}
