#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::cout << "minikv ready. Type EXIT to quit.\n";

    std::string line;
    while (true) {
        std::cout << "> " << std::flush;
        if (!std::getline(std::cin, line)) break;   // Ctrl+D ends input

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd.empty()) continue;
        if (cmd == "EXIT") break;

        std::cout << "command received: " << cmd << '\n';
    }
    std::cout << "bye\n";
}