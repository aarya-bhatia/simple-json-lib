#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

class JSON
{
public:
    JSON() {}
    virtual ~JSON() {}
    virtual std::string to_string() const { return NULL; }
    virtual JSON *clone() const { return NULL; }
};

class JSONObject : public JSON
{
public:
    JSONObject() : JSON()
    {
    }

    void set(const std::string &key, const JSON *value)
    {
        _map[key] = value->clone();
    }

    JSON *get(const std::string &key)
    {
        if (_map.find(key) == _map.end())
        {
            return NULL;
        }

        return _map[key];
    }

    std::string to_string() const override
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

    JSON *clone() const override {
        JSONObject *json = new JSONObject();
        json->_map = _map;
        return (JSON *) json;
    }

private:
    std::unordered_map<std::string, JSON *> _map;
};

class JSONString : public JSON
{
public:
    JSONString(const std::string &s = std::string("")) : JSON(), value(s)
    {
    }

    const std::string &get() const
    {
        return value;
    }

    void set(const std::string &s)
    {
        value = s;
    }

    std::string to_string() const override
    {
        return '\"' + value + '\"';
    }

    JSON *clone() const override
    {
        return new JSONString(value);
    }

private:
    std::string value;
};

class JSONNumber : public JSON
{
public:
    JSONNumber(int value = 0) : JSON(), value(value)
    {
    }

    std::string to_string() const override
    {
        return std::to_string(value);
    }

    JSON *clone() const override
    {
        return new JSONNumber(value);
    }

private:
    int value;
};

int main()
{
    JSON *json = new JSONObject();
    ((JSONObject *) json)->set("Name", new JSONString("Aarya"));
    ((JSONObject *) json)->set("Age", new JSONNumber(21));

    JSONObject *languages = new JSONObject();
    languages->set("C", new JSONNumber(10));
    languages->set("C++", new JSONNumber(6));

    ((JSONObject *) json) -> set("Languages", languages);
    delete languages;

    std::cout << json->to_string() << std::endl;
    return 0;
}