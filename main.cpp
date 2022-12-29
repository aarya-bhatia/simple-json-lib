#include "json.hpp"
#include <iostream>

int main()
{
    JSONObject *json = new JSONObject();
    json->set("Name", new JSONString("Aarya"));
    json->set("Age", new JSONNumber(21));

    JSONArray *languages = new JSONArray();
    languages->add(new JSONString("C"));
    languages->add(new JSONString("C++"));

    json->set("Languages", languages);

    JSONObject *education = new JSONObject();
    education->set("undergraduate", new JSONString("university of illinois"));
    education->set("school", new JSONString("the shri ram school aravali"));

    json->set("education", education);

    std::cout << json->to_string() << std::endl;

    delete json;

    return 0;
}