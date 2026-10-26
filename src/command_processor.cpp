#include "command_processor.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace
{

std::vector<std::string> tokenize(std::string_view line)
{
    std::vector<std::string> tokens;
    std::string current;
    bool inQuotes = false;
    bool hasToken = false; // lets "" count as an empty value

    for(char c : line)
    {
        if(c == '"')
        {
            inQuotes = !inQuotes;
            hasToken = true;
        }
        else if(!inQuotes && std::isspace(static_cast<unsigned char>(c)))
        {
            if(hasToken)
            {
                tokens.push_back(std::move(current));
                current.clear(); // moved-from string: reset to a known state
                hasToken = false;
            }
        }
        else
        {
            current += c;
            hasToken = true;
        }
    }

    if(inQuotes) throw std::invalid_argument("unterminated quote");
    if(hasToken) tokens.push_back(std::move(current));
    return tokens;
}    

std::string toUpper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(std::toupper(c)); }
    );
    return s;
}

} // namespace ends

CommandProcessor::CommandProcessor(KVStore& store) : store_(store)
{
    registerCommands();
}

void CommandProcessor::registerCommands()
{
    commands_["SET"] = {3, "SET <key> <value>", [this](Args& a) -> std::string {
        store_.set(std::move(a[1]), std::move(a[2]));
        return "OK";
    }};

    commands_["GET"] = {2, "GET <key>", [this](Args& a) -> std::string {
        auto value = store_.get(a[1]);
        return value ? *value : "(nil)";
    }};

    commands_["DEL"] = {2, "DEL <key>", [this](Args& a) -> std::string {
        return store_.del(a[1]) ? "1" : "0";
    }};

    commands_["EXISTS"] = {2, "EXISTS <key>", [this](Args& a) -> std::string {
        return store_.exists(a[1]) ? "1" : "0";
    }};

    commands_["SIZE"] = {1, "SIZE", [this](Args&) -> std::string {
        return std::to_string(store_.size());
    }};

    commands_["EXIT"] = {1, "EXIT", [this](Args&) -> std::string {
        quit_= true;
        return "bye...";
    }};
}

std::string CommandProcessor::execute(const std::string& line)
{
    Args args;

    try
    {
        args = tokenize(line);
    }
    catch(const std::invalid_argument& e)
    {
        return std::string("ERR ") + e.what();
    }

    if(args.empty()) return "";

    auto it = commands_.find(toUpper(args[0]));
    if(it == commands_.end())
    {
        return "ERR unknown command '" + args[0] + "'";
    }

    const Command& cmd = it->second;
    if(args.size() != cmd.argc)
    {
        return "ERR usage " + cmd.usage;
    }

    return cmd.handler(args);
}