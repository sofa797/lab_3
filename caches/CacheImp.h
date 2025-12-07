#pragma once
#include "ICache.h"

template<typename Key, typename Value>
class ExampleCache : public ICache<Key, Value> {
public:
    ExampleCache() {}
    
    void set(const Key& key, const Value& value) override {
        return;
    }
    
    Value get(const Key& key) override {
        return Value();
    }
    
    bool contains(const Key& key) const override {
        return false;
    }
    
    void clear() override {
        return;
    }
    
    size_t size() const override {
        return 0;
    }
};
