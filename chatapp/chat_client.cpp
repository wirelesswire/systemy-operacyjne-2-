#include <iostream>
#include <thread>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class ChatClient {
private:
    SOCKET clientSocket;
    bool running;
    std::string username;

public:
    ChatClient() : running(true) {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(12345);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cout << "Failed to connect to server.\n";
            running = false;
            return;
        }

        std::cout << "Enter your username: ";
        std::getline(std::cin, username);
        send(clientSocket, username.c_str(), username.length(), 0);
    }

    void start() {
        std::cout << "Connected to server. Type your messages:\n";
        
        std::thread receiveThread(&ChatClient::receiveMessages, this);
        receiveThread.detach();

        std::string message;
        while (running) {
            std::getline(std::cin, message);
            if (message == "exit") {
                running = false;
                break;
            }
            send(clientSocket, message.c_str(), message.length(), 0);
            // Clear the current line after sending
            std::cout << "\033[A\033[2K";  // Move up one line and clear it
        }
    }

    void receiveMessages() {
        char buffer[1024];
        while (running) {
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived <= 0) {
                std::cout << "Disconnected from server.\n";
                running = false;
                break;
            }
            
            buffer[bytesReceived] = '\0';
            std::cout << buffer << std::endl;
        }
    }

    ~ChatClient() {
        running = false;
        closesocket(clientSocket);
        WSACleanup();
    }
};

int main() {
    ChatClient client;
    client.start();
    return 0;
}