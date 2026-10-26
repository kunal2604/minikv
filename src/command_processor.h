#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "kv_store.h"

class CommandProcessor
{
public:
    explicit CommandProcessor(KVStore& store);

    std::string execute(const std::string& line);
    bool shouldQuit() const 
    {
        return quit_;
    }

private:
    using Args = std::vector<std::string>;
    using Handler = std::function<std::string(Args&)>;

    struct Command
    {
        std::size_t argc;
        std::string usage;
        Handler handler;
    };

    void registerCommands();

    KVStore& store_;
    std::unordered_map<std::string, Command> commands_;
    bool quit_ = false;
};