#include<iostream>
#include<string>

#include "command_processor.h"
#include "kv_store.h"

int main()
{
    KVStore store;
    CommandProcessor processor(store);

    std::cout << "minikv ready. Commnads: SET, GET, DEL, EXISTS, SIZE, EXIT \n";

    std::string line;
    while(!processor.shouldQuit())
    {
        std::cout << "> " << std::flush;
        if(!std::getline(std::cin, line)) break;

        std::string response = processor.execute(line);
        if(!response.empty()) std::cout << response << "\n";
    }
    
    return 0;
}