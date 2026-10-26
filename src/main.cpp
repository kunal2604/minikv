#include<iostream>
#include<sstream>
#include<string>

#include "kv_store.h"

int main()
{
    KVStore store;

    std::cout << "minikv ready. Commands: SET, GET, DEL, SIZE, EXIT \n";

    std::string line;

    while(true)
    {
        std::cout << "> " << std::flush;
        if(!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if(cmd.empty()) continue;

        if(cmd == "EXIT")
            break;
        else if(cmd == "SET")
        {
            std::string key, value;
            iss >> key;
            std::getline(iss >> std::ws, value);  // value may contain spaces
            if(key.empty() || value.empty())
            {
                std::cout << "ERR usage: SET <key> <value> \n";
                continue;
            }
            store.set(std::move(key), std::move(value));
            std::cout << "OK \n";   
        }

        else if(cmd == "GET")
        {
            std::string key;
            iss >> key;
            if(auto value = store.get(key))
                std::cout << *value << "\n";
            else
                std::cout << "(nil)\n";
        }
        else if(cmd == "DEL")
        {
            std::string key;
            iss >> key;
            std::cout << (store.del(key) ? "1" : "0") << "\n"; 
        }
        else if(cmd == "SIZE")
        {
            std::cout << store.size() << "\n";
        }
        else
        {
            std::cout << "ERR unknown command '" << cmd << "'\n";
        }
    }

    std::cout << "Byeeee... \n";
    return 0;
}