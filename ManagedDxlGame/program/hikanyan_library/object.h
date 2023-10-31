#pragma once
#include <string>

class object
{
public:
    object() : id(instantiate_id()), name("DefaultName")
    {
    }

    virtual ~object()
    {
    }

    object(const std::string& name) : id(instantiate_id()), name(name)
    {
    }

    int getID() const { return id; }
    const std::string& getName() const { return name; }

    static object* instantiate(const std::string& name)
    {
        return new object(name);
    }

    static void destroy(object* obj)
    {
        delete obj;
    }

protected:
    static int instantiate_id()
    {
        static int nextID = 1;
        return nextID++;
    }

    int id;
    std::string name;
};
