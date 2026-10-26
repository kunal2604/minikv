#include "kv_store.h"
#include<utility>

void KVStore::set(std::string key, std::string value)
{
    data_.insert_or_assign(std::move(key), std::move(value));
}

std::optional<std::string> KVStore::get(const std::string& key) const
{
    auto it = data_.find(key);
    if(it == data_.end()) 
        return std::nullopt;
    return it->second;
}

bool KVStore::del(const std::string& key)
{
    return data_.erase(key) > 0;
}

std::size_t KVStore::size() const

{
    return data_.size();
}