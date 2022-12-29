#include "json.hpp"

std::string JSONArray::to_string() const
{
    std::string s = "[";
    size_t c = 0;
    for (auto itr = _elem.cbegin(); itr != _elem.cend(); itr++)
    {
        const JSON *json = *itr;
        s += json->to_string();
        if (c + 1 < _elem.size())
        {
            s += ", ";
        }
        c++;
    }
    s += "]";
    return s;
}

std::string JSONObject::to_string() const
{
    std::string s = "{";
    size_t c = 0;

    for (auto itr = _map.cbegin(); itr != _map.cend(); itr++)
    {
        const std::string &key = itr->first;
        const JSON *value = itr->second;
        s += '\"' + key + "\": ";
        s += value->to_string();
        if (c + 1 < _map.size())
        {
            s += ',';
        }
        c++;
    }

    s += '}';

    return s;
}

JSONObject::~JSONObject()
{
    for (auto itr = _map.begin(); itr != _map.end(); itr++)
    {
        delete itr->second;
        itr->second = NULL;
    }
}

JSONArray::~JSONArray()
{
    for (auto itr = _elem.begin(); itr != _elem.end(); itr++)
    {
        delete *itr;
        *itr = NULL;
    }
}