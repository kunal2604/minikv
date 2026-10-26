#pragma once

#include<cstddef>
#include<optional>
#include<string>
#include<unordered_map>

class KVStore
{
public:
    void set(std::string key, std::string value);
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);
    std::size_t size() const;

private:
    std::unordered_map<std::string, std::string> data_;
};