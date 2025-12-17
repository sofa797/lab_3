#pragma once
#include "ICache.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

template<typename Key, typename Value>
class Clockcache : public ICache<Key, Value> {
private:
    struct Buffer{
        Key key;
        Value value;
        int usage_count = 0;
        bool busy = false;
    };
    std::vector<Buffer> cache;
    std::unordered_map<Key, size_t> hash_table;
    size_t capacity;
    size_t ptr=0;
    size_t findvictim() {
        while (true){
            Buffer& b=cache[ptr];
            if (!b.busy){
                return ptr;
            }
            if (b.usage_count==0){
                return ptr;
            }
            b.usage_count--;
            ptr=(ptr+1) % capacity;
        }
    }
public:
    explicit Clockcache(size_t c): capacity(c), cache(c) {}
    
    void set(const Key& key, const Value& value) override {
        auto it=hash_table.find(key);
        if (it != hash_table.end()) {
            Buffer& i=cache[it->second];
            i.value=value;
            i.usage_count=std::min(i.usage_count+1, 5);
            return;
        }
        size_t victim=findvictim();
        if (cache[victim].busy){
            hash_table.erase(cache[victim].key);
        }
        cache[victim].key=key;
        cache[victim].value=value;
        cache[victim].usage_count=1;
        cache[victim].busy=true;
        hash_table[key]=victim;
        ptr=(victim+1) % capacity;
    }

    Value get(const Key& key) override {
        auto it=hash_table.find(key);
        if (it != hash_table.end()){
            Buffer& i=cache[it->second];
            i.usage_count=std::min(i.usage_count+1, 5);
            return i.value;
        }
        return Value{};
    }
    
    bool contains(const Key& key) const override {
        return hash_table.find(key) != hash_table.end();
    }
    
    void clear() override {
        hash_table.clear();
        for (auto& i: cache){
            i.busy=false;
            i.usage_count=0;
        }
        ptr=0;
    }
    
    size_t size() const override {
        return hash_table.size();
    }
};
