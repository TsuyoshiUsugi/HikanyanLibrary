#include "object.h"

// 静的メンバの初期化
int object::nextID = 1;

int object::instantiate_id() {
    return nextID++;
}

object* object::instantiate(const std::string& name) {
    return new object(name);
}

void object::destroy(const object* object) {
    delete object;
}