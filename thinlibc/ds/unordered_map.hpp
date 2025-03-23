#pragma once

template<typename Key, typename Value>
class unordered_map {
    public:
    bool contains( Key );
    Value& operator[](Key key) const;

};