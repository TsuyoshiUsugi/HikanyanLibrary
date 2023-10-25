#pragma once
#include <string>

class object {
public:
    object() : id(instantiate_id()), name("DefaultName") {}
    virtual ~object() {}
    object(const std::string& name) : id(instantiate_id()), name(name) {}
    
    int getID() const { return id; }
    const std::string& getName() const { return name; }

    static object* instantiate(const std::string& name);
    static void destroy(const object* object);

protected:
    static int instantiate_id();  // メソッドの宣言
    int id;
    std::string name;
    static int nextID;
};
