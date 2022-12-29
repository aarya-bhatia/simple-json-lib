#include <string>
#include <vector>
#include <unordered_map>

class JSON
{
public:
    JSON() {}
    virtual ~JSON() {}
    virtual std::string to_string() const { return NULL; }
    virtual JSON *clone() const { return NULL; }
};

class JSONArray : public JSON
{
public:
    JSONArray() : JSON()
    {
    }

    ~JSONArray();

    JSON *get(size_t index)
    {
        return _elem[index];
    }

    void add(JSON *json)
    {
        _elem.push_back(json);
    }

    std::string to_string() const override;

    JSON *clone() const override
    {
        JSONArray *json = new JSONArray();
        json->_elem = _elem;
        return json;
    }

private:
    std::vector<JSON *> _elem;
};

class JSONObject : public JSON
{
public:
    JSONObject() : JSON()
    {
    }

    ~JSONObject();

    void set(const std::string &key, JSON *value)
    {
        _map[key] = value;
    }

    JSON *get(const std::string &key)
    {
        if (_map.find(key) == _map.end())
        {
            return NULL;
        }

        return _map[key];
    }

    std::string to_string() const override;

    JSON *clone() const override
    {
        JSONObject *json = new JSONObject();
        json->_map = _map;
        return (JSON *)json;
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
