#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <queue>
#include <algorithm>  // Add this line for std::find
#include <map>

#pragma comment(lib, "ws2_32.lib")

class ChatServer {
private:
    std::vector<SOCKET> clients;
    std::mutex clients_mutex;
    std::vector<std::string> messageHistory;  // Store message history
    std::mutex history_mutex;
    bool running;
    SOCKET serverSocket;
    std::map<SOCKET, std::string> clientNames;  // Store client names

    void handleClient(SOCKET clientSocket) {
        char buffer[1024];
        
        // Get client name
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) return;
        buffer[bytesReceived] = '\0';
        
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clientNames[clientSocket] = std::string(buffer);
        }

        // Send message history to new client
        {
            std::lock_guard<std::mutex> lock(history_mutex);
            for (const auto& msg : messageHistory) {
                std::string msgWithSender = clientNames[clientSocket] + ": " + msg;
                send(clientSocket, msg.c_str(), msg.length(), 0);
            }
        }

        while (running) {
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) break;
            
            buffer[bytesReceived] = '\0';
            std::string message = clientNames[clientSocket] + ": " + buffer;
            
            // Store message in history
            {
                std::lock_guard<std::mutex> lock(history_mutex);
                messageHistory.push_back(message);
            }
            
            // Broadcast message to all clients
            broadcastMessage(message);
        }
        
        // Remove client
        {
            std::lock_guard<std::mutex> lock(clients_mutex);
            auto it = std::find(clients.begin(), clients.end(), clientSocket);
            if (it != clients.end()) {
                clients.erase(it);
                clientNames.erase(clientSocket);
            }
        }
        closesocket(clientSocket);
    }

    void broadcastMessage(const std::string& message) {
        std::lock_guard<std::mutex> lock(clients_mutex);
        for (SOCKET client : clients) {
            send(client, message.c_str(), message.length(), 0);
        }
    }

public:
    ChatServer() : running(true) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(12345);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
        listen(serverSocket, SOMAXCONN);
    }

    void start() {
        // Get and display server IP address
        char hostName[256];
        gethostname(hostName, sizeof(hostName));
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        
        std::string serverIP = "127.0.0.1";
        if (getaddrinfo(hostName, NULL, &hints, &res) == 0) {
            struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
            serverIP = inet_ntoa(addr->sin_addr);
            freeaddrinfo(res);
        }
        
        std::cout << "Server started on IP: " << serverIP << ", waiting for connections...\n";
        
        while (running) {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == INVALID_SOCKET) {
                continue;
            }

            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                clients.push_back(clientSocket);
            }

            std::thread clientThread(&ChatServer::handleClient, this, clientSocket);
            clientThread.detach();
        }
    }

    ~ChatServer() {
        running = false;
        closesocket(serverSocket);
        WSACleanup();
    }
};

int main() {
    ChatServer server;
    server.start();
    return 0;
}